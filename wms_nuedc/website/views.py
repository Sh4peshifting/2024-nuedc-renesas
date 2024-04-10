from django.shortcuts import render, redirect

# Create your views here.
from django.http import HttpResponse, JsonResponse
from django.template import loader
from django.contrib import auth
from django.contrib.auth.models import User
from django.contrib.auth.decorators import login_required
from django.views.decorators.csrf import csrf_protect, csrf_exempt
from django.core import serializers
from django.utils import timezone

from website import models


def sign_in(request):
    return render(request, "website/sign_in/sign-in.html")


def main(request):
    return render(request, "website/main/main.html")


def log_list(request):
    return render(request, "website/log_list/log_list.html")


@csrf_exempt
def login(request):
    if request.method == "GET":
        return render(request, "website/sign_in/sign-in.html")
    username = request.POST.get("username")
    password = request.POST.get("password")
    path = request.GET.get("next") or "/"
    print(username, password)
    user_obj = auth.authenticate(username=username, password=password)
    if not user_obj:
        return redirect("/login/?&next=" + path)
    else:
        auth.login(request, user_obj)
        return redirect(path)


def reset_repository(request):
    goods = models.goods.objects.all()
    if (goods.count() == 0):
        models.goods.objects.create(place='1-1-1', number='', isempty=True)
        models.goods.objects.create(place='1-1-2', number='', isempty=True)
        models.goods.objects.create(place='1-1-3', number='', isempty=True)
        models.goods.objects.create(place='1-2-1', number='', isempty=True)
        models.goods.objects.create(place='1-2-2', number='', isempty=True)
        models.goods.objects.create(place='1-2-3', number='', isempty=True)
        models.goods.objects.create(place='1-3-1', number='', isempty=True)
        models.goods.objects.create(place='1-3-2', number='', isempty=True)
        models.goods.objects.create(place='1-3-3', number='', isempty=True)
    logs = models.log.objects.all()
    if (logs.count() == 0):
        admin = User.objects.filter(username="admin").first()
        models.log.objects.create(staff=admin, time=timezone.now(), operation="入库", other="1123")
        models.log.objects.create(staff=admin, time=timezone.now(), operation="出库", other="13123")
        models.log.objects.create(staff=admin, time=timezone.now(), operation="出库", other="a123")
        models.log.objects.create(staff=admin, time=timezone.now(), operation="入库", other="aa123")
    status = models.status.objects.all()
    if (status.count() == 0):
        models.status.objects.create(fire=False, temperature="23", humidity="12%", car_status=False)
    


@csrf_exempt
def get_respository_info(request):
    goods = models.goods.objects.all()
    serialized_books = serializers.serialize('json', goods, fields=('place', 'number', 'isempty'))
    data = {}
    data["cargo"] = []
    for item in goods:
        temp = {
            "cargo_list_id": item.place,
            "isEmpty": item.isempty,
            "cargo_id": item.number,
        }
        data["cargo"].append(temp)
    status = models.status.objects.first()
    data["context"] = {
        "isCarEmpty": status.car_status,
    }

    status.empty_self=models.goods.objects.filter(isempty=True).count()
    status.save()

    data["status"]={
        "alarm_status": "正常"if status.fire==False else "警报",
        "cargo_status": status.empty_self,
        "temp_status": status.temperature,
        "hum_status": status.humidity

    }
    return JsonResponse(data, safe=False)


@csrf_exempt
def get_log_info(request):
    goods = models.log.objects.all()
    data = {}
    data["log_list"] = []
    for item in goods:
        temp = {
            "id": item.id,
            "people": item.staff.username,
            "time": item.time,
            "operation": item.operation,
            "other": item.other,
        }
        data["log_list"].append(temp)
    return JsonResponse(data, safe=False)


@csrf_exempt
def get_car_info(request):
    goods = models.log.objects.all()
    data = {}
    data["log_list"] = []
    for item in goods:
        temp = {
            "id": item.id,
            "people": item.staff.username,
            "time": item.time,
            "operation": item.operation,
            "other": item.other,
        }
        data["log_list"].append(temp)
    return JsonResponse(data, safe=False)


@csrf_exempt
def index(request):
    return JsonResponse({"a": "helo"}, safe=False)


@csrf_exempt
def sensor(request):
    #/interface/sensor/?humi=%d&temp=%d.%d&fire=%d&working=%d
    humidity = request.GET.get("humi")
    temperature = request.GET.get("temp")
    fire = request.GET.get("fire")
    working = request.GET.get("working")

    status = models.status.objects.first()
    status.humidity = humidity
    status.temperature = temperature
    status.fire = fire
    status.car_status = working

    status.save()

    if(models.cmd8266.objects.all().count()!=0):
        cmd=models.cmd8266.objects.first().cmd
    else:
        cmd="L:0,Origin:0,Target:0,Work:0,Vacant:"+str(status.empty_self)+","
    return HttpResponse(cmd, content_type="text/plain")


@csrf_exempt
def cargo(request):
    #/interface/cargo/?cargo_id=%s&self_id%s&in=%d
    #inout: in1 out2 change3
    #L:%d,Origin:%d,Target:%d,Work:%d,
    cargo_id = request.GET.get("cargo_id")
    self_id = request.GET.get("self_id")
    in_out = request.GET.get("in")

    worigin=0
    wtarger=0
    if(self_id=="1-1-1"):
        wtarget=1
    elif(self_id=="1-1-2"):
        wtarget=2
    elif(self_id=="1-1-3"):
        wtarget=3
    elif(self_id=="1-2-1"):
        wtarget=4
    elif(self_id=="1-2-2"):
        wtarget=5
    elif(self_id=="1-2-3"):
        wtarget=6

    if(in_out=="1"):
        goods_self=models.goods.objects.filter(place=self_id).first()
        if(not goods_self):#self_id不存在
            return HttpResponse("error", content_type="text/plain")
        if(goods_self.isempty==False):#self_id已有货物
            return HttpResponse("error", content_type="text/plain")
        goods_self.update(number=cargo_id,isempty=False)
        models.log.objects.create(staff=request.user, time=timezone.now(), operation="入库", other=cargo_id)


    elif(in_out=="2"):
        goods_self=models.goods.objects.filter(number=cargo_id).first()
        if(not goods_self):#cargo_id不存在
            return HttpResponse("error", content_type="text/plain")
        if(goods_self.isempty==True):#cargo_id已出库
            return HttpResponse("error", content_type="text/plain")
        goods_self.update(number="",isempty=True)
        models.log.objects.create(staff=request.user, time=timezone.now(), operation="出库", other=cargo_id)

    

    elif(in_out=="3"):
        goods_self=models.goods.objects.filter(place=self_id).first()
        if(not goods_self):#self_id不存在
            return HttpResponse("error", content_type="text/plain")
        goods_self=models.goods.objects.filter(number=cargo_id).first()
        if(not goods_self):#cargo_id不存在
            return HttpResponse("error", content_type="text/plain")
        

        if(models.goods.objects.filter(place=self_id).first().isempty==False  or models.goods.objects.filter(number=cargo_id).first().isempty==True):
            return HttpResponse("error", content_type="text/plain")
        previous_self_id=models.goods.objects.filter(number=cargo_id).first().place
        models.goods.objects.filter(place=previous_self_id).update(number="",isempty=True)
        models.goods.objects.filter(place=self_id).update(number=cargo_id,isempty=False)
        models.log.objects.create(staff=request.user, time=timezone.now(), operation="转移", other=cargo_id)
        if(previous_self_id=="1-1-1"):
            worigin=1
        elif(previous_self_id=="1-1-2"):
            worigin=2
        elif(previous_self_id=="1-1-3"):
            worigin=3
        elif(previous_self_id=="1-2-1"):
            worigin=4
        elif(previous_self_id=="1-2-2"):
            worigin=5
        elif(previous_self_id=="1-2-3"):
            worigin=6
        
    models.cmd8266.objects.create(cmd="L:0"+",Origin:"+str(worigin)+",Target:"+str(wtarget)+",Work:"+str(in_out)+",")
    
    return HttpResponse("success", content_type="text/plain")


@csrf_exempt
def get_log(request):
    log=""
    logs=models.log.objects.all()
    for item in logs:
        log+=item.staff.username+" "+item.operation+" "+item.other+" "+str(item.time)+"\r\n"
    log="\""+log+"\""
    return HttpResponse(log, content_type="text/plain")


@csrf_exempt
def get_goods(request):
    goods_list=""
    goods=models.goods.objects.all()
    for item in goods:
        goods_list+=item.place+" "+item.number+"\r\n"

    goods_list="\""+goods_list+"\""
    return HttpResponse(goods_list, content_type="text/plain")

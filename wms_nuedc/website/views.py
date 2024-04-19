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
from django.contrib.auth.decorators import login_required

from website import models


def sign_in(request):
    return render(request, "website/sign_in/sign-in.html")


def logout(request):
    auth.logout(request)
    return redirect("/login/")


@login_required(login_url='/login/')
def main(request):
    return render(request, "website/main/main.html")


@login_required(login_url='/mobile/login/')
def mobile_main(request):
    return render(request, "website/mobile_main/mobile_main.html")


@login_required(login_url='/login/')
def log_list(request):
    return render(request, "website/log_list/log_list.html")


@login_required(login_url='/mobile/login/')
def mobile_log_list(request):
    return render(request, "website/mobile_log/mobile_log.html")


@login_required(login_url='/mobile/login/')
def mobile_shelf(request):
    return render(request, "website/mobile_shelf/mobile_shelf.html")


@csrf_exempt
def mobile_login(request):
    if request.method == "GET":
        return render(request, "website/mobile_sign_in/mobile_sign_in.html")
    username = request.POST.get("username")
    password = request.POST.get("password")
    path = request.GET.get("next") or "/mobile/"
    print(username, password)
    user_obj = auth.authenticate(username=username, password=password)
    if not user_obj:
        return redirect("/mobie/login/?&next=" + path)
    else:
        auth.login(request, user_obj)
        return redirect(path)


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

    status.empty_self = models.goods.objects.filter(isempty=True).count()
    status.save()

    data["status"] = {
        "alarm_status": "正常" if status.fire == False else "警报",
        "cargo_status": status.empty_self,
        "temp_status": status.temperature,
        "hum_status": status.humidity

    }
    return JsonResponse(data, safe=False)


@csrf_exempt
def get_log_info(request):
    goods = models.log.objects.all().order_by('-id')[:20]
    data = {}
    data["log_list"] = []
    for item in goods:
        # Format the datetime object to a string
        formatted_time = item.time.strftime('%Y-%m-%d %H:%M:%S')
        temp = {
            "id": item.id,
            "people": item.staff.username,
            "time": formatted_time,
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
    return HttpResponse("hello, world.")


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
    status.car_status = False if int(working) else True
    status.empty_self = models.goods.objects.filter(isempty=True).count()

    status.save()

    if (models.cmd8266.objects.all().count() != 0):
        cmd_record = models.cmd8266.objects.first()
        cmd = cmd_record.cmd
        cmd_record.delete()
    else:
        cmd = "L:0,Origin:0,Target:0,Work:0,Vacant:" + str(status.empty_self) + ","
    return HttpResponse(cmd, content_type="text/plain")


def cargo_operation(cargo_id, in_out, self_id, user):
    #/interface/cargo/?cargo_id=%s&self_id%s&in=%d
    #inout: in1 out2 change3
    #L:%d,Origin:%d,Target:%d,Work:%d,

    worigin = 0
    wtarget = 0

    shelf_dict = {"1-1-1": 1, "1-1-2": 2, "1-1-3": 3, "1-2-1": 4, "1-2-2": 5, "1-2-3": 6}

    if (in_out == "1"):
        wtarget = self_id
        revert_shelf_dict = {str(v): k for k, v in shelf_dict.items()}
        self_id = revert_shelf_dict[self_id]
        goods_self = models.goods.objects.filter(place=self_id).first()

        if (not goods_self):  #self_id不存在
            print("self_id不存在")
            return 1
        if (goods_self.isempty == False):  #self_id已有货物
            print("self_id已有货物")
            return 1
        goods_self.number = cargo_id
        goods_self.isempty = False
        goods_self.save()

        models.log.objects.create(staff=user, time=timezone.now(), operation="入库", other=cargo_id)


    elif (in_out == "2"):
        # findself=models.goods.objects.filter(place=cargo_id).first()
        # if(not findself):#self_id不存在
        #     return 1
        # cargo_id=findself.number
        goods_self = models.goods.objects.filter(place=self_id).first()
        if (not goods_self):  #self_id
            return 1
        if (goods_self.isempty == True):  #self_id已出库
            return 1
        cargo_id = goods_self.number
        goods_self.number = ""
        goods_self.isempty = True
        goods_self.save()
        wtarget = shelf_dict[self_id]
        models.log.objects.create(staff=user, time=timezone.now(), operation="出库", other=cargo_id)

    elif (in_out == "3"):
        goods_self = models.goods.objects.filter(place=self_id).first()
        if (not goods_self):  #self_id不存在 原货物
            return 1
        goods_self = models.goods.objects.filter(place=cargo_id).first()
        if (not goods_self):  #cargo_id不存在 现货物
            return 1

        if (models.goods.objects.filter(place=self_id).first().isempty == True \
                or models.goods.objects.filter(place=cargo_id).first().isempty == False):
            return 1
        previous_cargo_id = models.goods.objects.filter(place=self_id).first().number
        models.goods.objects.filter(place=self_id).update(number="", isempty=True)
        models.goods.objects.filter(place=cargo_id).update(number=previous_cargo_id, isempty=False)
        models.log.objects.create(staff=user, time=timezone.now(), operation="换货",
                                  other=previous_cargo_id + "->" + cargo_id)
        worigin = shelf_dict[self_id]
        wtarget = shelf_dict[cargo_id]
    elif (in_out == "4"):
        goods_self = models.goods.objects.filter(place=self_id).first()
        if (not goods_self):  #self_id不存在
            return 1
        if (goods_self.isempty == False):  #self_id已有货物
            return 1
        worigin = user.id
        wtarget = shelf_dict[self_id]

    else:
        return 1
    status = models.status.objects.first()
    models.cmd8266.objects.create(cmd="L:0" + ",Origin:" + str(worigin) + ",Target:" + str(wtarget) + \
                                      ",Work:" + str(in_out) + ",Vacant:99,")

    return 0


@csrf_exempt
def get_log(request):
    log = ""
    logs = models.log.objects.all().order_by('-id')[:10]
    for item in logs:
        log += str(item.id) + " " + item.staff.username + " " + item.operation + " " + item.other + "\r\n"
    log = "\"" + log + "\""
    return HttpResponse(log.encode('gb2312'), content_type="text/plain")


@csrf_exempt
def get_goods(request):
    goods_list = ""
    goods = models.goods.objects.all()
    for item in goods:
        goods_list += item.place + " " + item.number + "\r\n"

    goods_list = "\"" + goods_list + "\""
    return HttpResponse(goods_list.encode('gb2312'), content_type="text/plain")


@csrf_exempt
def lighton(request):
    status = models.status.objects.first()
    models.cmd8266.objects.create(cmd="L:1,Origin:0,Target:0,Work:0,Vacant:99,")
    return HttpResponse("success", content_type="text/plain")


@csrf_exempt
def lightoff(request):
    status = models.status.objects.first()
    models.cmd8266.objects.create(cmd="L:2,Origin:0,Target:0,Work:0,Vacant:99,")
    return HttpResponse("success", content_type="text/plain")


@csrf_exempt
def change_cargo(request):
    # if(models.status.objects.first().car_status==False):
    #     return JsonResponse({"status":1}, safe=False)
    self_id = request.POST.get("cargo_loc")
    cargo_id = request.POST.get("cargo_id")
    in_out = request.POST.get("cargo_op")

    if (in_out == "in_storage"):
        in_out = "4"
    elif (in_out == "out_storage"):
        in_out = "2"
    elif (in_out == "sw_cargo"):
        in_out = "3"
    else:
        return HttpResponse("error", content_type="text/plain")

    if (cargo_operation(cargo_id, in_out, self_id, request.user)):
        return JsonResponse({"status": 1}, safe=False)

    return JsonResponse({"status": 0}, safe=False)


@csrf_exempt
def cargo(request):
    self_id = request.GET.get("self_id")
    cargo_id = request.GET.get("cargo_id")
    in_out = request.GET.get("in")
    username = request.GET.get("username")
    password = request.GET.get("password")

    if (in_out == "11"):
        in_out = "1"
        user_obj = User.objects.filter(id=int(username)).first()
    else:
        user_obj = auth.authenticate(username=username, password=password)

    if not user_obj:
        return HttpResponse("error", content_type="text/plain")
    else:
        if (cargo_operation(cargo_id, in_out, self_id, user_obj)):
            return HttpResponse("error", content_type="text/plain")

    return HttpResponse("success", content_type="text/plain")


@csrf_exempt
def interface_login(request):
    username = request.GET.get("username")
    password = request.GET.get("password")
    user_obj = auth.authenticate(username=username, password=password)
    if not user_obj:
        return HttpResponse("error", content_type="text/plain")
    else:
        return HttpResponse("success", content_type="text/plain")


@csrf_exempt
def interface_shelf(request):
    shelf = ""
    for item in models.goods.objects.all():
        if (item.isempty == True):
            shelf += "0"
        else:
            shelf += "1"
    return HttpResponse(shelf.encode('gb2312'), content_type="text/plain")

from django.shortcuts import render,redirect

# Create your views here.
from django.http import HttpResponse,JsonResponse
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
    print(username,password)
    user_obj = auth.authenticate(username=username, password=password)
    if not user_obj:
        return redirect("/login/?&next="+path)
    else:
        auth.login(request, user_obj)
        return redirect(path)
    

def reset_repository(request):
    goods=models.goods.objects.all()
    if (goods.count() == 0):
            models.goods.objects.create(place='1-1-1',number='',isempty=True)
            models.goods.objects.create(place='1-1-2',number='',isempty=True)
            models.goods.objects.create(place='1-1-3',number='',isempty=True)
            models.goods.objects.create(place='1-2-1',number='',isempty=True)
            models.goods.objects.create(place='1-2-2',number='',isempty=True)
            models.goods.objects.create(place='1-2-3',number='',isempty=True)
            models.goods.objects.create(place='1-3-1',number='',isempty=True)
            models.goods.objects.create(place='1-3-2',number='',isempty=True)
            models.goods.objects.create(place='1-3-3',number='',isempty=True)
    logs=models.log.objects.all()
    if (logs.count() == 0): 
        admin=User.objects.filter(username="admin").first()
        models.log.objects.create(staff=admin,time=timezone.now(),operation="入库",other="1123")
        models.log.objects.create(staff=admin,time=timezone.now(),operation="出库",other="13123")
        models.log.objects.create(staff=admin,time=timezone.now(),operation="出库",other="a123")
        models.log.objects.create(staff=admin,time=timezone.now(),operation="入库",other="aa123")

            



def get_respository_info(request):
    goods=models.goods.objects.all()
    serialized_books = serializers.serialize('json', goods, fields=('place', 'number','isempty'))
    data={}
    data["cargo"]=[]
    for item in goods:
        temp={
            "cargo_list_id": item.place,
            "isEmpty": item.isempty,
            "cargo_id":item.number,
        }
        data["cargo"].append(temp)
    return JsonResponse(data, safe=False)

def get_log_info(request):
    goods=models.log.objects.all()
    data={}
    data["log_list"]=[]
    for item in goods:
        temp={
             "id": item.id, 
             "people": item.staff.username, 
             "time": item.time, 
             "operation": item.operation, 
             "other": item.other,
        }
        data["log_list"].append(temp)
    return JsonResponse(data, safe=False)
    

    
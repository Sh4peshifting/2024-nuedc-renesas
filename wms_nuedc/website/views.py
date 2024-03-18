from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse
from django.template import loader

def sign_in(request):
    return render(request, "website/sign_in/sign-in.html")

def main(request):
    return render(request, "website/main/main.html")
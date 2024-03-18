from django.urls import path

from . import views

urlpatterns = [
    path("sign_in/", views.sign_in, name="sign_in"),
    path("main/", views.main, name="main"),
    path("log_list/", views.log_list, name="log_list"),
]
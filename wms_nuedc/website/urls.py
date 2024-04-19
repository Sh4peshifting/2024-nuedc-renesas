from django.urls import path

from . import views

urlpatterns = [
    path("login/", views.login, name="sign_in"),
    path("", views.main, name="main"),
    path("log_list/", views.log_list, name="log_list"),
    path('reset/', views.reset_repository),
    path('repository/get_repository_info/', views.get_respository_info),
    path('repository/get_log_info/', views.get_log_info),
    path('index/', views.index),
    path('light_on/', views.lighton),
    path('light_off/', views.lightoff),
    path('change_cargo/', views.change_cargo),

    path('interface/sensor/', views.sensor),
    path('interface/cargo/', views.cargo),
    path('interface/get_log/', views.get_log),
    path('interface/get_goods/', views.get_goods),
    path('interface/login/', views.interface_login),
    path('interface/shelf/', views.interface_shelf),

    path("mobile/", views.mobile_main, name="mobile_main"),
    path("mobile/login/", views.mobile_login, name="mobile_login"),
    path("mobile/log_list/", views.mobile_log_list, name="mobile_log_list"),
    path("mobile/shelf/", views.mobile_shelf, name="mobile_shelf"),

    path("logout/", views.logout, name="logout"),
]

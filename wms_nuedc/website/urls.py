from django.urls import path

from . import views

urlpatterns = [
    path("login/", views.login, name="sign_in"),
    path("", views.main, name="main"),
    path("log_list/", views.log_list, name="log_list"),
    path('reset/',views.reset_repository),
    path('repository/get_repository_info',views.get_respository_info),
    path('repository/get_log_info',views.get_log_info),
]
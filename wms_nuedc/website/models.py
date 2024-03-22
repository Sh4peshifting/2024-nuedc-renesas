from django.db import models
from django.contrib.auth.models import User

# Create your models here.

class goods(models.Model):
    id=models.AutoField(primary_key=True)
    place=models.CharField(verbose_name='位置',max_length=10)
    number=models.CharField(verbose_name='编号',max_length=10,blank=True,null=True)
    isempty=models.BooleanField(default=True,verbose_name='可用')

class status(models.Model):
    light=models.BooleanField(default=False,verbose_name='灯光')
    temperture=models.CharField(verbose_name='温度',max_length=5)
    humidity=models.CharField(verbose_name='湿度',max_length=5)

class log(models.Model):
    id=models.AutoField(primary_key=True)
    staff=models.ForeignKey(User,verbose_name='员工',on_delete=models.CASCADE,blank=True,null=True)
    time=models.DateTimeField(verbose_name='时间',blank=True,null=True)
    operation=models.CharField(verbose_name='操作',max_length=10)
    other=models.CharField(verbose_name='详情',max_length=50)
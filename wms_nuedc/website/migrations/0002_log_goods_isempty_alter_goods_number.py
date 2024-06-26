# Generated by Django 4.2.4 on 2024-03-19 12:53

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('website', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='log',
            fields=[
                ('id', models.AutoField(primary_key=True, serialize=False)),
                ('staff', models.CharField(max_length=10, verbose_name='员工')),
                ('time', models.DateTimeField(blank=True, null=True, verbose_name='时间')),
                ('operation', models.CharField(max_length=10, verbose_name='操作')),
                ('other', models.CharField(max_length=50, verbose_name='详情')),
            ],
        ),
        migrations.AddField(
            model_name='goods',
            name='isempty',
            field=models.BooleanField(default=True, verbose_name='可用'),
        ),
        migrations.AlterField(
            model_name='goods',
            name='number',
            field=models.CharField(blank=True, max_length=10, null=True, verbose_name='编号'),
        ),
    ]

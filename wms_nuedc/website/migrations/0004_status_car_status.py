# Generated by Django 4.2.4 on 2024-03-22 09:34

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('website', '0003_alter_log_staff'),
    ]

    operations = [
        migrations.AddField(
            model_name='status',
            name='car_status',
            field=models.BooleanField(default=False, verbose_name='车状态'),
        ),
    ]

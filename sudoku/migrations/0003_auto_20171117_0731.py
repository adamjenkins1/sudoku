# -*- coding: utf-8 -*-
# Generated by Django 1.11.7 on 2017-11-17 07:31
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('sudoku', '0002_auto_20171114_0157'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='sudokudata',
            name='ac3Time',
        ),
        migrations.RemoveField(
            model_name='sudokudata',
            name='geneTime',
        ),
        migrations.AddField(
            model_name='sudokudata',
            name='algorithm',
            field=models.CharField(default='0', max_length=200),
        ),
        migrations.AddField(
            model_name='sudokudata',
            name='time',
            field=models.FloatField(default=0),
        ),
        migrations.AlterField(
            model_name='sudokudata',
            name='difficulty',
            field=models.CharField(default='0', max_length=200),
        ),
    ]
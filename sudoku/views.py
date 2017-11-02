from django.shortcuts import render, redirect, HttpResponse
from django.views.generic.base import RedirectView

def index(request):
    return render(request, 'index.html')

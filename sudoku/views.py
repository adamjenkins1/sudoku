from django.shortcuts import render, redirect, HttpResponse
from django.views.generic.base import RedirectView

def index(request):
    selected = 'home'
    return render(request, 'index.html', {'selected': selected})

def about(request):
    selected = 'about'
    return render(request, 'about.html', {'selected': selected})

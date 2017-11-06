from django.shortcuts import render, redirect, HttpResponse
from django.views.generic.base import RedirectView
import json

def index(request, boardSize, diff):
    selected = 'home'
    difficulty = ''
    shortDifficulty = diff
    if(diff == 'm'):
        difficulty = 'medium'
    elif(diff == 'e'):
        difficulty = 'easy'
    elif(diff == 'h'):
        difficulty = 'hard'
    elif(diff == 'vh'):
        difficulty = 'very hard'
    else:
        difficulty = diff

    return render(request, 'index.html', 
        {'selected': selected, 
          'boardSize': boardSize, 
          'difficulty': difficulty,
          'shortDifficulty': shortDifficulty})

def about(request):
    selected = 'about'
    return render(request, 'about.html', {'selected': selected})

def solve(request):
    ret = request.POST
    initialBoard = []
    initialBoard = ret.getlist('board[]')
    print(initialBoard)
    return HttpResponse()

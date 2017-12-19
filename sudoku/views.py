from django.shortcuts import render, HttpResponse
from django.http import JsonResponse
from .models import SudokuData
import json, subprocess, os
from time import strftime, gmtime, time

def index(request, boardSize, diff, algorithm):
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
          'shortDifficulty': shortDifficulty,
          'algorithm': algorithm})

def about(request):
    selected = 'about'
    return render(request, 'about.html', {'selected': selected})

def stats(request):
    selected = 'stats'
    return render(request, 'stats.html', {'selected': selected})

def data(request):
    return render(request, 'data.html')

def jsonData(request):
    data = SudokuData.objects.all().order_by('-id')
    dictionary = []
    obj = {}

    for row in data:
        obj = row.as_dict()
        dictionary.append(obj)

    jsonObj = json.dumps(dictionary)
    return HttpResponse(jsonObj, content_type = 'application/json')
    

def saveData(request, boardSize, diff):
    board = []
    board = request.POST.getlist('board[]')
    filename = boardSize + '_' + diff + '_' + strftime('%Y-%m-%d_%H:%M:%S', gmtime()) + '.txt'
    dir_path = os.path.dirname(os.path.realpath(__file__))
    staticPath = dir_path + '/static/'
    with open(staticPath + 'data/' + filename, 'w') as f:
        f.write(' '.join(board))
    
    return HttpResponse()

def solve(request, algorithm, difficulty):
    initialBoard = []
    initialBoard = request.POST.getlist('board[]')
    dir_path = os.path.dirname(os.path.realpath(__file__))
    tempfilePath = dir_path + '/static/c++/tempgrid'
    staticPath = dir_path + '/static/'

    if(request.method != 'POST' or len(initialBoard) == 0 or 
        (algorithm != 'AC3' and algorithm != 'Genetic' and algorithm != 'Hill')):
        return render(request, 'error.html', status = '400')

    with open(tempfilePath, 'w') as f:
        f.write(' '.join(initialBoard))
    boardSize = int((len(initialBoard))**(0.5))


    start = time()
    p = subprocess.Popen([staticPath + 'c++/solver', algorithm, str(boardSize), tempfilePath], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    real = time() - start
    #print(real)
    out, error = p.communicate()
    error = error.decode()[:-1]

    if(error != ''):
        print('Error while calling algorithm: ' + error)
        return HttpResponse('Error while calling algorithm', status = '500')

    out = out.decode()[:-2]
    solved = out[0]
    #print(out)

    solvedBoard = out[1:]
    solvedBoard = solvedBoard.strip()
    solvedBoard = solvedBoard.split(' ')
    solvedBoard = list(map(int, solvedBoard))
    solvedBoardJson = json.dumps(solvedBoard)

    if(solved != '1'):
        return HttpResponse(solvedBoardJson, content_type = 'application/json', status = '400')

    newRow = SudokuData()
    newRow.algorithm = algorithm
    newRow.size = boardSize
    newRow.time = real*1000
    newRow.difficulty = difficulty
    newRow.save()
    return HttpResponse(solvedBoardJson, content_type = 'application/json')

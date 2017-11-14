from django.shortcuts import render, HttpResponse
import json, subprocess
from time import strftime, gmtime, time

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

def stats(request):
    selected = 'stats'
    return render(request, 'stats.html', {'selected': selected})

def data(request):
    return render(request, 'data.html')

def saveData(request, boardSize, diff):
    board = []
    board = request.POST.getlist('board[]')
    filename = boardSize + '_' + diff + '_' + strftime('%Y-%m-%d_%H:%M:%S', gmtime()) + '.txt'
    with open('sudoku/static/data/' + filename, 'w') as f:
        f.write(' '.join(board))
    
    return HttpResponse()

def solve(request, algorithm):
    initialBoard = []
    initialBoard = request.POST.getlist('board[]')
    with open('sudoku/static/c++/tempgrid', 'w') as f:
        f.write(' '.join(initialBoard))
    boardSize = int((len(initialBoard))**(0.5))

    if(algorithm != 'AC3' and algorithm != 'Genetic'):
        return HttpResponse('Chosen algorithm not in supported algorithms', status = '400')

    start = time()
    p = subprocess.Popen(['./sudoku/static/c++/solver', algorithm, str(boardSize), 'sudoku/static/c++/tempgrid'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    real = time() - start
    print(real)
    out, error = p.communicate()
    error = error.decode()[:-1]

    if(error != ''):
        print('Error while calling algorithm: ' + error)
        return HttpResponse('Error while calling algorithm', status = '500')

    out = out.decode()[:-2]
    print(out)
    if(out[0] != '1'):
        print('solver encoutered an error')
        return HttpResponse('Solver unable to find puzzle solution', status = '500')

    solvedBoard = out[1:]
    solvedBoard = solvedBoard.strip()
    solvedBoard = solvedBoard.split(' ')
    solvedBoard = list(map(int, solvedBoard))
    solvedBoardJson = json.dumps(solvedBoard)

    return HttpResponse(solvedBoardJson, content_type = 'application/json')

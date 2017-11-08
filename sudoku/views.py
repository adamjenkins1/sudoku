from django.shortcuts import render, HttpResponse
import json, subprocess, time

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
    initialBoard = []
    initialBoard = request.POST.getlist('board[]')
    with open('sudoku/static/c++/tempgrid', 'w') as f:
        f.write(' '.join(initialBoard))
    boardSize = int((len(initialBoard))**(0.5))
    start = time.time()
    p = subprocess.Popen(['./sudoku/static/c++/AC3', str(boardSize), 'sudoku/static/c++/tempgrid'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    real = time.time() - start
    print(real)
    out, error = p.communicate()
    real = time.time() - start
    print(real)
    error = error.decode()[:-1]

    if(error != ''):
        print('Error while calling algorithm: ' + error)
        return HttpResponse(status = '204')

    out = out.decode()[:-2]
    print(out)
    if(out[0] != '1'):
        print('AC3 encoutered an error')
        return HttpResponse(status = '204')

    solvedBoard = out[1:]
    solvedBoard = solvedBoard.strip()
    solvedBoard = solvedBoard.split(' ')
    solvedBoard = list(map(int, solvedBoard))
    solvedBoardJson = json.dumps(solvedBoard)

    return HttpResponse(solvedBoardJson, content_type = 'application/json')

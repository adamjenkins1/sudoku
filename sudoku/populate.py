#!/usr/bin/env python3
import django
import subprocess
import os
import sys
from sudoku.models import SudokuData
from time import time

# to run script, type ../manage.py shell < populate.py
# if the db is changed, don't forget ./manage.py makemigrations 
# and ./manage.py migrate --run-syncdb

def checkForErrors(error):
  if(error != ''):
    print('Encountered the following error(s):')
    sys.exit(error)

p = subprocess.Popen(['ls', 'static/data/'], stdout = subprocess.PIPE, stderr = subprocess.PIPE)
out, error = p.communicate()
out = out.decode()[:-1]
error = error.decode()[:-1]
checkForErrors(error)

out = out.strip()
files = out.split('\n')

algorithms = ['AC3', 'Genetic']
for filename in files:
  args = filename.split('_')
  for method in algorithms:
    # comment out these lines if you want to run genetic algorithm
    if(method == 'Genetic'):
      break
    start = time()
    p = subprocess.Popen(['./static/c++/solver', method, args[0], 'static/data/' + filename], 
        stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    real = time() - start
    print('running ./static/c++/solver ' + method + ' ' + args[0] + ' static/data/' + filename)
    out, error = p.communicate()
    out = out.decode()[:-2]
    error = error.decode()[:-1]
    checkForErrors(error)

    if(out[0] == '1'):
      print('solution found, adding to database...')
      newRow = SudokuData()
      newRow.size = int(args[0])
      newRow.difficulty = args[1]
      newRow.time = real*1000
      newRow.algorithm = method
      newRow.save()
    else:
      print('solution not found, excluding from database...')

    if(filename != files[-1]):
      print()

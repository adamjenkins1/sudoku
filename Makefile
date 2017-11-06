#Makefile to run server and make the AC3 executable
#Author: Alexander Corley
# 11-6-2017

#run server
run: AC3
	manage.py runserver $(PORT)

#make AC3
AC3:
	make -C sudoku/static/c++/

#clean up stuff
clean:
	make clean -C sudoku/static/c++/

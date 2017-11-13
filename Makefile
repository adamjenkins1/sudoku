#Makefile to run server and make the solver executable
#Author: Alexander Corley
# 11-6-2017

PY="python3"
PORT="8000"

.PHONY: run clean pyreqs save-pyreqs

#run server
run: solver pyreqs
	./manage.py runserver $(PORT)

#make solver
solver:
	make -C sudoku/static/c++/

#clean up stuff
clean:
	make -C sudoku/static/c++/ clean

pyreqs: requirements.txt
# the {true} construction means this target will not fail even if every
# line pip produces matches the pattern (which is actually a good thing)
	@echo $(PY) -m pip install -r requirements.txt
	@$(PY) -m pip install -r requirements.txt | { grep -v 'already satisfied\|Cleaning up'; true; }
save-pyreqs:
	$(PY) -m pip freeze | sort > requirements.txt

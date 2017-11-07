# Sudoku Solver

## About
* This Django web app is designed to solve sudoku puzzles and uses [sudokuJS]
    [sudokuJS link], and jQuery for front end, and C++ in the back end to implement 
    algorithms. Our application can solve and display sudoku puzzles of sizes 4x4, 
    9x9, and 16x16 with varying difficulties.  

## Requirements
* All that is required to run this web app is Python 3, Django >= 1.11.5, g++, and make.

## Running the project
* To install requirements run `make pyreqs`.
    This is also done automatically when `make run` is called
* To run this project, fork and clone the git repository, and type `make run PORT=<port>`.
    This will compile the C++ program required for running the algorithms and start the
    Django web server. If no port is specified, Django will start the web server on port 8000.

## The Algorithms
* [AC-3][ac3 wiki]

## Authors
* [Adam Jenkins][adam github]
* [Alexander Corley][xandy github]
* [Caleb Alexander][caleb github]

[adam github]:	http://github.com/adamjenkins1
[xandy github]:	http://github.com/archer31
[caleb github]:	http://github.com/calexander13

[ac3 wiki]: https://en.wikipedia.org/wiki/AC-3_algorithm
[sudokuJS link]: https://github.com/pocketjoso/sudokuJS

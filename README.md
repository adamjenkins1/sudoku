# Sudoku Solver

## About
* This Django web app is designed to solve [Sudoku][sudoku link] puzzles and uses 
    [sudokuJS][sudokuJS link], [jQuery][jquery link], and [Bootstrap][bootstrap link] for 
    front end, and C++ in the back end to implement algorithms. Our application can solve 
    and display Sudoku puzzles of sizes 4x4, 
    9x9, and 16x16 with varying difficulties.  

## Requirements
* All that is required to run this web app is [Python 3][python link], 
    [Django][django link] >= 1.11.5, g++, and make. It is also import to have . 
    (current directory) in your PATH.

## Running the project
* To run this project, first fork and clone the git repository. To run this project locally, make sure to set 
  `DEBUG = True` in `project/settings.py`, otherwise the Django web server will not serve the 
  required static files. Once that has been changed, type make run PORT=<port>. This will compile 
  the C++ program required for running the algorithms and start the Django web server. If no port is specified, 
  Django will start the web server on port 8000. 
* To install requirements run `make pyreqs`.
    This is also done automatically when `make run` is called

## The Algorithms
* [AC-3][ac3 wiki]
* [Genetic][genetic wiki]

## Authors
* [Caleb Alexander][caleb github]
* [Alexander Corley][xandy github]
* [Adam Jenkins][adam github]

[adam github]:	https://github.com/adamjenkins1
[xandy github]:	https://github.com/archer31
[caleb github]:	https://github.com/calexander13

[ac3 wiki]: https://en.wikipedia.org/wiki/AC-3_algorithm
[genetic wiki]: https://en.wikipedia.org/wiki/Genetic_algorithm
[sudokuJS link]: https://github.com/pocketjoso/sudokuJS
[sudoku link]: https://en.wikipedia.org/wiki/Sudoku
[jquery link]: https://jquery.com/
[bootstrap link]: https://getbootstrap.com/
[python link]: https://www.python.org/downloads/
[django link]: https://www.djangoproject.com/

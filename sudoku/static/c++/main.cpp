//main.cpp
//Author: Alexander Corley
//11-01-2017
#include "ac3.h"
#include "genetic.h"
#include "board.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "[AI] usage: solver <method> <size> <filename>" << std::endl;
    return 1;
  }
  std::string method = argv[1];
  if (method != "AC3" && method != "Genetic") {
    std::cerr << "[AI] error: invalid method type" << std::endl;
    return 3;
  }
  int size = atoi(argv[2]);
  if (size == 0) {
    std::cerr << "[AI] error: size must be an integer" << std::endl;
    return 2;
  }
  std::string filename = argv[3];
  std::ifstream in(filename);
  Board board(size);
  in >> board;
#ifdef DEBUG
  std::cerr << "[AI] H: " << board.H << std::endl;
#endif
  if (method == "AC3") {
    AC3 solver(size, board);
#ifdef DEBUG
    std::cerr << "[AI] is_solved: " << solver.solve() << std::endl;
#else
    std::cerr << solver.solve() << std::endl;
#endif
    std::cout << solver;
  } else if (method == "Genetic") {
    Genetic genetic(board);
#ifdef DEBUG
    std::cerr << "[AI] is_solved: " << genetic.solve() << std::endl;
#else
    std::cerr << genetic.solve() << std::endl;
#endif
    std::cout << genetic;
  }
}

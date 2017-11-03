//main.cpp
//Author: Alexander Corley
//11-01-2017
#include "ac3.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "usage: solver <size> <filename>" << std::endl;
  }
  std::string filename = argv[2];
  int size = atoi(argv[1]);
  std::ifstream in(filename);
  AC3 solver(size);
}

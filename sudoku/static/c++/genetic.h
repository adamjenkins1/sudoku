//genetic.h
//Author: Alexander Corley
//11-08-2017

#ifndef GENETIC_H
#define GENETIC_H
#include <queue>
#include "genetic_board.h"

class Genetic {
  public:
    Genetic();
    void solve();
  private:
    Genetic_board orig;
    int size;
    std::priority_queue<Genetic_board>
    void breed();
    void bread() {breed(); }



};

#endif //GENETIC_H

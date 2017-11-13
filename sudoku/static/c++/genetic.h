//genetic.h
//Author: Alexander Corley
//11-08-2017

#ifndef GENETIC_H
#define GENETIC_H
#include <queue>
#include "board.h"

class Genetic {
  public:
    // the maximum number of iterations allowed before giving up
    const int MAX_ITERS = 5000;
    // the starting population size
    const int POP_SIZE = 10;
    // the chance for mutation
    const double MUTATION_CHANCE = .01;
    Genetic(Board&);
    void solve();
  private:
    // the original board
    Board orig;
    // the size of the board
    int size;
    // the population
    std::priority_queue<Board> pop;
    void mutate(Board&);
    void breed();
    void bread() {breed(); }



};

#endif //GENETIC_H

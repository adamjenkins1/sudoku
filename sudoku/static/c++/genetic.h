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
    const unsigned int MAX_ITERS = 50000;
    // the starting population size
    const unsigned int POP_SIZE = 10;
    // the chance for mutation
    const int MUTATION_CHANCE = 25;
    Genetic(Board&);
    friend std::ostream& operator<<(std::ostream&, const Genetic&);
    bool solve();
  private:
    // the original board
    Board orig;
    // the size of the board
    int size;
    // the population
    std::priority_queue<Board, std::vector<Board>, std::greater<Board> > pop;
    void mutate(Board&);
    void breed();
    void bread() {breed(); }



};

#endif //GENETIC_H

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
    const unsigned int MAX_ITERS = 5000;
    // the maximum number of iterations with no improvement in H before restarting
    const unsigned int MAX_IDLE_ITERS = 1000;
    // the starting population size
    const unsigned int POP_SIZE = 100;
    // the chance for mutation
    const double MUTATION_CHANCE = 0.25;
    Genetic(const Board&);
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
    void generate_pop();



};

#endif //GENETIC_H

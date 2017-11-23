//hill.h
//Author: Alexander Corley
//11-15-2017

#ifndef HILL_H
#define HILL_H
#include "board.h"
#include <utility>

class Hill {
  public:
    static const int MAX_RETRIES = 15;
    Hill(const Board&);
    friend std::ostream& operator<<(std::ostream&, const Hill&);
    bool solve();
  private:
    Board orig, fin;
    int size;
    std::pair<int, int> get_random_loc();
    std::vector<std::pair<int, int>> valid_locs;

};

#endif //HILL_H

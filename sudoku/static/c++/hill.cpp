//hill.cpp
//Author: Alexander Corley
//11-15-2017
#include "hill.h"
#include "board.h"
#include <cmath>
#include <ctime>
#include <vector>
#include <utility>
#include <algorithm>

Hill::Hill(const Board& board)
  : orig(board)
  , fin(orig.get_size())
  , size(orig.get_size()) {
  std::srand(std::time(0));
  fin = Board::generate_rand(orig);
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (orig.get(row, col) == 0)
        valid_locs.push_back(std::make_pair(row, col));
    }
  }
}

bool Hill::solve() {
  Board best(orig);
  int iters = 0, retries = 0;
  while (fin.H != 0 && retries < MAX_RETRIES) {
    std::pair<int, int> loc = get_random_loc();
    int row = loc.first, col = loc.second;
    std::vector<Board> vals;
    int min = -1, min_val = 0;
    for (int i = 0; i < size; ++i) {
      vals.push_back(fin);
      if (orig.get(row, i) == 0)
        vals[i].swap(row, col, row, i);
      if (vals[i].H < min || min == -1) {
        min = vals[i].H;
        min_val = i;
      }
    }
    fin = vals[min_val];
    if (iters > 1000) {
      fin = Board::generate_rand(orig);
      iters = 0;
      ++retries;
    }
    ++iters;
    if (fin.H < best.H)
      best = fin;
  }
  fin = best;
  return fin.H == 0;
}

std::pair<int, int> Hill::get_random_loc() {
  return valid_locs[std::rand()/RAND_MAX*valid_locs.size()];
}

std::ostream& operator<<(std::ostream& out, const Hill& ob) {
  out << ob.fin << "\n";
  return out;
}

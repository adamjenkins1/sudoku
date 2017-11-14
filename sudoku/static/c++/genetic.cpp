//genetic.cpp
//Author: Alexander Corley
//11-08-2017
#include "genetic.h"
#include "board.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using std::rand;
using std::vector;

/**
 * @brief     constructor for the Genetic Algorithm takes the original board as input
 */
Genetic::Genetic(Board& board)
  : orig(board)
  , size(orig.get_size()) {
}

std::ostream& operator<<(std::ostream& out, const Genetic& ob) {
  if (ob.pop.size() > 0)
    out << ob.pop.top();
  return out;
}

/**
 * @brief     solves the board using a genetic algorithm
 */
bool Genetic::solve() {
//	const float mutation_chance = .01;

	std::srand(std::time(0));

	//generate random population
	for (int i = 0; i < POP_SIZE; ++i) {
		vector<vector<int>> contents(size);
		//generate random board
		for (int row = 0; row < size; ++row) {
      vector<int> vals(size);
			for (int col = 0; col < size; ++col) {
        vals[col] = col+1;
			}
      std::random_shuffle(vals.begin(), vals.end());
      for (int col = 0; col < size; ++col) {
        if (orig.get(row, col) != 0) {
          vals.erase(std::find(vals.begin(), vals.end(), orig.get(row, col)));
          vals.insert(vals.begin()+col, orig.get(row, col));
          
        }
      }
      contents[row] = vals;
		}
		pop.emplace(contents);
	}
  int iters = 0;
  while (pop.top().H != 0 && iters < MAX_ITERS) {
    breed();
    ++iters;
  }
  return pop.top().H == 0;
}

vector<int> generate(int size) {
  int val;
  vector<int> vals;
  for (int i = 0; i < size/3; ++i) {
    val = (rand()%size) + 1;
    if (std::find(vals.begin(), vals.end(), val) != vals.end())
      vals.push_back(val);
  }
  return vals;
}

/**
 * @brief     breeds the top two boards together and puts them back in the population
 */
void Genetic::breed() {
  Board board1 = pop.top(); pop.pop();
  Board board2 = pop.top(); pop.pop();
  board1.trade_rows(generate(size), board2);
  pop.push(board1); pop.push(board2);
}


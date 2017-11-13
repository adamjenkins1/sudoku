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
  : orig(board) {

}

/**
 * @brief     solves the board using a genetic algorithm
 */
void Genetic::solve() {
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
        // i do this method so that i can outright reduce h below 2*size
        // rather than 3*size
        std::random_shuffle(vals.begin(), vals.end());
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


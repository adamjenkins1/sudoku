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
	std::srand(std::time(0));

	//generate random population
	for (unsigned int i = 0; i < POP_SIZE; ++i) {
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
  unsigned int iters = 0;
  while (pop.top().H != 0 && iters < MAX_ITERS) {
    breed();
    ++iters;
  }
#ifdef DEBUG
  std::cerr << "[GE] iters taken: " << iters << "\n";
#endif
  return pop.top().H == 0;
}

/**
 * @brief     return a list of indexes to swap
 */
vector<int> generate(int size) {
  int val;
  vector<int> vals;
  for (int i = 0; i < size/3; ++i) {
    val = rand()%size;
    if (std::find(vals.begin(), vals.end(), val) == vals.end())
      vals.push_back(val);
  }
  return vals;
}

/**
 * @brief     breeds the top two boards together and puts them back in the population
 */
void Genetic::breed() {
  if (pop.size() < POP_SIZE/3+1) return;
  Board board = pop.top(); pop.pop();
  vector<Board> vals;
  for (unsigned int i = 0; i < POP_SIZE/3; ++i) {
    Board man = board, fem = pop.top(); pop.pop();
    man.trade_rows(generate(size), fem);
    mutate(man); mutate(fem);
    vals.push_back(man); vals.push_back(fem);
  }
  for (unsigned int i = 0; i < vals.size(); ++i)
    pop.push(vals[i]);
}

void Genetic::mutate(Board& board) {
  if ((rand() % 100)/100 < MUTATION_CHANCE) {
    int row = rand() % size;
    int col1 = rand() % size;
    int col2 = rand() % size;
    int temp = board.get(row, col1);
    if (orig.get(row, col1) == 0 && orig.get(row, col2) == 0) {
      board.set(row, col1, board.get(row, col2));
      board.set(row, col2, temp);
    }
  }
}


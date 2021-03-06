//genetic.cpp
//Author: Alexander Corley
//11-08-2017
#include "genetic.h"
#include "board.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
//#define DEBUG
using std::rand;
using std::vector;

/**
 * @brief     constructor for the Genetic Algorithm takes the original board as input
 */
Genetic::Genetic(const Board& board)
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

  generate_pop();

  unsigned int iters = 0;
  unsigned int idle_iters = 0;
  int best_h = pop.top().H;
  Board best_board_ever = pop.top();
  int best_h_ever = best_h;

#ifdef DEBUG
  std::cerr << "[GE] starting h: " << best_h_ever << "\n";
#endif

  while (pop.top().H != 0 && iters < MAX_ITERS) {
    if (pop.top().H < best_h) {
      idle_iters = 0;
      best_h = pop.top().H;
    } else if (idle_iters >= MAX_IDLE_ITERS) {
      pop = std::priority_queue<Board, std::vector<Board>, std::greater<Board> >();
      generate_pop();
      best_h = pop.top().H;
    }
    breed();
    if (pop.top().H < best_h_ever) {
      best_h_ever = pop.top().H;
      best_board_ever = pop.top();
    }
    ++iters;
    ++idle_iters;
  }

  if (iters == MAX_ITERS) {
    pop.push(best_board_ever);
  }
#ifdef DEBUG
  std::cerr << "[GE] iters taken: " << iters << "\n";
  std::cerr << "[GE] lowest h found: " << best_h_ever << "\n";
#endif
  return pop.top().H == 0;
}

/**
 * @brief     return a list of indexes to swap
 */
vector<int> generate(int size) {
  int val;
  vector<int> vals;
  int num_of_rows = size/3 == 1 ? 1 : rand()%(size/3 - 1) + 1;
  for (int i = 0; i < num_of_rows; ++i) {
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
  vector<Board> vals;
  for (unsigned int i = 0; i < POP_SIZE/3; ++i) {
    vals.push_back(pop.top()); pop.pop();
  }
  for (unsigned int i = 0; i < vals.size(); ++i) {
    for (unsigned int j = 0; j < vals.size(); ++j) {
      Board man = vals[i], fem = vals[j];
      man.trade_rows(generate(size), fem);
      mutate(man); mutate(fem);
      pop.push(man); pop.push(fem);
    }
  }
  cull();
}

void Genetic::cull() {
  std::priority_queue<Board, std::vector<Board>, std::greater<Board> > tmp;
  for (unsigned int i = 0; i < POP_SIZE; ++i) {
    tmp.push(pop.top()); pop.pop();
  }
  pop = std::priority_queue<Board, std::vector<Board>, std::greater<Board> >();
  for (unsigned int i = 0; i < POP_SIZE; ++i) {
    pop.push(tmp.top()); tmp.pop();
  }
}

/**
 * @brief     generates the random population
 */
void Genetic::generate_pop() {
  for (unsigned int i = 0; i < POP_SIZE; ++i) {
    pop.push(Board::generate_rand(orig));
  }
}

void Genetic::mutate(Board& board) {
  if ((double)rand()/RAND_MAX < MUTATION_CHANCE) {
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


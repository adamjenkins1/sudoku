//genetic.cpp
//Author: Alexander Corley
//11-08-2017
#include "genetic.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using std::rand;
using std::vector;

/**
 * @brief     constructor for the Genetic Algorithm takes the original board as input
 */
Genetic::Genetic(std::vector<std::vector<int> > &board)
  : orig(board) {

}

/**
 * @brief     solves the board using a genetic algorithm
 */
void Genetic::solve() {
	const int pop_size = 15;
	const float mutation_chance = .01;

	std::srand(std::time(0));

	//generate random population
	for (int i = 0; i < pop_size; ++i) {
		vector<vector<int>> contents(size, vector<int>(size));
		//generate random board
		for (int row = 0; row < size; ++row) {
			for (int col = 0; col < size; ++col) {
				if (orig.board[row][col] >= 1)
					contents[row][col] = orig.board[row][col];
				else
					contents[row][col] = rand() % size + 1;
			}
		}
		boards.emplace(contents);
	}

	breed();

	//to be continued ...
}

/**
 * @brief     breeds the top two boards together and puts them back in the population
 */
void Genetic::breed() {

}


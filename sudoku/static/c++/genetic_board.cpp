//genetic_board.cpp
//Author: Alexander Corley
//11-08-2017
#include "genetic_board.h"
#include <vector>
#include <cassert>

/**
 * @brief     default constructor for a board
 */
Genetic_board::Genetic_board(const std::vector<std::vector<int> > &board) {

}

/**
 * @brief     gets the values from a column
 */
std::vector<int> Genetic_board::get_col() {

  return std::vector<int>();
}

/**
 * @brief     gets the values from a row
 */
std::vector<int> Genetic_board::get_row() {

  return std::vector<int>();
}

/**
 * @brief     sets a column with values
 */
void Genetic_board::set_col(std::vector<int> vals) {
  assert(vals.size() == size);

}

/**
 * @brief     sets a row with values
 */
void Genetic_board::set_row(std::vector<int> vals) {
  assert(vals.size() == size);

}

/**
 * @brief     trades columns with the other board
 */
void Genetic_board::trade_cols(std::vector<int> indexes, Genetic_board& other) {

}

/**
 * @brief     trades rows with the other board
 */
void Genetic_board::trade_rows(std::vector<int> indexes, Genetic_board& other) {

}

/**
 * @brief     calculates the H value for this board
 * @retur     a value, H, between [0, 3*sqrt(size)]
 */
void Genetic_board::h() {

}

/**
 * @brief     compare operator for use with priority_queue
 */
bool operator<(const Genetic_board& lhs, const Genetic_board& rhs) {
  return lhs.H < rhs.H;
}


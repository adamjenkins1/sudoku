//genetic_board.cpp
//Author: Alexander Corley
//11-08-2017
#include "genetic_board.h"
#include <vector>
#include <cassert>
#include <algorithm>

/**
 * @brief     default constructor for a board
 */
Genetic_board::Genetic_board(const std::vector<std::vector<int> > &board)
  : board(board)
  , size(board.size()) {
  h();
}

/**
 * @brief     gets the values from a column
 */
std::vector<int>& Genetic_board::get_col(int i) {

  return std::vector<int>();
}

/**
 * @brief     gets the values from a row
 */
std::vector<int>& Genetic_board::get_row(int i) {

  return std::vector<int>();
}

/**
 * @brief     sets a column with values
 */
void Genetic_board::set_col(int i, const std::vector<int>& vals) {
  assert(vals.size() == size);

}

/**
 * @brief     sets a row with values
 */
void Genetic_board::set_row(int i, const std::vector<int>& vals) {
  assert(vals.size() == size);

}

/**
 * @brief     trades columns with the other board
 */
void Genetic_board::trade_cols(std::vector<int>& indexes, Genetic_board& other) {
  for (auto index: indexes) {
    for (int i = 0; i < size; ++i) {
      std::swap(board[i][index], other.board[i][index]);
    }
  }
}

/**
 * @brief     trades rows with the other board
 */
void Genetic_board::trade_rows(std::vector<int>& indexes, Genetic_board& other) {
  for (auto index: indexes) {
    board[index].swap(other[index]);
  }
}

/**
 * @brief     calculates the H value for this board
 * @retur     a value, H, between [0, 3*sqrt(size)]
 */
void Genetic_board::h() {
  H = 0;
  //check to see if the rows and columns are all valid
  std::vector<bool> rowset(size, 0), colset(size, 0);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (board[i][j].value)
        rowset[board[i][j].value-1] = 1;
      if (board[j][i].value)
        colset[board[j][i].value-1] = 1;
    }
    if (!all(rowset)) H++;
    if (all(colset)) H++;
    rowset.clear(); colset.clear();
  }

  std::vector<bool> block(size, 0);
  int ssize = std::sqrt(size);
  for (int brow = 0; brow < ssize; ++brow) {
    for (int bcol = 0; bcol < ssize; ++bcol) {
      for (int row = 0; row < ssize; ++row) {
        for (int col = 0; col < ssize; ++col) {
          if (board[brow*ssize+row][bcol*ssize+col].value)
            block[board[brow*ssize+row][bcol*ssize+col]].value-1] = 1;
        }
      }
      if (!all(block)) H++;
      block.clear();
    }
  }
}

/**
 * @brief     compare operator for use with priority_queue
 */
bool operator<(const Genetic_board& lhs, const Genetic_board& rhs) {
  return lhs.H < rhs.H;
}


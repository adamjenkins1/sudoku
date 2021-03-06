//board.cpp
//Author: Alexander Corley
//11-08-2017
#include "board.h"
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

/**
 * @brief     default constructor for a board
 */
Board::Board(const std::vector<std::vector<int> > &board)
  : board(board)
  , size(board.size()) {
  h();
}

Board::Board(int size)
  : board(size, std::vector<int>(size, 0))
  , size(size) {}



/**
 * @brief     print the board
 */
std::ostream& operator<<(std::ostream& out, const Board& ob) {
  ob.print_board(out);
  return out;
}

/**
 * @brief     output the board
 *            does the same thing as the extraction operator
 */
void Board::print_board(std::ostream& out) const {
#ifdef DEBUG
  std::cerr << "[AI] H: " << H << "\n";
#endif
  for (unsigned int row = 0; row < size; ++row) {
    for (unsigned int col = 0; col < size; ++col) {
      if (get(row, col) != 0)
        out << get(row, col) << ' ';
      else
        out << "- ";
    }
#ifdef DEBUG
    out << "\n";
#endif
  }
  out << "\n";
}

std::istream& operator>>(std::istream& in, Board& ob) {
  int val;
  for (unsigned int row = 0; row < ob.size; ++row) {
    for (unsigned int col = 0; col < ob.size; ++col) {
      in >> val;
      ob.board[row][col] = val;
    }
  }
  ob.h();
  return in;
}

/**
 * @brief     generates a randomized board that respects the values of orig
 */
Board Board::generate_rand(Board& orig) {
  int size = orig.get_size();
  Board board(size);

  std::vector<int> vals;
  for (int row = 0; row < size; ++row) {
    vals.resize(size);
    for (int col = 0; col < size; ++col) {
      vals[col] = col+1;
    }
    //remove all taken values
    for (int col = 0; col < size; ++col) {
      if (orig.get(row, col) != 0) {
        vals.erase(std::find(vals.begin(), vals.end(), orig.get(row, col)));
      }
    }
    int val_i = 0; //what we'll insert at next available space
    std::random_shuffle(vals.begin(), vals.end());
    for (int col = 0; col < size; ++col) {
      if (orig.get(row, col) != 0) {
        board.board[row][col] = orig.get(row, col);
      } else {
        board.board[row][col] = vals[val_i];
        val_i++;
      }
    }
  }

  board.h();
  return board;
}

void Board::set(int row, int col, int val) {
  board[row][col] = val;
  h();
}

int Board::get(int row, int col) const {
  return board[row][col];
}

void Board::swap(int row1, int col1, int row2, int col2) {
  int val = get(row1, col1);
  board[row1][col1] = get(row2, col2);
  board[row2][col2] = val;
  h();
}

/**
 * @brief     gets the values from a column
 */
std::vector<int> Board::get_col(int index) const {
  std::vector<int> vec;
  for (unsigned int i = 0; i < size; ++i) {
    vec.push_back(board[i][index]);
  }
  return vec;
}

/**
 * @brief     gets the values from a row
 */
std::vector<int> Board::get_row(int index) const {
  return board[index];
}

/**
 * @brief     sets a column with values
 */
void Board::set_col(int index, const std::vector<int>& vals) {
  assert(vals.size() == size);
  for (unsigned int i = 0; i < size; ++i) {
    board[index][i] = vals[i];
  }
  h();
}

/**
 * @brief     sets a row with values
 */
void Board::set_row(int index, const std::vector<int>& vals) {
  assert(vals.size() == size);
  for (unsigned int i = 0; i < size; ++i) {
    board[i][index] = vals[i];
  }
  h();
}

/**
 * @brief     trades columns with the other board
 */
void Board::trade_cols(std::vector<int> indexes, Board& other) {
  for (auto index: indexes) {
    for (unsigned int i = 0; i < size; ++i) {
      std::swap(board[i][index], other.board[i][index]);
    }
  }
  h();
  other.h();
}

/**
 * @brief     trades rows with the other board
 */
void Board::trade_rows(std::vector<int> indexes, Board& other) {
  for (auto index: indexes) {
    board[index].swap(other.board[index]);
  }
  h();
  other.h();
}

/**
 * @brief     returns false if any value in the vector is false
 */
bool all(std::vector<bool> vec) {
  for (auto it = vec.begin(); it != vec.end(); ++it) {
    if (!*it) return false;
  }
  return true;
}

void clear(std::vector<bool> vec) {
  for (unsigned int i = 0; i < vec.size(); ++i) {
    vec[i] = 0;
  }
}

/**
 * @brief     calculates the H value for this board
 */
void Board::h() {
  H = 0;
  if (USE_ALTERNATE_H) { //this method counts collisions
    for (unsigned int i = 0; i < size; ++i) {
      for (unsigned int j = 0; j < size; ++j) {
        for (unsigned int j1 = j + 1; j1 < size; ++j1) {
          if (board[i][j] == board[i][j1])
            H++; //collision in a row
          if (board[j][i] == board[j1][i])
            H++; //collision in a col
        }
      }
    }

    std::vector<int> block(size, 0);
    int ssize = std::sqrt(size);
    for (int brow = 0; brow < ssize; ++brow) {
      for (int bcol = 0; bcol < ssize; ++bcol) {
        for (int row = 0; row < ssize; ++row) {
          for (int col = 0; col < ssize; ++col) {
            if (board[brow*ssize+row][bcol*ssize+col]) {
              H += block[board[brow*ssize+row][bcol*ssize+col]-1];
              block[board[brow*ssize+row][bcol*ssize+col]-1]++;
            }
          }
        }
        std::fill(block.begin(), block.end(), 0);
      }
    }
  } else {
    //check to see if the rows and columns are all valid
    std::vector<bool> rowset(size), colset(size);
    for (unsigned int i = 0; i < size; ++i) {
      for (unsigned int j = 0; j < size; ++j) {
        if (board[i][j])
          rowset[board[i][j]-1] = 1;
        if (board[j][i])
          colset[board[j][i]-1] = 1;
      }
      if (!all(rowset)) H++;
      if (!all(colset)) H++;
      std::fill(rowset.begin(), rowset.end(), false);
      std::fill(colset.begin(), colset.end(), false);
    }

    std::vector<bool> block(size, 0);
    int ssize = std::sqrt(size);
    for (int brow = 0; brow < ssize; ++brow) {
      for (int bcol = 0; bcol < ssize; ++bcol) {
        for (int row = 0; row < ssize; ++row) {
          for (int col = 0; col < ssize; ++col) {
            if (board[brow*ssize+row][bcol*ssize+col])
              block[board[brow*ssize+row][bcol*ssize+col]-1] = 1;
          }
        }
        if (!all(block)) H++;
        std::fill(block.begin(), block.end(), false);
      }
    }
  }
}

/**
 * @brief     compare operator for use with priority_queue
 */
bool operator<(const Board& lhs, const Board& rhs) {
  return lhs.H < rhs.H;
}

/**
 * @brief     compare operator for use with priority_queue
 */
bool operator>(const Board& lhs, const Board& rhs) {
  return lhs.H > rhs.H;
}


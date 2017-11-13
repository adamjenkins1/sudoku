//ac3.cpp
//Author: Alexander Corley
//10-31-2017
#include "ac3.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

/**
 * @brief     Constructor
 * @param     size:       the size of the board
*/
AC3::AC3(int size, Board board)
  : size(size)
  , vars(size*size, size)
  , board(board) {
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      Variable &var = vars[row*size+col];
      var.row = row; var.col = col;
      if (board.get(row, col) != 0) {
        var.domain.clear();
        var.domain.push_back(board.get(row, col));
      }
      std::vector<Edge> &cons = var.connections;
      int sqrt_size = std::sqrt(size);
      int block_row = row/sqrt_size, block_col = col/sqrt_size;
      for (int row1 = 0; row1 < size; ++row1) {
        for (int col1 = 0; col1 < size; ++col1) {
          if (row == row1 && col == col1);
          else if (block_row == row1/sqrt_size && block_col == col1/sqrt_size) {
            cons.emplace_back();
            (*cons.rbegin()).left = &var;
            (*cons.rbegin()).right = &vars[row1*size+col1];
          }
          else if (row == row1) {
            cons.emplace_back();
            (*cons.rbegin()).left = &var;
            (*cons.rbegin()).right = &vars[row1*size+col1];
          }
          else if (col == col1) {
            cons.emplace_back();
            (*cons.rbegin()).left = &var;
            (*cons.rbegin()).right = &vars[row1*size+col1];
          }
        }
      }
    }
  }
}

/**
 * @brief     Variable consturctor
 */
AC3::Variable::Variable(int size, int row, int col)
  : row(row) 
  , col(col) {
  for (int i = 1; i <=size; ++i) {
    domain.push_back(i);
  }
}

/**
 * @brief     print the board
 */
std::ostream& operator<<(std::ostream& out, const AC3& ob) {
  out << ob.board << "\n";
  return out;
}

/**
 * @brief     uses all the power under the sun to solve the problem
 */
bool AC3::solve() {
  std::queue<Edge> q;

  //fill in queue with initial arcs
  for (auto var = vars.begin(); var != vars.end(); ++var) {
    for (auto edge = var->connections.begin(); edge != var->connections.end(); ++edge) {
      q.push(*edge);
    }
  }
  //backtracking stack
  std::stack<BackItem> bck;
  while (!q.empty()) {
    Edge edge = q.front();
    q.pop();
    // reduce based on the edge
    bool changed = evaluate(edge);

    //check if we need to guess
    if (q.empty()) {
      Variable *best_var = nullptr;
      int best_i;
      //get best unfinished var (smallest domain > 1)
      for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
          if (vars[row*size+col].domain.size() > 1) {
            if (!best_var || vars[row*size+col].domain.size() < best_var->domain.size()) {
              best_var = &vars[row*size+col];
              best_i = row*size+col;

              if (best_var->domain.size() == 2)
                break;
            }
          }
        }
      }

      //if there are slots left to fill, guess
      if (best_var) {
        //add current state to the stack
        bck.emplace(board, vars, best_i, 0);

        //choose first value in the domain of best_var
        int val = best_var->domain[0];
        best_var->domain.clear();
        best_var->domain.push_back(val);
        board.set(best_var->row, best_var->col, val);

        //add all connections of best_var to the queue
        queue_neighbors(*best_var, q);

        continue;
      }
    }
    // if left didnt change then try the next edge
    if (!changed) continue;
    
    //if need to backtrack
    if (edge.left->domain.size() < 1) {
      if (bck.empty()) {
        //unsolvable
        return false;
      } else {
        //backtrack:

        BackItem &bck_item = bck.top();
        vars = bck_item.vars;
        board = bck_item.board;

        bck.pop();

        auto &affected_var = vars[bck_item.var_choice_i];
        auto &affected_domain = affected_var.domain;
        //remove the failed guess from the domain
        affected_domain.erase(affected_domain.begin() + bck_item.var_domain_choice_i);

        if (affected_domain.size() == 1)
          board.set(affected_var.row, affected_var.col, affected_domain[0]);

        //add all connections of affected_var to the queue
        queue_neighbors(affected_var, q);

        continue;
      }
    }

    //if domain size of x decreased then add relavent edges to q

    if (edge.left->domain.size() == 1) {
      board.set(edge.left->row, edge.left->col, edge.left->domain[0]);
    }
    for (unsigned int i = 0; i < edge.left->connections.size(); ++i) {
      Variable *neighbor = edge.left->connections[i].right;

      if (neighbor != edge.right && board.get(edge.right->row, edge.right->col) != 0) {
        q.emplace();
        q.back().left = neighbor;
        q.back().right = edge.left;
      }
    }
  }
  solved = is_solved();
  board.set(0,0,board.get(0,0));
  return solved;
}

/**
 * @brief     returns true if the puzzle is solved, false otherwise
 */
bool AC3::is_solved() {
  return board.H == 0;
}

/**
 * @brief     evaluate an edge to restrict left
 */
bool AC3::evaluate(Edge& edge) {
  //restrict domain of edge.left based on edge.right
  auto it = std::find(edge.left->domain.begin(), edge.left->domain.end(), board.get(edge.right->row, edge.right->col));
  //if left's domain contains edge.right->value
  if (it != edge.left->domain.end()) {
    // remove from left's domain
    edge.left->domain.erase(it);
    return true;
  }
  return false;
}

/**
 * @brief     add arcs to the queue based on the fact var changed its domain
 */
void AC3::queue_neighbors(Variable& var, std::queue<Edge>& q) {
  for (unsigned int i = 0; i < var.connections.size(); ++i) {
    Variable *neighbor = var.connections[i].right;

    q.emplace();
    q.back().left = neighbor;
    q.back().right = &var;
  }
}


//ac3.cpp
//Author: Alexander Corley
//10-31-2017
#include "ac3.h"
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
AC3::AC3(int size)
  : size(size)
  , vars(size*size, size) {
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      Variable &var = vars[row*size+col];
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
AC3::Variable::Variable(int size) {
  for (int i = 1; i <=size; ++i) {
    domain.push_back(i);
  }
}

/**
 * @brief     read in the variables then the edges
 */
std::istream& operator>>(std::istream& in, AC3& ob) {
  ob.read_vars(in);
  return in;
}

/**
 * @brief     read in the variables
 */
void AC3::read_vars(std::istream& in) {
  int val;
  for (int i = 0; i < size*size; ++i) {
    in >> val;
    if (val == 0) continue;
    vars[i].value = val;
    vars[i].domain.clear();
    vars[i].domain.push_back(val);
  }
}

/**
 * @brief     print all the variables
 */
std::ostream& operator<<(std::ostream& out, const AC3& ob) {
  ob.print_vars(out);
  return out;
}

/**
 * @brief     output the variables
 *            does the same thing as the extraction operator
 */
void AC3::print_vars(std::ostream& out) const {
  for (int row = 0; row < size; ++row) {
    for (int col = 0; col < size; ++col) {
      if (vars[row*size+col].domain.size() == 1)
        out << vars[row*size+col].value << ' ';
      else
        out << "- ";
    }
#ifdef DEBUG
    out << "\n";
#endif
  }
  out << "\n";
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
        bck.emplace(vars, best_i, 0);

        //choose first value in the domain of best_var
        int val = best_var->domain[0];
        best_var->domain.clear();
        best_var->domain.push_back(val);
        best_var->value = val;

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

        bck.pop();

        auto &affected_var = vars[bck_item.var_choice_i];
        auto &affected_domain = affected_var.domain;
        //remove the failed guess from the domain
        affected_domain.erase(affected_domain.begin() + bck_item.var_domain_choice_i);

        if (affected_domain.size() == 1)
          affected_var.value = affected_domain[0];

        //add all connections of affected_var to the queue
        queue_neighbors(affected_var, q);

        continue;
      }
    }

    //if domain size of x decreased then add relavent edges to q

    if (edge.left->domain.size() == 1) {
      edge.left->value = edge.left->domain[0];
    }
    for (unsigned int i = 0; i < edge.left->connections.size(); ++i) {
      Variable *neighbor = edge.left->connections[i].right;

      if (neighbor != edge.right && edge.right->value != -1) {
        q.emplace();
        q.back().left = neighbor;
        q.back().right = edge.left;
      }
    }
  }
  solved = is_solved();
  return solved;
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

/**
 * @brief     returns true if the puzzle is solved, false otherwise
 */
bool AC3::is_solved() {
  //check to see if the rows and columns are all valid
  std::vector<bool> rowset(size, 0), colset(size, 0);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (vars[i*size+j].value)
        rowset[vars[i*size+j].value-1] = 1;
      if (vars[j*size+i].value)
        colset[vars[j*size+i].value-1] = 1;
    }
    if (!all(rowset) || !all(colset)) return false;
    rowset.clear(); colset.clear();
  }


  std::vector<bool> block(size, 0);
  int ssize = std::sqrt(size);
  for (int brow = 0; brow < ssize; ++brow) {
    for (int bcol = 0; bcol < ssize; ++bcol) {
      for (int row = 0; row < ssize; ++row) {
        for (int col = 0; col < ssize; ++col) {
          if (vars[(brow*ssize+row)*size+(bcol*ssize+col)].value)
            block[vars[(brow*ssize+row)*size+(bcol*ssize+col)].value-1] = 1;
        }
      }
      if (!all(block)) return false;
      block.clear();
    }
  }
  return true;
}

/**
 * @brief     evaluate an edge to restrict left
 */
bool AC3::evaluate(Edge& edge) {
  //restrict domain of edge.left based on edge.right
  auto it = std::find(edge.left->domain.begin(), edge.left->domain.end(), edge.right->value);
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


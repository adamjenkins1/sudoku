//ac3.cpp
//Author: Alexander Corley
//10-31-2017
#include "ac3.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

/**
 * @brief     default constructor
 */
AC3::AC3()
  : AC3(9) {}

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
 * @brief     returns the size of the variable's domain or 1 if value is set
*/
int AC3::Variable::domain_size() const {
  return (value == -1) ? domain.size() : 1;
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
  for (auto it = vars.begin(); it != vars.end(); ++it) {
    if (it->domain_size() == 1)
      out << it->value << ' ';
    else
      out << "- ";
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
  // add back tracking here
  while (!q.empty()) {
    Edge edge = q.front();
    q.pop();
    // reduce based on the edge
    bool changed = evaluate(edge);
    // if the left only has one value left then set value
    if (edge.left->domain_size() < 1)
      return false;

    //if domain size of x decreased then add relavent edges to q
    if (changed) {
      if (edge.left->domain_size() == 1) {
        edge.left->value = edge.left->domain[0];
      }
      for (unsigned int i = 0; i < edge.left->connections.size(); ++i) {
        Variable *neighbor = edge.left->connections[i].right;

        if (neighbor != edge.right) {
          Edge newEdge;
          newEdge.left = neighbor;
          newEdge.right = edge.left;
          
          q.push(newEdge);
        }
      }
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


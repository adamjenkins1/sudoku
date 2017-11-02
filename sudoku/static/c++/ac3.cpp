//ac3.cpp
//Author: Alexander Corley
//10-31-2017
#include "ac3.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/**
 * @brief     returns the size of the variable's domain or 1 if value is set
*/
int AC3::Variable::domain_size() {
  return (value == -1) ? domain.size() : 1;
}

/**
 * @brief     read in the variables then the edges
 */
std::istream& AC3::operator>>(std::istream& in) {
  return in;
}

/**
 * @brief     read in the variables
 *            does the first half of the extraction operator
 */
void AC3::read_vars(std::istream& in) {

}

/**
 * @brief     read in the edges
 *            does the second half of the extraction operator
 */
void AC3::read_edges(std::istream& in) {

}

/**
 * @brief     print all the variables
 */
std::ostream& AC3::operator<<(std::ostream& out) {
  return out;
}

/**
 * @brief     output the variables
 *            does the same thing as the extraction operator
 */
void AC3::print_vars(std::ostream& out) {

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


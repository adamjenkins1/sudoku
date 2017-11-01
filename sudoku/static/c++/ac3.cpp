//ac3.cpp
//Author: Alexander Corley
//10-31-2017
#include "ac3.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

/**
 * @brief     read in the variables then the edges
 */
std::istream& AC3::operator>>(std::istream& in) {

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

  while (!q.empty()) {
    Edge edge = q.front();
    q.pop();

    int oldDomainSize = edge.left->value == -1 ? (int) edge.left->domain.size() : 1;

    //restrict domain of edge.left based on edge.right
    if (oldDomainSize == 1) {
      auto it = std::find(edge.left->domain.begin(), edge.left->domain.end(), edge.right->value);
      //if left's domain contains edge.right->value, then remove from left's domain
      if (it != edge.left->domain.end()) {
        edge.left->domain.erase(it);
      }

      if ((int) edge.left->domain.size() == 1)
        edge.left->value = edge.left->domain[0];
    }

    int newDomainSize = edge.left->value == -1 ? (int) edge.left->domain.size() : 1;

    if (newDomainSize == 0)
      return false;

    //if domain size of x decreased then add relavent edges to q
    if (newDomainSize < oldDomainSize) {
      for (int i = 0; i < (int) edge.left->connections.size(); ++i) {
        Variable * neighbor = edge.left->connections[i].right;

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

}


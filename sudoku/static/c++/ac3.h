//ac3.h
//Author: Alexander Corley
//10-31-2017

#ifndef AC3_H
#define AC3_H

#include <vector>
#include <iostream>


class AC3 {
  public:
    // read in all possible variables
    std::istream& operator>>(std::istream&);
    // read in the variables (does the first half of the extraction operator)
    void read_vars(std::istream&);
    // read in the edges (does the second half of the extraction operator)
    void read_edges(std::istream&);
    // output all variables
    std::ostream& operator<<(std::ostream&);
    // print out the variables (does the same thing as the insertion operator)
    void print_vars(std::ostream&);
    // attempt to solve the problem
    bool solve();
  private:
    struct Variable;
    // struct representing an edge edges have to be unidirectional
    struct Edge {
      // the variables that are connected by this edge
      Variable *left, *right;
    };
    // struct representing a variable, its relations and possible values
    struct Variable {
      // vector of edges connecting to other variables
      std::vector<Edge> connections;
      // the possible values of this variable
      vector<int> domain;
      // the value of this variable
      // (if this is set then domain should be ignored)
      int value = -1;
    };
    // vector of all variables (variables contain the edges)
    vector<Variable> vars;
    // whether all variables have a value
    bool solved = false;
    // evaluates an edge to make 
    bool evaluate(Edge&);
    
};

#endif //AC3_H

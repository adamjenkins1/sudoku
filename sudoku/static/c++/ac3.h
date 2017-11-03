//ac3.h
//Author: Alexander Corley
//10-31-2017

#ifndef AC3_H
#define AC3_H

#include <vector>
#include <iostream>


class AC3 {
  public:
    AC3();
    AC3(int);
    // read in all possible variables
    friend std::istream& operator>>(std::istream&, AC3&);
    // read in the variables
    void read_vars(std::istream&);
    // output all variables
    friend std::ostream& operator<<(std::ostream&, const AC3&);
    // print out the variables (does the same thing as the insertion operator)
    void print_vars(std::ostream&) const;
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
      Variable(int);
      // vector of edges connecting to other variables
      std::vector<Edge> connections;
      // the possible values of this variable
      std::vector<int> domain;
      // the value of this variable
      // (if this is set then domain should be ignored)
      int value = -1;
      int domain_size() const ;
    };
    // the size of the sudoku board
    int size;
    // vector of all variables (variables contain the edges)
    std::vector<Variable> vars;
    // whether all variables have a value
    bool solved = false;
    // evaluates an edge to make 
    bool evaluate(Edge&);
    
};

#endif //AC3_H

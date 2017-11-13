//ac3.h
//Author: Alexander Corley
//10-31-2017

#ifndef AC3_H
#define AC3_H

#include "board.h"
#include <vector>
#include <queue>
#include <iostream>


class AC3 {
  public:
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
    AC3() : AC3(9) {}
    struct Variable;
    // struct representing an edge edges have to be unidirectional
    struct Edge {
      // the variables that are connected by this edge
      Variable *left, *right;
    };
    // struct representing a variable, its relations and possible values
    struct Variable {
      Variable(int, int, int);
      Variable(int size) : Variable(size, 0, 0) {}
      int row, col;
      // vector of edges connecting to other variables
      std::vector<Edge> connections;
      // the possible values of this variable
      std::vector<int> domain;
      // the value of this variable
      // (if this is set then domain should be ignored)
    };
    //stored in the backtracking stack
    struct BackItem {
      Board board;
      std::vector<Variable> vars;
      //the index of the var whose value was guessed
      int var_choice_i;
      //the index into the var's domain
      int var_domain_choice_i;

      BackItem(Board board, std::vector<Variable> vars, int var_choice_i, 
        int var_domain_choice_i)
          : board(board)
          , vars(vars)
          , var_choice_i(var_choice_i)
          , var_domain_choice_i(var_domain_choice_i) {}
    };
    // the size of the sudoku board
    int size;
    // vector of all variables (variables contain the edges)
    std::vector<Variable> vars;
    // whether all variables have a value
    bool solved = false;
    Board board;
    bool evaluate(Edge&);
    void queue_neighbors(Variable&, std::queue<Edge>&);
    bool is_solved();
    
    
};

#endif //AC3_H

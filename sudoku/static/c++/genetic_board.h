//genetic_board.h
//Author: Alexander Corley
//11-08-2017

#ifndef GENETIC_BOARD_H
#define GENETIC_BOARD_H
#include <vector>

//this class just holds boards for the genetic algorithm to play with

class Genetic_board {
  public:
    Genetic_board(const std::vector<std::vector<int> >&);
    std::vector<int> get_col();
    std::vector<int> get_row();
    void set_col(std::vector<int>);
    void set_row(std::vector<int>);
    void trade_cols(std::vector<int>, Genetic_board&);
    void trade_rows(std::vector<int>, Genetic_board&);
    friend bool operator<(const Genetic_board&, const Genetic_board&);
    int H;
  private:
    std::vector<std::vector<int> > board;
    unsigned int size;
    void h();
};

#endif //GENETIC_BOARD_H

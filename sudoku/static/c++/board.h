//board.h
//Author: Alexander Corley
//11-08-2017

#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>

#define USE_ALTERNATE_H true

//this class just holds boards for the genetic algorithm to play with

class Board {
  public:
    Board(const std::vector<std::vector<int> >&);
    Board(int);
    int get_size() const {return size; }
    void set(int, int, int);
    int get(int, int) const;
    void swap(int, int, int, int);
    std::vector<int> get_col(int) const;
    std::vector<int> get_row(int) const;
    void set_col(int, const std::vector<int>&);
    void set_row(int, const std::vector<int>&);
    void trade_cols(std::vector<int>, Board&);
    void trade_rows(std::vector<int>, Board&);
    friend bool operator<(const Board&, const Board&);
    friend bool operator>(const Board&, const Board&);
    friend std::ostream& operator<<(std::ostream& out, const Board& ob);
    friend std::istream& operator>>(std::istream& in, Board& ob);
    void print_board(std::ostream& out) const;
    static Board generate_rand(Board& board);
    int H;
    //whether it should use a alternate fitness function
  private:
    std::vector<std::vector<int> > board;
    unsigned int size;
    void h();
};

#endif //BOARD_H

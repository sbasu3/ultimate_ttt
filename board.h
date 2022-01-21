#ifndef __BOARD
#define __BOARD

#include "utils.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Board{
protected:
  std::string _string_state;
  std::size_t hash;
  State __state;
  MacroState __major;
  MiniState __mini;
public:
  Board();
  ~Board();
  Board(const Board &B);
  void setStringFromState(void);
  void setStateFromString(std::string &minor);
  void setMajorStateFromString(std::string &major);
  void setstate(const int &row, const int &col , const int8_t color);
  void setbigstate(const int &row, const int &col , const int8_t color);
  inline State getState(void){ return __state;};
  inline MacroState getMacroState(void){ return __major;};
  std::size_t getHash();
  Squares getWinner();
  std::vector<int> getMacroCells();
  std::vector<Move> getMoves();

  bool ValidMove(Move m);



};



#endif

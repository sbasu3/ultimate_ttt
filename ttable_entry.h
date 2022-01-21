#ifndef TTABLE_ENTRY_H
#define TTABLE_ENTRY_H

#include<iostream>

#define EXACT 1024
#define LOWERBOUND -2048
#define UPPERBOUND 2048

class TTableEntry
{
  private:

    std::size_t hash;
    //int alpha;
    //int beta;
    int value;
    int flag;
    int depth;

  public:
    TTableEntry();
    TTableEntry(std::size_t hash,  int value, int depth ,int flag);
    std::size_t get_hash();
    int getdepth(void);
    bool is_valid();
    bool is_lowerbound();
    bool is_upperbound();
    bool is_exact();
    //bool is_within_cutoff(int alpha, int beta, int depth);
    int get_value();
};
#endif

#ifndef TTABLE_H
#define TTABLE_H

#include <iostream>
#include <math.h>

const int TTABLE_SIZE = 0x7fffff;
class TTableEntry;

class TTable
{
  private:
    static TTableEntry entries[TTABLE_SIZE];
  public:
    static TTableEntry * lookup(std::size_t hash);
    static void save_entry(TTableEntry entry);
};
#endif

#include "ttable.h"
#include "ttable_entry.h"

TTableEntry TTable::entries[TTABLE_SIZE];

TTableEntry * TTable::lookup(std::size_t hash)
{
  int index = hash & 0x7fffff; // for < pow(2, 22)
  if (entries[index].is_valid()) {
    //std::cerr<<"index::"<<index<<std::endl;
    return &(entries[index]);
  }
  else
   return NULL;
}

void TTable::save_entry(TTableEntry entry)
{
  int index = entry.get_hash() & 0x7fffff;
  entries[index] = entry;
}

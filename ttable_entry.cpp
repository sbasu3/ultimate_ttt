#include "ttable_entry.h"

TTableEntry::TTableEntry()
{
  hash = value = 0;
  depth = 0;
  flag = -1;
}

TTableEntry::TTableEntry(std::size_t hash, int value,int depth , int flag)
{
  this->hash = hash;
  this->value = value;
  this->depth = depth;
  this->flag = flag;
}

std::size_t TTableEntry::get_hash()
{
  return hash;
}

bool TTableEntry::is_valid()
{
  return ((flag  == EXACT) || (flag == LOWERBOUND) ||( flag == UPPERBOUND));
}


int TTableEntry::get_value()
{
  return value;
}

int TTableEntry::getdepth(void){
    return depth;
}

bool TTableEntry::is_exact(){
  return (flag == EXACT);
}

bool TTableEntry::is_upperbound(void){
  return (flag == UPPERBOUND);
}

bool TTableEntry::is_lowerbound(void){
  return (flag == LOWERBOUND);
}

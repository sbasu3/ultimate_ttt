#include "squares.h"

Squares::Squares(Player p){

  this->color = p.getColor();

}

Squares::Squares(int8_t c){
  this->color = c;
}

Squares::Squares(){
  color = '*';    // * denotes empty and playable
}
bool Squares::is_current_square(void){

  if(color == '*')
    return true;
  else
    return false;
}

Squares Squares::operator =(Player s){

  this->color = s.getColor();

  return *this;
}
Squares Squares::operator =(int8_t s){

  this->color = s;

  return *this;
}
bool operator ==(const Squares &s , const Squares &r){
  return (s.color == r.color) ? true : false;
}
bool operator !=(const Squares &s , const Squares &r){
  return (s.color != r.color) ? true : false;
}

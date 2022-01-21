#include "player.h"


Player::Player(){

  color = 0;

}

Player::Player(int8_t c){

  color = c;

}
Player Player::operator =(const Player &s){

  this->color = s.color;

  return *this;
}

Player Player::operator =(const int8_t &c){

  this->color = c;

  return *this;
}

bool operator ==(const Player &p , const Player &q){

  if(q.color == p.color)
    return true;
  else
    return false;

}

bool operator !=(const Player &p , const Player &q ){

    if(q.color != p.color)
      return true;
    else
      return false;
}

Player operator ~(const Player &p){

  Player q;

  q.color = -p.color;

  return q;

}
bool Player::is_a_player(void){

  if(( color == 1) || (color == -1))
    return true;
  else
    return false;
}

bool Player::is_empty(void){

  return (color == 0)? true : false;
}

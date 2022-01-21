#ifndef __SQUARES
#define __SQUARES

#include "player.h"

class Squares : public Player {
  public:
    Squares();
    Squares(int8_t c);
    Squares(Player p);
    bool is_current_square(void);
    Squares operator=(Player s);
    Squares operator=(int8_t c);
    friend bool operator ==(const Squares &s , const Squares &r);
    friend bool operator !=(const Squares &s , const Squares &r);
};

#endif

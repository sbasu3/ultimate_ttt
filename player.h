#ifndef __PLAYER
#define __PLAYER

#include<cstdint>


class Player {
    protected:
        int8_t  color;     //color can be -1,1,0 [un-occupied]
    public:
        Player();
        Player(int8_t c);
        bool is_a_player(void);
        bool is_empty(void);
        const inline int8_t getColor(void){ return color;};
        Player operator =(const Player &s);
        Player operator =(const int8_t &c);
        friend bool operator ==(const Player &p , const Player &q);
        friend bool operator !=(const Player &p , const Player &q);
        friend Player operator ~(const Player &p);
};

#endif

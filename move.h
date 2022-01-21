#ifndef __MOVE
#define __MOVE

#include<iostream>
#include<cstdint>

class Move{
	private:
		int8_t x;
		int8_t y;
		int8_t macrocell;
		//int color;
	public:
		Move();
		Move(const int8_t &x, const int8_t &y, const int8_t &macrocell);

		inline const int8_t getRow(void){return x;};
		inline const int8_t getCol(void){return y;};

		inline void setRow(int8_t i){ x = i;};
		inline void setCol(int8_t i){ y = i;};
		inline int8_t getMacro(void){return macrocell;};

		Move operator=(const Move &m);
		friend bool operator ==(const Move &m , const Move &n);
		friend bool operator !=(const Move &m , const Move &n);

		friend std::ostream &operator<<(std::ostream& os, const Move &m);

		bool ValidMove(void);

};


#endif

#include "move.h"
#include "utils.h"

Move::Move(){
		x = -1;
		y = -1;
		macrocell = -1;
}

Move::Move(const int8_t &x, const int8_t &y, const int8_t &macrocell){

		this->x = x;
		this->y = y;
		this->macrocell = macrocell;
}


Move Move::operator=(const Move &m){

		this->x = m.x;
		this->y = m.y;
		this->macrocell = m.macrocell;

		return *this;
}

bool operator ==(const Move &m , const Move &n){

		if((m.x == n.x) && (m.y == n.y) && (m.macrocell == n.macrocell))
			return true;
		else
			return false;

}
bool operator !=(const Move &m , const Move &n){

	if((m.x != n.x) || (m.y != n.y) || (m.macrocell != n.macrocell))
		return true;
	else
		return false;

}

bool Move::ValidMove(void){

	int macro_row = (int) (this->macrocell / MACROROWS);
	int macro_cols = (int) (this->macrocell % MACROCOLS);

	int r = this->x;
	int c = this->y;


	if((r >= (macro_row * MACROROWS)) && ( r < ((macro_row + 1 ) * MACROROWS)) && ( (c >= (macro_cols * MACROCOLS)) && (c < ((macro_cols + 1) * MACROCOLS)) ) )
		return true;
	else
		return false;
}

std::ostream &operator<<(std::ostream& os, const Move &m) {
//	os << " " << (int) m.y << " " << (int) m.x << " "<<(int) m.macrocell << std::endl;
	os << " " << (int) m.y << " " << (int) m.x << std::endl;
	return os;
}

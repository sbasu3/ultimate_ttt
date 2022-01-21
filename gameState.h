#ifndef __GAMESTATE
#define __GAMESTATE

#include"board.h"


class GameState : public Board{

	private:
		int score;
		Player currentPlayer;
	public:
		inline void setCurrentPlayer(int p){ currentPlayer = (int8_t) (p>0)?1:-1;}
		inline Player getCurrentPlayer(void){ return currentPlayer;};
		void evaluate(void);
		int getScore();
		bool make_move(Move m);
	  bool unmake_move(Move m);

};

#endif

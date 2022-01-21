#include "gameState.h"


int GameState::getScore(){
	return score;
}

void GameState::evaluate(void){

	score = (int) cost(this->getState(),this->getMacroState(),this->getCurrentPlayer());
}

bool GameState::make_move(Move m){


	int macro_row = (int) (m.getMacro() / MACROROWS);
	int macro_cols = (int) (m.getMacro() % MACROCOLS);

	int row = m.getRow();
	int col = m.getCol();


	//std::cerr<<"Making Move::"<<m;

	if( !__state[row][col].is_a_player() ){

		this->__state[row][col] = currentPlayer;

		this->setStringFromState();

		hash = std::hash<std::string>{}(_string_state);
		//std::cerr<<"New hash::"<<hash<<std::endl;

		//Update Macrocell
		if(__major[row%MACROROWS][col%MACROCOLS].is_a_player()){
			for(int i = 0 ; i < MACROROWS; i++)
				for(int j = 0 ; j < MACROCOLS; j++)
					if(!__major[i][j].is_a_player())
						__major[i][j] = '*';
		} else {
			__major[row%MACROROWS][col%MACROCOLS] = (int8_t) '*';	//Play here next
		}

		__mini = get_small_state(__state, m.getMacro());
		if(check_for_win(__mini , m , currentPlayer)){
			__major[macro_row][macro_cols] = currentPlayer;
		}

		currentPlayer = ~currentPlayer;		//toggle Player
		return true;
	}

	return false;

}

bool GameState::unmake_move(Move m){

	int macro_row = (int) (m.getMacro() / MACROROWS);
	int macro_cols = (int) (m.getMacro() % MACROCOLS);

	int row = m.getRow();
	int col = m.getCol();

	Squares zilch(0);
	Squares currentCell;

	//std::cerr<<"unmaking move::"<<m;

	if(__state[row][col].is_a_player()){
		this->__state[row][col] = zilch;

		this->setStringFromState();

		hash = std::hash<std::string>{}(_string_state);
		//std::cerr<<"Old hash::"<<hash<<std::endl;

		//Update Macrocell
		if(__major[row%MACROROWS][col%MACROCOLS].is_a_player()){
			for(int i = 0 ; i < MACROROWS; i++)
				for(int j = 0 ; j < MACROCOLS; j++)
					if(!__major[i][j].is_a_player())
						__major[i][j] = 0;
		} else {
			__major[row%MACROROWS][col%MACROCOLS] = (int8_t) 0;	//Play here next
		}


		__major[macro_row][macro_cols] = (int8_t) '*';
		currentPlayer = ~currentPlayer;

		return true;
	}

	return false;


}

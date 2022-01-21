// Subhojit Basu
// using Template from Aswin van Woudenberg



#include "utils.h"



std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

/*
std::ostream &operator<<(std::ostream& os, const Player &s) {
	for (int r=0; r<ROWS; r++) {
		for (int c=0; c<COLS; c++) {
			os << s[r][c];
		}
		os << std::endl;
	}
	return os;
}
*/

float cost(const State &minor, const MacroState &major, const Player &currentPlayer){

	float score = -MAX_SCORE;
	int global_best = 0;
	std::vector<Move> moves;
	MiniState SS, bigstate;
	Move empty(-1,-1,-1);

		for(int i = 0 ; i < MACROROWS; i++)
			for(int j = 0 ; j < MACROCOLS; j++){
				Squares BS = major[i][j];
				if(BS.is_empty() || BS.is_current_square()){
					SS = get_small_state(minor, i*MACROROWS + j);
					if (winning_move(SS,currentPlayer) != empty ){
						score = MAX_SCORE/FACTOR;
						moves.push_back( winning_move(SS,currentPlayer));
					}else{
						score = std::max(score,Probability_of_win(SS,currentPlayer));
					}
				}
		}


		//write a different winning move construct for bigstate
		if(Probability_of_win(major,currentPlayer) > 0.99){
			global_best = Winning_move_Major(major,currentPlayer);
			if(global_best != -1)
				SS = get_small_state(minor,global_best);
			else
				return score;
			for(std::vector<Move>::iterator	it = moves.begin() ; it != moves.end() ; global_best++){
				if(winning_move(SS,currentPlayer) == *it){
					return MAX_SCORE;
				}

			}
		}

	return score;
}

MiniState get_small_state(const State &minor, const int &major){

	MiniState mini;
	int start_row = (int) major/MACROROWS;							//Major Row
	int start_col = (int) major%MACROCOLS;							//Major Col

	for(int i = 0 ; i < MACROROWS ; i++)
		for(int j = 0 ; j < MACROROWS ; j++){
			mini[i][j] = minor[start_row*MACROROWS + i][start_col*MACROCOLS + j];
			//std::cerr<<"Mini Cell::Row:"<<(start_row*MACROROWS+i)<<"Col:"<<(start_col*MACROCOLS+j)<<std::endl;
		}

	return mini;
}

Move winning_move(const MiniState &mini, const Player &color){

	std::vector<Move> moves = getAllMovesMini(mini);
	Move emptyMove;

	//Player currentPlayer(color);			//Possible bug

	for(int i = 0 ; i < (int) moves.size() ; i++)
		if(check_for_win(mini,moves[i],color))
			return moves[i];

	emptyMove.setRow(-1);
	emptyMove.setCol(-1);

	return emptyMove;

}

int Winning_move_Major(const MacroState &major, const Player &color){

	std::vector<Move> moves = getAllMovesMajor(major);
	Move emptyMove;

	//Player currentPlayer(color);			//Possible bug
	MiniState mini = convert_to_small_state(major);
	for(int i = 0 ; i < (int) moves.size() ; i++)
		if(check_for_win(mini,moves[i],color))
			return (moves[i].getRow() * MACROROWS + moves[i].getCol());


	return -1;

}

bool check_for_win(MiniState mini ,Move m ,Player currentPlayer){

	Player p;

	mini[m.getRow()%MACROROWS][m.getCol()%MACROCOLS] = currentPlayer;											//TODO: change teh co-od for MiniState

	if((mini[0][1] == mini[0][2]) && (mini[0][1] == mini[0][0])) 		// Top row
		p = mini[0][0];
	else if ((mini[1][1] == mini[1][2]) && (mini[1][1] == mini[1][0]))	// Mid row
		p = mini[1][0];
	else if ((mini[2][1] == mini[2][2]) && (mini[2][1] == mini[2][0]))	// Bot row
		p = mini[2][0];
	else if ((mini[0][0] == mini[1][0]) && (mini[0][0] == mini[2][0]))	// Left col
		p = mini[0][0];
	else if ((mini[0][1] == mini[1][1]) && (mini[0][1] == mini[2][1]))	// Mid col
		p = mini[0][1];
	else if ((mini[0][2] == mini[1][2]) && (mini[0][2] == mini[2][2]))	// Right col
		p = mini[0][2];
	else if ((mini[0][0] == mini[1][1]) && (mini[0][0] == mini[2][2]))	// Left Diag
		p = mini[0][0];
	else if ((mini[0][2] == mini[1][1]) && (mini[0][2] == mini[2][0]))	// Right Diag
		p = mini[1][1];

	if(p == currentPlayer)
		return true;
	else
		return false;


}

MiniState convert_to_ministate( MacroState major){

	MiniState m;
	Player empty;

	for(int i = 0; i < MACROROWS; i++)
		for(int j = 0; j < MACROCOLS; j++ ){
			Player notempty(major[i][j].getColor());
			m[i][j] = (major[i][j].is_current_square())? empty:notempty ;
			//m[i][j] = (major[i][j] == States::X)? Player::X : ((major[i][j] == States::O)? Player::O : Player::None);
		}
	return m;
}

std::vector<Move> getAllMovesMini(MiniState mini){

	std::vector<Move> m;

	for(int i = 0 ; i < MACROROWS; i++)
		for(int j = 0 ; j < MACROCOLS ; j++){
			if(mini[i][j].is_empty()){
				Move mymove(i,j,-1);
				m.push_back(mymove);
			}
		}

	return m;

}

std::vector<Move> getAllMovesMajor(MacroState major){
	std::vector<Move> m;
	for(int i = 0 ; i < MACROROWS; i++)
		for(int j = 0 ; j < MACROCOLS ; j++){
			if(major[i][j].is_empty() || major[i][j].is_current_square()){
				Move mymove(i,j,-1);
				m.push_back(mymove);
			}
		}
	return m;
}

float Probability_of_win(const MacroState &major,const Player &color){

	std::vector<Move> moves = getAllMovesMajor(major);
	int count = 0;


	if(moves.size() == 0)
		return 0;

	MiniState mini = convert_to_small_state(major);
	for(std::vector<Move>::iterator it = moves.begin() ; it != moves.end() ; it++){
		if(check_for_win(mini,*it,color))
			count++;

	}
	return (count/moves.size());

}

float Probability_of_win(const MiniState &minor,const Player &color){

	std::vector<Move> moves = getAllMovesMini(minor);
	int count = 0;


	if(moves.size() == 0)
		return 0;

	//MiniState mini = convert_to_small_state(major);
	for(std::vector<Move>::iterator it = moves.begin() ; it != moves.end() ; it++){
		if(check_for_win(minor,*it,color))
			count++;

	}
	return (count/moves.size());

}

MiniState convert_to_small_state(MacroState major){
	MiniState mini;

	for(int i = 0 ; i < MACROROWS ; i++)
		for(int j = 0 ; j < MACROCOLS ; j++)
			mini[i][j] = major[i][j];

	return mini;

}

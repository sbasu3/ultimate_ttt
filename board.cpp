#include "board.h"

Board::Board(){

}
Board::~Board(){

}

Board::Board(const Board &B){

	_string_state = B._string_state;
	hash = B.hash;
	__state = B.__state;
	__major = B.__major;
	__mini = B.__mini;

}

Squares Board::getWinner()
{
	if((__major[0][1] == __major[0][2]) && (__major[0][1] == __major[0][0])) 		// Top row
		return __major[0][0];
	else if ((__major[1][1] == __major[1][2]) && (__major[1][1] == __major[1][0]))	// Mid row
		return __major[1][0];
	else if ((__major[2][1] == __major[2][2]) && (__major[2][1] == __major[2][0]))	// Bot row
		return __major[2][0];
	else if ((__major[0][0] == __major[1][0]) && (__major[0][0] == __major[2][0]))	// Left col
		return __major[0][0];
	else if ((__major[0][1] == __major[1][1]) && (__major[0][1] == __major[2][1]))	// Mid col
		return __major[0][1];
	else if ((__major[0][2] == __major[1][2]) && (__major[0][2] == __major[2][2]))	// Right col
		return __major[0][2];
	else if ((__major[0][0] == __major[1][1]) && (__major[0][0] == __major[2][2]))	// Left Diag
		return __major[0][0];
	else if ((__major[0][2] == __major[1][1]) && (__major[0][2] == __major[2][0]))	// Right Diag
		return __major[1][1];
	else
		return Squares(0);
}

std::size_t Board::getHash(){

	return std::hash<std::string>{} (_string_state);

}

std::vector<Move> Board::getMoves(void)														//Get all Legal moves
{
	//list all possible moves
  std::vector<Move> moves;

	std::vector<int> cells = this->getMacroCells();

	Squares winner = this->getWinner();

	if (!winner.is_a_player()){
		for (int i=0; i<ROWS; i++)
			for( int j = 0 ;j < COLS ; j++)
				for (std::vector<int>::iterator it = cells.begin() ; it != cells.end(); it++)
					if ( __state[i][j].is_empty() ){
							Move tmpMove(i,j,*it);
							if (tmpMove.ValidMove())
								moves.push_back(tmpMove);
					}
	}

	std::random_shuffle(moves.begin(),moves.end());
    return moves;
}

std::vector<int> Board::getMacroCells(){								//Return playable macro cells

	std::vector<int> macroCells;
	for (int i=0; i<MACROROWS; i++)
			for( int j = 0 ;j < MACROCOLS ; j++){
				if (__major[i][j].is_current_square() 	){
					//std::cerr<<"Macrocell:"<<i<<" "<<j<<std::endl;
					macroCells.push_back(i*MACROROWS + j);
				}
			}

	return macroCells;

}

void Board::setstate(const int &row, const int &col , const int8_t color){

		Player p(color);

	__state[row][col] =  p;

}
void Board::setbigstate(const int &row, const int &col , const int8_t color){

	Squares s(color);

	__major[row][col] = s;

}
void Board::setStringFromState(void){

	int val;
	char cval;
	std::stringstream S;

	for(int i = 0 ; i < ROWS; i++)
		for(int j = 0 ; j < COLS; j++){
				val = (int) __state[i][j].getColor();
				switch(val){
					case 1:
						cval = '1';
						break;
					case -1:
						cval = '0';
						break;
					case 0:
					default:
						cval = '.';
						break;
				}
				S <<cval<<',';
		}


		this->_string_state = S.str();
		this->_string_state.back() = '\0';
		//std::cerr<<_string_state<<std::endl;
}
void Board::setStateFromString(std::string &minor){

	int row = 0;
	int col = 0;
	_string_state = minor;
	hash = std::hash<std::string>{}(_string_state);
	//std::cerr<<"hash::"<<hash<<std::endl;

	std::vector<std::string> fields = split(minor, ',');
	for (std::string &field : fields) {
		if (field == "0") {
			this->setstate(row , col ,-1);
		} else if (field == "1") {
			this->setstate(row , col ,1);
		} else {
			this->setstate(row , col , 0);
		}
		col++;
		if (col == COLS) {
			row++;
			col = 0;
		}
	}
}

void Board::setMajorStateFromString(std::string &major){
	int row = 0;
	int col = 0;
	std::vector<std::string> fields = split(major, ',');
	for (std::string &field : fields) {
		if (field == "0") {
			this->setbigstate( row , col , -1);
		} else if (field == "1") {
			this->setbigstate( row , col , 1);
		} else if (field == "."){
			this->setbigstate( row , col , 0);
		} else {
			this->setbigstate( row , col , '*');
		}
		col++;
		if (col == COLS) {
			row++;
			col = 0;
		}
	}
}

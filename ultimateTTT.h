// Subhojit Basu
// using Template from Aswin van Woudenberg


#ifndef TTTBOT_H
#define TTTBOT_H

#include <string>
#include <vector>

#include "gameState.h"
#include "utils.h"
#include "negamax.h"

class TTTBot {
	int timebank;
	int time_per_move;
	std::string player_names[2];
	std::string your_bot;
	int your_botid;
	int field_columns;
	int field_rows;
	std::size_t currentHash;
	int round;

	GameState G;
	inline int getTime(void){ return time_per_move;};
	void setting(std::string &key, std::string &value);
	void update(std::string &key, std::string &value);
	void move(int timeout);

public:
	void run();
};

#endif // TTTBOT_H

// c4bot.cpp
// Aswin van Woudenberg

#include "ultimateTTT.h"

#include <iostream>
#include <sstream>
#include<functional>

void TTTBot::run() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::vector<std::string> command = split(line, ' ');
		if (command[0] == "settings") {
			setting(command[1], command[2]);
		} else if (command[0] == "update" && command[1] == "game") {
			update(command[2], command[3]);
		} else if (command[0] == "action" && command[1] == "move") {
			move(std::stoi(command[2]));
		} else {
			std::cerr << "Unknown command: " << line << std::endl;
		}
	}
}


void TTTBot::move(int timeout) {
	// Do something more intelligent here instead of returning a random move
	//std::vector<Move> moves = G.getMoves();
	Move m = findBestMove(G , timeout);
	//Move myMove = *select_randomly(moves.begin(), moves.end());
	if(m.ValidMove())
		std::cout << "place_move" << m;
	else
		std::cout << "no_moves"<<std::endl;

	//moves.clear();
}

void TTTBot::update(std::string &key, std::string &value) {
	if (key == "round") {
		round = std::stoi(value);
	} else if (key == "field") {
		G.setStateFromString(value);
	} else if (key == "macroboard"){
		G.setMajorStateFromString(value);
	}
}


void TTTBot::setting(std::string &key, std::string &value) {
	if (key == "timebank") {
		timebank = std::stoi(value);
	} else if (key == "time_per_move") {
		time_per_move = std::stoi(value);
	} else if (key == "player_names") {
		std::vector<std::string> names = split(value, ',');
		player_names[0] = names[0];
		player_names[1] = names[1];
	} else if (key == "your_bot") {
		your_bot = value;
	} else if (key == "your_botid") {
		your_botid = std::stoi(value);
		G.setCurrentPlayer(your_botid);
	} else if (key == "field_columns") {
		field_columns = std::stoi(value);
	} else if (key == "field_rows") {
		field_rows = std::stoi(value);
	}
}

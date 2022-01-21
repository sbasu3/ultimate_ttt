// Subhojit Basu
// using Template from Aswin van Woudenberg

#ifndef UTILS_H
#define UTILS_H

#include <array>
#include <vector>
#include <ctime>
#include <random>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>

#include "player.h"
#include "squares.h"
#include "move.h"

#define ROWS 9
#define COLS 9
#define MACROROWS 3
#define MACROCOLS 3

#define MAX_SCORE 1000
#define FACTOR 33

typedef std::array<std::array<Player,ROWS>,COLS>  State;				//Size of Board 9x9
typedef std::array<std::array<Squares,MACROROWS>,MACROCOLS> MacroState;		//Size of Board 3x3
typedef std::array<std::array<Player,MACROROWS>,MACROCOLS>  MiniState;		//Size of Board 3x3 ; only used for local compute


// used to get a random element from a container
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

//std::ostream &operator<<(std::ostream& os, const Player &p);
//std::ostream &operator<<(std::ostream& os, const State &s);


std::vector<std::string> split(const std::string &s, char delim);
//std::ostream &operator<<(std::ostream& os, const Squares &s);
//std::hash<std::string> hash_fn;

MiniState get_small_state(const State &state, const int &MajorState);
bool check_for_win(MiniState mini ,Move m ,Player currentPlayer);

std::vector<Move> getAllMoves(const MiniState &mini);
std::vector<Move> getAllMovesMini(MiniState mini);
std::vector<Move> getAllMovesMajor(MacroState major);
MiniState convert_to_ministate( MacroState major);
MiniState convert_to_small_state(MacroState major);
//bool winning_move_exists(const MiniState &mini, const int &color);
Move winning_move(const MiniState &smallstate, const Player &color);
int Winning_move_Major(const MacroState &major, const Player &color);
float Probability_of_win(const MiniState &minor,const Player &color);
float Probability_of_win(const MacroState &major,const Player &color);
float cost(const State &minor, const MacroState &major, const Player &color);

/*
Move Blockingmove(MiniState &smallstate, MacroState &bigstate);
*/
#endif // UTILS_H

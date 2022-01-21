#ifndef __NEGAMAX
#define __NEGAMAX

#include "ttable.h"
#include "gameState.h"

Move findBestMove(GameState G , int totaltime);
int negamax(GameState current_state,  int depth, clock_t start_time,  int alpha, int beta , int totaltime);



#endif

#include "negamax.h"
#include "utils.h"
#include "ttable.h"
#include "ttable_entry.h"
#include "gameState.h"


// This will return the best possible move for the player
Move findBestMove(GameState G , int totaltime)
{
    static int count;
    int bestVal = -MAX_SCORE;
    Move bestMove;
    std::vector<Move> moves = G.getMoves();
    clock_t start_time;
    // Traverse all cells, evalutae minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    start_time = clock();

    for (std::vector<Move>::iterator it = moves.begin() ; it != moves.end(); it++)
        if ((clock() - start_time)/CLOCKS_PER_SEC < totaltime){
            std::cerr<<"Count::"<<count++<<std::endl;
            G.make_move(*it);
            int moveval = negamax(G , 3, start_time, -MAX_SCORE, MAX_SCORE, totaltime);
            if(!G.unmake_move(*it))
                std::cerr<<"error in unmake"<<std::endl;

            if(moveval >= bestVal)
                bestMove = *it;

        }
        else
            break;



    std::cerr<<"The value of the best Move is : "<<bestVal<<std::endl;

    return bestMove;
}

int negamax(GameState current_state,  int depth, clock_t start_time, int alpha, int beta , int totaltime)
{

    int value = -MAX_SCORE;
    int alpha_0 = alpha;
    Move next_move;
    Move best_move;
    int flag;

	//TTable lookup
	std::size_t hash = current_state.getHash();
    //std::cerr<<"Lookup hash::"<<hash<<std::endl;
  	TTableEntry * table_entry = TTable::lookup(hash);

  	if ((table_entry != NULL) && (table_entry->is_valid()) && (table_entry->getdepth() >= depth )){
    	if(table_entry->is_exact())
            return table_entry->get_value();
        else if (table_entry->is_lowerbound())
            alpha = std::max(alpha , table_entry->get_value() );
        else if ( table_entry->is_upperbound())
            beta = std::min(beta , table_entry->get_value());

        if(alpha >= beta)
            return table_entry->get_value();
  	}


	if (( current_state.getWinner().is_empty() ) || (depth <= 0)) {
		current_state.evaluate();
        //std::cerr<<"terminal state for hash::"<<hash<<std::endl;
    	return current_state.getScore();
	}


  	std::vector<Move> moves = current_state.getMoves();
  	int size = moves.size();

	//Node traversal algorithm , we have to reorder teh nodes
    if ((clock() - start_time)/CLOCKS_PER_SEC < totaltime) {
        for (int i = 0; i < size; ++i) {
            next_move = moves[i];
            current_state.make_move(next_move);
            value = std::max(value , -(negamax(current_state, depth - 1, start_time, -beta, -alpha,totaltime)));
            alpha = std::max(alpha , value);
            current_state.unmake_move(next_move);
            if(alpha >= beta)
                break;
        }
    }
    else
        return value;

	//TTable store
	hash = current_state.getHash();

    if(value <= alpha_0)
        flag = UPPERBOUND;
    else if( value >= beta)
        flag = LOWERBOUND;
    else
        flag = EXACT;

  	table_entry = new TTableEntry(hash, value , depth, flag);
  	TTable::save_entry(*table_entry);
    delete table_entry;
  	best_move = next_move;
  	return value;
}

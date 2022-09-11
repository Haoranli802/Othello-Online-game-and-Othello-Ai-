//
// Created by Haoran Li on 2/13/22.
//

#include "HaoranLiOthelloAI.hpp"
#include "ics46/factory/DynamicFactory.hpp"


ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, haoral19::HaoranLiOthelloAI, "Haoran's AI (Required)");


std::pair<int, int> haoral19::HaoranLiOthelloAI::chooseMove(const OthelloGameState& state)
{
    // implementation of the AI goes here
    int myTurn;
    if(state.isWhiteTurn()){
        myTurn = 2;
    }
    else{
        myTurn = 1;
    }
    std::vector<std::pair<int , int>> moves = findAllPossibleMoves(state);
    int max = -10086;
    std::pair<int, int> bestMove = std::make_pair(-1, -1);
    for(std::pair<int, int> move : moves){
        int temp = heuristicSearch(state, 4, myTurn);
        if(temp >= max){
            max = temp;
            bestMove = move;
        }
    }
    return bestMove;
}

// The simple evaluation
int haoral19::HaoranLiOthelloAI::evaluation(const OthelloGameState& state, int myTurn){
    if(myTurn == 1){
        return state.blackScore() - state.whiteScore();
    }
    else{
        return state.whiteScore() - state.blackScore();
    }
}


std::vector<std::pair<int , int>> haoral19::HaoranLiOthelloAI::findAllPossibleMoves(const OthelloGameState& state){
    std::vector<std::pair<int , int>> allPossibleMove;
    for(int i = 0; i < state.board().width(); i++){
        for(int j = 0; j < state.board().height(); j++){
            if(state.isValidMove(i, j)){
                allPossibleMove.emplace_back(i, j);
            }
        }
    }
    return allPossibleMove;
}


int haoral19::HaoranLiOthelloAI::heuristicSearch(const OthelloGameState& state, int depth, int myTurn){
    if(depth == 0){
        return evaluation(state, myTurn);
    }
    else{
        if((state.isBlackTurn() and myTurn == 1) or (state.isWhiteTurn() && myTurn == 2)){
            int max = -10086; // else it will be too big
            for(std::pair<int, int> moves : findAllPossibleMoves(state)){
                std::unique_ptr<OthelloGameState> temp = state.clone();
                temp->makeMove(moves.first, moves.second);
                int temp_eval = heuristicSearch(*temp, depth - 1, myTurn);
                if(temp_eval >= max){
                    max = temp_eval;
                }
            }
            return max;
        }
        else{
            int min = 10086; // maximum is actually 64
            for(std::pair<int, int> moves : findAllPossibleMoves(state)){
                std::unique_ptr<OthelloGameState> temp = state.clone();
                temp->makeMove(moves.first, moves.second);
                int temp_eval = heuristicSearch(*temp, depth - 1, myTurn);
                if(temp_eval <= min){
                    min = temp_eval;
                }
            }
            return min;
        }
    }
}
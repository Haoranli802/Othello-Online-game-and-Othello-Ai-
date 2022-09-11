//
// Created by Haoran Li on 2/13/22.
//

#ifndef PROJCET3_HAORANLIOTHELLOAI_HPP
#define PROJCET3_HAORANLIOTHELLOAI_HPP

#include "othellogame/OthelloAI.hpp"
#include <vector>


namespace haoral19
{
    class HaoranLiOthelloAI : public OthelloAI
    {
    public:
        // The main function for Haoran's AI to choose a move based on the current state based on the best final
        // possible state from the initial state. I used depth of 4 here to get the best result within resonable time.
        std::pair<int, int> chooseMove(const OthelloGameState& state) override;

        // The evaluation function for the heuristic Search. This is a simple evaluation function which basically
        // returns the the score of Haoran's AI minus the score of its opponent.
        int evaluation(const OthelloGameState& state, int myTurn);

        // This function takes in the game state and find out all the possible moves based on the current turn and the
        // game board.
        std::vector<std::pair<int , int>> findAllPossibleMoves(const OthelloGameState& state);

        // The heuristic Search function finds out the best evaluation score recursively from all the possible moves
        // based the current game state. It uses the search-tree-based algorithm.
        int heuristicSearch(const OthelloGameState& state, int depth, int myTurn);
    };
}



#endif //PROJCET3_HAORANLIOTHELLOAI_HPP

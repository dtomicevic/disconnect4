#ifndef PARPRO_CONNECT4_MINIMAX_HPP
#define PARPRO_CONNECT4_MINIMAX_HPP

#include <limits>
#include <iostream>

#include "bitboard.hpp"
#include "transition.hpp"
#include "print.hpp"

float max_value(const game_t& game, int d);


float utility(const game_t& game)
{
    return haswon(game.boards[0]) ? -1 :
           haswon(game.boards[1]) ?  1 : 0;
}

bool terminal(const game_t& game)
{
    return haswon(game.boards[0]) ||
           haswon(game.boards[1]) ||
           !playable(game);
}

float min_value(const game_t& game, int d) //, int& wins, int& losses)
{
    if(terminal(game))
        return utility(game);

    if(d == 0)
        return 0;

    float m = std::numeric_limits<float>::infinity();

    for(auto& x : succ(game))
        m = std::min(m, max_value(x, d - 1));

    return m;
}

float max_value(const game_t& game, int d)
{
    if(terminal(game))
        return utility(game);

    if(d == 0)
        return 0;

    float m = -std::numeric_limits<float>::infinity();

    for(auto& x : succ(game))
        m = std::max(m, min_value(x, d - 1));

    return m;
}

game_t minimax(const game_t& game, int d)
{
    float m = -std::numeric_limits<float>::infinity();
    game_t best;

    // int wins = 0, losses = 0, searched = 0;

    for(auto& x : succ(game))
    {
        auto v = min_value(x, d);

        if (v > m)
            m = v, best = x; 
    }

    return best;
}

#endif

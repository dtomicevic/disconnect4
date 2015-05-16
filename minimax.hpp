#ifndef PARPRO_CONNECT4_MINIMAX_HPP
#define PARPRO_CONNECT4_MINIMAX_HPP

#include <limits>

#include "bitboard.hpp"
#include "transition.hpp"

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
        return 0.5f;

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
        return 0.5f;

    float m = -std::numeric_limits<float>::infinity();

    for(auto& x : succ(game))
        m = std::max(m, min_value(x, d - 1));

    return m;
}

#endif

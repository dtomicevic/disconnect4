#ifndef PARPRO_CONNECT4_MINIMAX_HPP
#define PARPRO_CONNECT4_MINIMAX_HPP

#include <limits>
#include <iostream>

#include "bitboard.hpp"
#include "transition.hpp"
#include "print.hpp"

float max_value(const game_t& game, float a, float b, int d);


float utility(const game_t& game, int d)
{
    auto ut =  (haswon(game.boards[0]) ? -1 :
                haswon(game.boards[1]) ?  1 : 0);

    return ut * (d + 1);
}

bool terminal(const game_t& game)
{
    return haswon(game.boards[0]) ||
           haswon(game.boards[1]) ||
           !playable(game);
}

float heuristic(const game_t& game)
{
    return 0;
}

float min_value(const game_t& game, float alpha, float beta, int d)
{
    if(terminal(game))
        return utility(game, d);

    if(d == 0)
        return heuristic(game);

    float m = beta;

    for(auto& x : succ(game))
    {
        m = std::min(m, max_value(x, alpha, m, d - 1));

        if(m <= alpha)
            return alpha;
    }

    return m;
}

float max_value(const game_t& game, float alpha, float beta, int d)
{
    if(terminal(game))
        return utility(game, d);

    if(d == 0)
        return heuristic(game);

    float m = alpha;

    for(auto& x : succ(game))
    {
        m = std::max(m, min_value(x, m, beta, d - 1));

        if(m >= beta)
            return beta;
    }

    return m;
}

game_t minimax(const game_t& game, int d)
{
    using lim = std::numeric_limits<float>;

    float m = -lim::infinity();
    game_t best;
    int i = 0;

    for(auto& x : succ(game))
    {
        i++;

        auto v = min_value(x, -lim::infinity(), lim::infinity(), d - 1);

        std::cout << "i = " << i << "; v = " << v << std::endl;

        if (v > m)
            m = v, best = x; 
    }

    return best;
}

#endif

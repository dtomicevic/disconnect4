#ifndef PARPRO_CONNECT4_MINIMAX_HPP
#define PARPRO_CONNECT4_MINIMAX_HPP

#include <limits>
#include <iostream>

#include <cmath>
#include "bitboard.hpp"
#include "transition.hpp"
#include "print.hpp"
#include "transtable.hpp"
#include <cassert>

#define LOSS -1
#define WIN 1
#define DRAW 0

struct stats_t
{
    int wins = 0;
    int losses = 0;
};

float max_value(const game_t& game,
                float a,
                float b,
                int d,
                TransTable& transtable,
                stats_t& stats);

float utility(const game_t& game, int d, stats_t& stats)
{
    if(haswon(game.boards[0]))
    {
        stats.losses++;
        return LOSS * (d + 1);
    }
    else if (haswon(game.boards[1]))
    {
        stats.wins++;
        return WIN * (d + 1);
    }

    return DRAW;
}

bool terminal(const game_t& game)
{
    return haswon(game.boards[0]) ||
           haswon(game.boards[1]) ||
           !playable(game);
}

float heuristic(const game_t&, int d, const stats_t& stats)
{
    return (stats.wins - stats.losses) * (d + 1)
        / (float)(stats.wins + stats.losses + 1);
}

float min_value(const game_t& game,
                float alpha,
                float beta,
                int d,
                TransTable& transtable,
                stats_t& stats)
{
    if(terminal(game))
        return utility(game, d, stats);

    if(d == 0)
        return heuristic(game, d, stats);

    auto encoded = encode(game);

    if(transtable.has(encoded))
        return transtable[encoded];

    float m = beta;

    for(auto& x : succ(game))
    {
        m = std::min(m, max_value(x, alpha, m, d - 1, transtable, stats));

        if(m <= alpha)
            return alpha;
    }

    transtable.put(encoded, m);
    return m;
}

float max_value(const game_t& game,
                float alpha,
                float beta,
                int d,
                TransTable& transtable,
                stats_t& stats)
{
    if(terminal(game))
        return utility(game, d, stats);

    if(d == 0)
        return heuristic(game, d, stats);

    auto encoded = encode(game);

    if(transtable.has(encoded))
        return transtable[encoded];

    float m = alpha;

    for(auto& x : succ(game))
    {
        m = std::max(m, min_value(x, m, beta, d - 1, transtable, stats));

        if(m >= beta)
            return beta;
    }

    transtable.put(encoded, m);
    return m;
}

float minimax_worker(const game_t& game, int d)
{
    auto inf = std::numeric_limits<float>::infinity();

    TransTable transtable;
    stats_t stats;

    return game.turn ?
        max_value(game, -inf, inf, d, transtable, stats) :
        min_value(game, -inf, inf, d, transtable, stats);
}

game_t minimax(const game_t& game, int d, TransTable& transtable)
{
    using lim = std::numeric_limits<float>;

    float m = -lim::infinity();
    game_t best;
    //int i = 0;

    stats_t stats;

    for(auto& x : succ(game))
    {
        //i++;

        auto v = min_value(x, -lim::infinity(), lim::infinity(),
                           d - 1, transtable, stats);

        // std::cout << "i = " << i << "; v = " << v << std::endl;

        if (v > m)
            m = v, best = x; 
    }

    return best;
}

#endif

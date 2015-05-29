#ifndef PARPRO_CONNECT4_AI_HPP
#define PARPRO_CONNECT4_AI_HPP

#include "minimax.hpp"

class Ai
{
public:
    Ai(int depth = 7)
        : depth(depth) {}

    game_t play(const game_t& game);

private:
    int depth;
};

game_t Ai::play(const game_t& game)
{
    return minimax(game, this->depth);
}

#endif

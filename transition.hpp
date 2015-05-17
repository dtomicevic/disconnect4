#ifndef PARPRO_CONNECT4_TRANSITION_HPP
#define PARPRO_CONNECT4_TRANSITION_HPP

#include <vector>

#include "game.hpp"

std::vector<game_t> succ(const game_t& game)
{
    std::vector<game_t> states;

    for(int i = 0; i < WIDTH; ++i)
    {
        // don't create a state if the column i is already full
        if(!legal(game, i))
            continue;

        // TODO refactor play to copy value
        game_t newgame(game);
        play(newgame, i);
        states.push_back(newgame);
    }

    return states;
}

#endif

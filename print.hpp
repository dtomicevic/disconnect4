#ifndef PARPRO_CONNECT4_PRINTHPP
#define PARPRO_CONNECT4_PRINTHPP

#include <ostream>

#include "bitboard.hpp"
#include "game.hpp"
#include "colors.hpp"

std::ostream& operator<<(std::ostream& os, const game_t& game)
{
    for(int i = HEIGHT - 1; i >= 0; --i)
    {
        for(int j = 0; j < WIDTH; ++j)
        {
            auto p = is_set(game.boards[0], i, j) ? 1 :
                     is_set(game.boards[1], i, j) ? 2 : 0;

            os << "|"
               << (p == 1 ? color::red : p == 2 ? color::yellow : "") 
               << (p > 0 ? "O" : "_") << color::end;
        }

        os << "|" << std::endl;
    }

    return os;
}

#endif

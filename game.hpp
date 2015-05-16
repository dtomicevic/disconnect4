#ifndef PARPRO_CONNECT4_GAME_HPP
#define PARPRO_CONNECT4_GAME_HPP

#include "bitboard.hpp"

typedef unsigned char ubyte_t;

struct game_t
{
    // board data for each player encoded as hot ones
    bitboard_t boards[2];
    
    // bit indices of the first empty field in the corresponding column
    ubyte_t height[WIDTH];
    
    // determines which player plays next
    size_t turn;
};

void reset(game_t& game)
{
    // player zero goes first
    game.turn = 0;

    // boards are initially empty
    game.boards[0] = game.boards[1] = 0;
    
    // reset each index to the bottom of the board
    // if WIDTH = 7 then [0, 7, 14, 21, ...]
    for(int i = 0; i < WIDTH; ++i)
        game.height[i] = STRIDE * i;
}

void play(game_t& game, size_t col)
{
    // flip the bit in the current players bitboard corresponding to the first
    // non empty row on the game board increment the height for the played
    // column by 1
    game.boards[game.turn] |= 1LL << game.height[col]++;
    game.turn = !game.turn;
}

bool playable(const game_t& game)
{
    return (game.boards[0] | game.boards[1]) ^ FULL;
}

#endif

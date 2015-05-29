#ifndef PARPRO_CONNECT4_BITBOARD_HPP
#define PARPRO_CONNECT4_BITBOARD_HPP

#include <cstdint>
#include <cstdlib>

#define WIDTH 7
#define HEIGHT 6

#define STRIDE (HEIGHT + 1)
#define SIZE (WIDTH * HEIGHT)

#define STRIDE1 (STRIDE + 1)

// 6x7 board size bitmask in uint64_t

//  .  .  .  .  .  .  .  top
//  5 12 19 26 33 40 47
//  4 11 18 25 32 39 46
//  3 10 17 24 31 38 45
//  2  9 16 23 30 37 44
//  1  8 15 22 29 36 43
//  0  7 14 21 28 35 42  bottom 

typedef uint64_t bitboard_t;

#define BOTTOM_ROW 0x0101010101010101LL
#define TOP_ROW (BOTTOM_ROW << HEIGHT)

// bitmask of the full board
#define FULL 0x0FDFBF7EFDFBFLL

bool is_set(bitboard_t board, int row, int col)
{
    return board & 1LL << (col * STRIDE + row);
}

bool haswon(bitboard_t board)
{
    bitboard_t diag1 = board & (board >> HEIGHT);
    bitboard_t hori  = board & (board >> STRIDE);
    bitboard_t diag2 = board & (board >> STRIDE1);
    bitboard_t vert  = board & (board >> 1);
    
    return ((diag1 & (diag1 >> 2 * HEIGHT)) |
            (hori  & (hori  >> 2 * STRIDE)) |
            (diag2 & (diag2 >> 2 * STRIDE1)) |
            (vert  & (vert  >> 2)));
}

#endif

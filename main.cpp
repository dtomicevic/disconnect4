#include <iostream>

#include "game.hpp"
#include "ai.hpp"
#include "print.hpp"

int main(void)
{
    auto game = newgame();
    int move;

    auto ai = Ai(7);

    while(playable(game))
    {
        std::cout << game << std::endl;
        std::cin >> move;

        if(move < 1 || move > 7)
        {
            std::cout << "Illegal move " << move << std::endl;
            continue;
        }

        move -= 1;

        if(!legal(game, move))
        {
            std::cout << "Column full!" << std::endl;
            continue;
        }

        play(game, move);

        if(haswon(game.boards[0]))
        {
            std::cout << game << std::endl << "You win!" << std::endl;
            break;
        }

        game = ai.play(game);

        if(haswon(game.boards[1]))
        {
            std::cout << game << std::endl << "You lose!" << std::endl;
            break;
        }
    }

    return 0;
}

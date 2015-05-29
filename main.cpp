#include <iostream>

#include "game.hpp"
#include "ai.hpp"
#include "print.hpp"
#include "stopwatch.hpp"
#include "mpi/mpi.hpp"

int main(int argc, char **argv)
{
    mpi::Context context(&argc, &argv);
    mpi::World world;

    auto ai = Ai(world, 12);

    if(world.rank > 0)
    {
        ai.loop();
        exit(0);
    }

    auto game = newgame();
    int move;

    while(playable(game))
    {
        std::cout << std::endl << game << color::green;
        
        for(int i = 0; i < 7; ++i)
            std::cout << (legal(game, i) ? " ^" : "  ");

        std::cout << std::endl;

        for(int i = 0; i < 7; ++i)
            std::cout << " " << (legal(game, i) ? std::to_string(i + 1) : " ");

        std::cout << color::end << std::endl << "> ";
        std::cin >> move;

        if(move < 1 || move > 7)
        {
            std::cout << color::red << "Illegal move " << move
                      << color::end << std::endl;
            continue;
        }

        move -= 1;

        if(!legal(game, move))
        {
            std::cout << color::red << "Column full!" 
                      << color::end << std::endl;
            continue;
        }

        play(game, move);

        if(haswon(game.boards[0]))
        {
            std::cout << game << std::endl << color::green
                      << "You win!" << color::end << std::endl;
            break;
        }

        std::cout << std::endl << color::blue
                  << "[Ai] Thinking..." << std::endl;

        Stopwatch<std::chrono::milliseconds> stopwatch;
        game = ai.play(game);

        std::cout << "[Ai] Made my move in " << stopwatch.stop()
                  << " ms." << color::end << std::endl;

        if(haswon(game.boards[1]))
        {
            std::cout << game << std::endl << color::red
                      << "You lose!" << color::end << std::endl;
            break;
        }
    }

    return 0;
}

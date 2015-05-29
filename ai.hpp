#ifndef PARPRO_CONNECT4_AI_HPP
#define PARPRO_CONNECT4_AI_HPP

#include <deque>

#include "minimax.hpp"
#include "mpi/mpi.hpp"
#include "print.hpp"

class Ai
{
public:
    Ai(const mpi::Comm& comm, int depth = 7)
        : comm(comm), depth(depth) {}

    game_t play(const game_t& game);

    void loop();

private:
    mpi::Comm comm;
    int depth;
};

auto expand(const game_t& game, int depth, size_t size)
{
    std::deque<std::pair<int, game_t>> queue;
    queue.push_back(std::make_pair(depth, game));

    while(queue.size() < size)
    {
        auto item = queue.front();

        for(auto x : succ(item.second))
            queue.push_back(std::make_pair(item.first - 1, x));

        queue.pop_front();
    }

    return queue;
}

game_t Ai::play(const game_t& game)
{
    TransTable transtable;

    auto items = expand(game, depth, comm.size);

    int busy = 0;

    for(int i = 1; i < comm.size && !items.empty(); ++i)
    {
        mpi::send(items.front(), i, 1, comm);
        busy++;
        items.pop_front();
    }

    while(busy > 0)
    {
        auto data = mpi::recv<std::pair<float, game_t>>(MPI_ANY_SOURCE, 0, comm);
        float value = data->ptr->first;
        transtable.put(encode(data->ptr->second), value);

        if(items.empty())
        {
            busy--;
            continue;
        }

        auto sender = data->status.source();
        mpi::isend(items.front(), sender, 1, comm);
        items.pop_front();
    }

    return minimax(game, depth, transtable);
}

void Ai::loop()
{
    while(true)
    {
        auto data = mpi::recv<std::pair<int, game_t>>(0, 1, comm);
        auto value = minimax_worker(data->ptr->second, data->ptr->first);
        mpi::isend(std::make_pair(value, data->ptr->second), 0, 0, comm);
    }
}

#endif

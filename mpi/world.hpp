#ifndef PARPRO_MPI_WORLD_HPP
#define PARPRO_MPI_WORLD_HPP

#include <mpi.h>

#include "comm.hpp"

namespace mpi
{

class World : public Comm
{
public:
    World()
        : Comm(MPI_COMM_WORLD) {}
};

}

#endif

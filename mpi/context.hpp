#ifndef PARPRO_MPI_CONTEXT_HPP
#define PARPRO_MPI_CONTEXT_HPP

#include <mpi.h>

namespace mpi
{

class Context
{
public:
    Context(int *argc, char ***argv);
    ~Context();
};

Context::Context(int *argc, char ***argv)
{
    MPI_Init(argc, argv);
}

Context::~Context()
{
    MPI_Finalize();
}

}

#endif

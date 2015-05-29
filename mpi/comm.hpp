#ifndef PARPRO_MPI_COMM_HPP
#define PARPRO_MPI_COMM_HPP

#include <mpi.h>

#include "data.hpp"

namespace mpi
{

class Comm
{
public:
    Comm(MPI_Comm comm);

    int rank, size;

    operator const MPI_Comm&() const;

    template <typename T>
    typename Data<T>::sptr recv(int source, int tag);

protected:
    MPI_Comm comm;
};

Comm::Comm(MPI_Comm comm)
    : comm(comm)
{
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

}

Comm::operator const MPI_Comm&() const
{
    return comm;
}

}

#endif

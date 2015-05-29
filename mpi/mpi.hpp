#ifndef PARPRO_MPI_MPI_HPP
#define PARPRO_MPI_MPI_HPP

#include <cstdlib>
#include <mpi.h>

#include "context.hpp"
#include "comm.hpp"
#include "world.hpp"
#include "request.hpp"
#include "recv_request.hpp"
#include "data.hpp"

namespace mpi
{

template <class T>
Request::sptr isend(const T& data, int dest, int tag, Comm& comm)
{
    auto request = std::make_shared<RecvRequest<T>>();

    // TODO add status
    MPI_Isend(&data, sizeof(T), MPI_BYTE, dest, tag, comm, *request);

    return request;
}

template <class T>
void send(const T& data, int dest, int tag, Comm& comm)
{
    MPI_Send(&data, sizeof(T), MPI_BYTE, dest, tag, comm);
}

template <class T>
typename RecvRequest<T>::sptr irecv(int source, int tag, Comm& comm)
{
    auto request = std::make_shared<RecvRequest<T>>();

    MPI_Irecv(request->data.ptr, sizeof(T), MPI_BYTE, source, tag, comm, *request);

    return request;
}

template <class T>
typename Data<T>::sptr recv(int source, int tag, Comm& comm)
{
    auto data = std::make_shared<Data<T>>();

    MPI_Recv(data->ptr, sizeof(T), MPI_BYTE, source, tag, comm, data->status);

    return data;
}

}

#endif

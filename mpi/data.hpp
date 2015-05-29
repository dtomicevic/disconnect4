#ifndef PARPRO_MPI_DATA_HPP
#define PARPRO_MPI_DATA_HPP

#include <cstdlib>
#include <memory>
#include <mpi.h>

#include "status.hpp"

namespace mpi
{

template <class T>
class Data
{
public:
    using sptr = std::shared_ptr<Data<T>>;

    Data();
    ~Data();

    Status status;
    T* ptr;
};

template <class T>
Data<T>::Data()
    : ptr(static_cast<T*>(malloc(sizeof(T)))) {}

template <class T>
Data<T>::~Data()
{
    free(ptr);
}

}

#endif

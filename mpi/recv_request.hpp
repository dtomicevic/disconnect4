#ifndef PARPRO_MPI_RECVREQUEST_HPP
#define PARPRO_MPI_RECVREQUEST_HPP

#include <memory>
#include <mpi.h>

#include "request.hpp"
#include "data.hpp"

namespace mpi
{

template <typename T>
class RecvRequest : public Request
{
public:
    using sptr = std::shared_ptr<Request>;

    RecvRequest() {}

    Data<T> data;
};

}

#endif

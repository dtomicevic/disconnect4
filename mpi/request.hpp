#ifndef PARPRO_MPI_REQ_HPP
#define PARPRO_MPI_REQ_HPP

#include <memory>
#include <mpi.h>

#include "status.hpp"

namespace mpi
{

class Request
{
public:
    using sptr = std::shared_ptr<Request>;

    Request() {}

    bool test();

    operator MPI_Request*();
    operator const MPI_Request* const() const;

    operator MPI_Request();
    operator const MPI_Request() const;

    const Status& status() const;
    
protected:
    MPI_Request request;
    Status status_;
};

bool Request::test()
{
    int flag;

    MPI_Test(&request, &flag, status_);

    return flag;
}

Request::operator MPI_Request*()
{
    return &request;
}

Request::operator const MPI_Request* const() const
{
    return &request;
}

Request::operator MPI_Request()
{
    return request;
}

Request::operator const MPI_Request() const
{
    return request;
}

}

#endif

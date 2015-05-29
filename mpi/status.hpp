#ifndef PARPRO_MPI_STATUS_HPP
#define PARPRO_MPI_STATUS_HPP

#include <memory>
#include <mpi.h>

namespace mpi
{

class Status
{
public:
    using sptr = std::shared_ptr<Status>;

    Status() {}

    int source() const;
    int tag() const;

    operator MPI_Status*();
    operator const MPI_Status*() const;

private:
    MPI_Status status;
};

int Status::source() const
{
    return status.MPI_SOURCE;
}

int Status::tag() const
{
    return status.MPI_TAG;
}

Status::operator MPI_Status*()
{
    return &status;
}

Status::operator const MPI_Status*() const
{
    return &status;
}

}

#endif

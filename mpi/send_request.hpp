#ifndef PARPRO_MPI_SENDREQUEST_HPP
#define PARPRO_MPI_SENDREQUEST_HPP

#include <memory>
#include <mpi.h>

#include "request.hpp"

namespace mpi
{

class SendRequest : public Request
{
public:
    SendRequest() {}
};

}

#endif

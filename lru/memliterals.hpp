#ifndef PARPRO_CONNECT4_MEMLITERALS_HPP
#define PARPRO_CONNECT4_MEMLITERALS_HPP

namespace mem_literals
{

constexpr unsigned long long operator"" _GB(unsigned long long gb)
{
    return 1024 * 1024 * 1024 * gb;
}

constexpr unsigned long long operator"" _MB(unsigned long long mb)
{
    return 1024 * 1024 * mb;
}

constexpr unsigned long long operator"" _kB(unsigned long long kb)
{
    return 1024 * kb;
}

}

#endif



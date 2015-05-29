#ifndef PARPRO_CONNECT4_TRANSTABLE_HPP
#define PARPRO_CONNECT4_TRANSTABLE_HPP

#include "bitboard.hpp"

#include "lru/lrucache.hpp"
#include "lru/memliterals.hpp"

#ifndef TRANSTABLE_SIZE
#define TRANSTABLE_SIZE 700_MB
#endif

typedef unsigned long long ull;
typedef unsigned char byte;

using namespace mem_literals;

typedef LruCache<bitboard_t, byte, TRANSTABLE_SIZE> BoardCache;

class TransTable : BoardCache
{
public:
    TransTable() {}

    using BoardCache::cbegin;
    using BoardCache::cend;

    using BoardCache::size;
    using BoardCache::max_items;

    using BoardCache::has;

    using BoardCache::at;
    using BoardCache::operator[];

    using BoardCache::put;
};


#endif

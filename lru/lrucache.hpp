#ifndef PARPRO_CONNECT4_LRUCACHE_HPP
#define PARPRO_CONNECT4_LRUCACHE_HPP

#include <map>
#include <list>

typedef unsigned long long ull;

template <typename K, typename T>
using list_pair_t = std::list<std::pair<K, T>>;

template <typename K, typename T>
using list_pair_iterator_t = typename list_pair_t<K, T>::iterator;

template <typename K,
          typename T,
          ull mem,
          typename lookup_t = std::map<K, list_pair_iterator_t<K, T>>>
class LruCache
{
public:
    LruCache() {}

    auto cbegin() const;
    auto cend() const;

    size_t size() const;
    ull max_items() const;

    bool has(const K& key) const;

    const T& at(const K& key);
    const T& operator[](const K& key);

    void put(const K& key, const T& value);

private:
    list_pair_t<K, T> items;
    lookup_t lookup;
    
    ull max_items_ = mem / (2 * sizeof(K) + sizeof(T));
};

#include "lrucache.inl"

#endif

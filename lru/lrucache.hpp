#ifndef PARPRO_CONNECT4_LRUCACHE_HPP
#define PARPRO_CONNECT4_LRUCACHE_HPP

#include <map>
#include <list>

template <typename K, typename T>
using list_pair_t = std::list<std::pair<K, T>>;

template <typename K, typename T>
using list_pair_iterator_t = typename list_pair_t<K, T>::iterator;

template <typename K,
          typename T,
          size_t mem,
          typename lookup_t = std::map<K, list_pair_iterator_t<K, T>>>
class LruCache
{
public:
    LruCache() {}

    auto cbegin() const;
    auto cend() const;

    size_t size() const;
    size_t max_items() const;

    bool has(const K& key) const;

    const T& at(const K& key);
    const T& operator[](const K& key);

    void put(const K& key, const T& value);

private:
    list_pair_t<K, T> items;
    lookup_t lookup;
    
    size_t max_items_ = mem;
};

#include "lrucache.inl"

#endif

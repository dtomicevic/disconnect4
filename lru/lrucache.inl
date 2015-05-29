#include "lrucache.hpp"

template <typename K, typename T, ull mem, typename lookup_t>
auto LruCache<K, T, mem, lookup_t>::cbegin() const
{
    return items.cbegin();
}

template <typename K, typename T, ull mem, typename lookup_t> 
auto LruCache<K, T, mem, lookup_t>::cend() const
{
    return items.cend();
}

template <typename K, typename T, ull mem, typename lookup_t> 
size_t LruCache<K, T, mem, lookup_t>::size() const
{
    return items.size();
}

template <typename K, typename T, ull mem, typename lookup_t> 
ull LruCache<K, T, mem, lookup_t>::max_items() const
{
    return max_items_;
}

template <typename K, typename T, ull mem, typename lookup_t> 
bool LruCache<K, T, mem, lookup_t>::has(const K& key) const
{
    return lookup.find(key) != lookup.end();
}

template <typename K, typename T, ull mem, typename lookup_t> 
const T& LruCache<K, T, mem, lookup_t>::at(const K& key)
{
    auto it = lookup.at(key);
    items.splice(items.begin(), items, it);
    return items.begin()->second;
}

template <typename K, typename T, ull mem, typename lookup_t> 
const T& LruCache<K, T, mem, lookup_t>::operator[](const K& key)
{
    return at(key);
}

template <typename K, typename T, ull mem, typename lookup_t> 
void LruCache<K, T, mem, lookup_t>::put(const K& key, const T& value)
{
    items.push_front(std::make_pair(key, value));
    lookup[key] = items.begin();

    if(items.size() > max_items_)
    {
        lookup.erase(items.back().first);
        items.pop_back();
    }
}

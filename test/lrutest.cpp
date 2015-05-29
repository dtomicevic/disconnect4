#include <iostream>

#include "../lru/lrucache.hpp"
#include "../lru/memliterals.hpp"

int main(void)
{
    using namespace mem_literals;

    LruCache<int, int, 1_kB> lru;

    lru.put(1, 10);
    lru.put(2, 20);
    lru.put(3, 30);
    lru.put(4, 40);
    lru.put(5, 50);
    lru.put(6, 60);

    std::cout << lru.at(3) << ", " << lru[6] << std::endl;

    std::cout << lru.has(7) << std::endl;
    std::cout << lru.has(5) << std::endl;

    std::cout << lru.max_items() << std::endl;

    for(int i = 10; i < 120; ++i)
        lru.put(i, 11 * i);

    for(auto it = lru.cbegin(); it != lru.cend(); ++it)
        std::cout << it->first << ", " << it->second << std::endl;

    return 0;
}

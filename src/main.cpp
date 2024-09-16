#include <cassert>
#include <iostream>

#include "LRUcache.hpp"

int slow_get_page_int(int key) { return key; }

int main()
{
    size_t cacheSize = 0;
    int numElem   = 0;
    int hits = 0;

    std::cout << "Enter cache size: ";
    std::cin >> cacheSize;

    std::cout << "Enter the number of elements: ";
    std::cin >> numElem;

    lru_cache_t<int>cache{cacheSize};
  
    for (int i = 0; i < numElem; i++) 
    {
        int page;
        std::cin >> page;

        assert(std::cin.good());

        if (cache.lookup_update(page, slow_get_page_int))
            hits += 1;
    }
    
    std::cout << "Number of hits: " << hits << "\n";
    
    return 0;
}
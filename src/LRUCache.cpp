#include <cassert>
#include <iostream>

#include "LRUCache.hpp"
#include "GetPage.hpp"

void lru_cache()
{
    size_t cacheSize = 0;
    int numElem  = 0;

    std::cin >> cacheSize >> numElem;
    assert(std::cin.good());
    
    cache::lru_cache_t<int>cache{cacheSize};
  
    for (int i = 0; i < numElem; i++) 
    {
        int page;
        std::cin >> page;
        assert(std::cin.good());

        cache.lookup_update(page, slow_get_page);
    }

    std::cout << cache.get_hits() << std::endl; 
}
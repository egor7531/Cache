#include <cassert>
#include <iostream>
#include <vector>

#include "PerfectCache.hpp"
#include "GetPage.hpp"

void perfect_cache()
{
    size_t cacheSize = 0;
    int numElem  = 0;

    std::cin >> cacheSize >> numElem;
    assert(std::cin.good());
    
    std::vector<int> pages;
    for (size_t i = 0; i != numElem; i++)
    {
        int page = 0;
        std::cin >> page;
        assert(std::cin.good());

        pages.push_back(page);
    }

    cache::perfect_cache_t<int, int> cache(cacheSize, pages);

    for (auto x: pages)
        cache.lookup_update(x, slow_get_page);

    std::cout << cache.get_hits() << std::endl; 
}
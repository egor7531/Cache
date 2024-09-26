#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

#include "LRUCache.hpp"
#include "LFUCache.hpp"
#include "PerfectCache.hpp"

enum cache_t { LRU, LFU, PERFECT, ERROR_TYPE_CACHE };

int slow_get_page_int(int key);
cache_t choose_cache(int argc, char* argv[]);
int get_hits(int argc, char* argv[], const size_t cacheSize, const int numElem);

int main(int argc, char* argv[])
{
    size_t cacheSize = 0;
    int numElem  = 0;
    int hits = 0;

    std::cin >> cacheSize >> numElem;
    assert(std::cin.good());
    
    hits = get_hits(argc, argv, cacheSize, numElem);
    if(hits < 0)
        return 1;

    std::cout << hits << std::endl;
    
    return 0;
}

int slow_get_page_int(int key)
{
    return key; 
}

cache_t choose_cache(int argc, char* argv[])
{
    if (argc < 2)
        return LRU;
    else if (argc > 2)
        return ERROR_TYPE_CACHE;

    else
    {
        if (strcmp(argv[1], "lru") == 0)
            return LRU;
        else if (strcmp(argv[1], "lfu") == 0)
            return LFU;
        else if (strcmp(argv[1], "perfect") == 0)
            return PERFECT;
        else
            return ERROR_TYPE_CACHE;
    }
}

int get_hits(int argc, char* argv[], const size_t cacheSize, const int numElem)
{
    cache_t cacheType = choose_cache(argc, argv);

    if(cacheType == LRU)
    {
        cache::lru_cache_t<int>cache{cacheSize};
  
        for (int i = 0; i < numElem; i++) 
        {
            int page;
            std::cin >> page;
            assert(std::cin.good());

            cache.lookup_update(page, slow_get_page_int);
        }

        return cache.get_hits();
    }

    if(cacheType == LFU)
    {
        cache::lfu_cache_t<int>cache{cacheSize};
  
        for (int i = 0; i < numElem; i++) 
        {
            int page;
            std::cin >> page;
            assert(std::cin.good());

            cache.lookup_update(page, slow_get_page_int);
        }

        return cache.get_hits();
    }

    if(cacheType == PERFECT)
    {
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
            cache.lookup_update(x, slow_get_page_int);
        
        return cache.get_hits();
    }

    return -1;
}
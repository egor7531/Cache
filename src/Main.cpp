#include <cassert>
#include <cstring>
#include <iostream>

#include "LRUcache.hpp"
#include "LFUcache.hpp"

int slow_get_page_int(int key);
int choose_cache(int argc, char* argv[]);
int get_hits(int argc, char* argv[], const size_t cacheSize, const int numElem);

int main(int argc, char* argv[])
{
    size_t cacheSize = 0;
    int numElem   = 0;
    int hits = 0;

    std::cout << "Enter cache size: ";
    std::cin >> cacheSize;

    std::cout << "Enter the number of elements: ";
    std::cin >> numElem;

    hits = get_hits(argc, argv, cacheSize, numElem);
    if(hits < 0)
        return 1;

    std::cout << "Number of hits: " << hits << std::endl;
    
    return 0;
}

int slow_get_page_int(int key)
{
    return key; 
}

int choose_cache(int argc, char* argv[])
{
    if (argc < 2)
        return 1;
    else if (argc > 2)
        return -1;

    else
    {
        if (strcmp(argv[1], "lru") == 0)
            return 1;
        else if (strcmp(argv[1], "lfu") == 0)
            return 2;
        else
            return -1;
    }
}

int get_hits(int argc, char* argv[], const size_t cacheSize, const int numElem)
{
    int cacheType = choose_cache(argc, argv);

    if(cacheType == 1)
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

    if(cacheType == 2)
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

    return -1;
}
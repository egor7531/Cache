#include <cassert>
#include <cstring>

#include "LRUCache.hpp"
#include "LFUCache.hpp"
#include "PerfectCache.hpp"

void choose_cache(int argc, char* argv[]);

int main(int argc, char* argv[])
{   
    choose_cache(argc, argv);
    
    return 0;
}

void choose_cache(int argc, char* argv[])
{
    assert(argc <= 2);

    if (argc < 2)
        lru_cache();
    else
    {
        if (strcmp(argv[1], "lru") == 0)
            lru_cache();
        else if (strcmp(argv[1], "lfu") == 0)
            lfu_cache();
        else if (strcmp(argv[1], "perfect") == 0)
            perfect_cache();
        else
            assert("Incorrect cache type input");
    }
}
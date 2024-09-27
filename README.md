# Cache
In this project, I am implementing my LRU, LFU and "perfect" caches. LFU is based on two lists: a cache list consisting of elements, each of which stores the number of hits and a list of elements with this number of hits (
you can read about it [here](https://ieftimov.com/posts/when-why-least-frequently-used-cache-implementation-golang /) ). The perfect cache is based on the idea that we know the future and leave in the cache those elements that will soon meet again.

As input, the user gives the cache size and the number of items that the cache will have to work with. At the output, the program outputs the number of hits.

# Build

```
cmake -S . -B build
cmake --build build
```
# Run

```
./build/src/cache [type of cache]
```
[type of cache] - lru, lfu, perfect (by default LRU)

# Run tests

```
./tests/runTests/LRU.sh
./tests/runTests/LFU.sh
./tests/runTests/Perfect.sh
```




<h1 align="center">Cache</h1>

# Description
In this project, I am implementing my LRU, LFU and "perfect" caches in C++. LFU is based on two lists: a cache list consisting of elements, each of which stores the number of hits and a list of elements with this number of hits (
you can read more about it [here](https://arpitbhayani.me/blogs/lfu/) ). The perfect cache is based on the idea that we know the future and leave in the cache those elements that will soon meet again.

As input, the user gives the cache size and the number of items that the cache will have to work with. At the output, the program outputs the number of hits.

# Build
```
git clone https://github.com/egor7531/Cache.git
cd Cache
cmake -S . -B build
cmake --build build
```
# Run
```
./build/src/lru
```
```
./build/src/lfu
```
```
./build/src/perfect 
```
# Run tests

```
./tests/runTests/LRU.sh
```
```
./tests/runTests/LFU.sh
```
```
./tests/runTests/Perfect.sh
```
# Support
This project is created by [egor7531](https://t.me/Nojey)



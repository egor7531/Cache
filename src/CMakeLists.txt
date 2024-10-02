cmake_minimum_required(VERSION 3.5)
project(src)		

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(lru LRUCache.cpp)
target_include_directories(lru PUBLIC ${INCLUDE_DIR})

add_executable(lfu LFUCache.cpp)
target_include_directories(lfu PUBLIC ${INCLUDE_DIR})

add_executable(perfect PerfectCache.cpp)
target_include_directories(perfect PUBLIC ${INCLUDE_DIR})

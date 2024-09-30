cmake_minimum_required(VERSION 3.11)

project(src)		

set(SRC_EXE Main.cpp)
set(SRC_LIB LRUCache.cpp PerfectCache.cpp LFUCache.cpp)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(getPage_lib STATIC GetPage.cpp)
add_library(caches_lib STATIC ${SRC_LIB})

target_include_directories(getPage_lib PUBLIC ${INCLUDE_DIR})
target_include_directories(caches_lib PUBLIC ${INCLUDE_DIR})

add_executable(cache ${SRC_EXE})
target_link_libraries(cache caches_lib getPage_lib)

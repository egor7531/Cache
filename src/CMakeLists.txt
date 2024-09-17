cmake_minimum_required(VERSION 3.30.3)

project(src)		

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(lru main.cpp)
target_include_directories(lru PUBLIC ${INCLUDE_DIR})


cmake_minimum_required(VERSION 3.30.3)

project(src)		

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(cache Main.cpp)
target_include_directories(cache PUBLIC ${INCLUDE_DIR})


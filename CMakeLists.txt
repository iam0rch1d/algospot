cmake_minimum_required(VERSION 3.17)
project(algospot)

set(CMAKE_CXX_STANDARD 20)

add_executable(picnic picnic.cpp)
add_executable(boardcover boardcover.cpp)
add_executable(clocksync clocksync.cpp)
add_executable(example_karatsuba example_karatsuba.cpp)
add_executable(quadtree quadtree.cpp)
add_executable(fence fence.cpp)
add_executable(fanmeeting fanmeeting.cpp)
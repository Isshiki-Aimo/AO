cmake_minimum_required(VERSION 3.22)
project(ACO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ACO
        main.cpp Information.h Ant.cpp Ant.h CVRP.cpp CVRP.h Graph.cpp Graph.h)

cmake_minimum_required(VERSION 3.22)
project(PSO)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(PSO
        main.cpp Information.h Coordinate.cpp Coordinate.h Particle.cpp Particle.h Graph.cpp Graph.h PSO.cpp PSO.h)

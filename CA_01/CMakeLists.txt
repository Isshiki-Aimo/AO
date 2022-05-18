cmake_minimum_required(VERSION 3.22)
project(CA_01)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CA_01
        Chromosome.h
        Information.h
        main.cpp
        Population.cpp
        Population.h)

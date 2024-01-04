cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ2_G1207)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(AED2324_PRJ2_G1207
        Airlines.h
        Airport.h
        csvInfo.cpp
        Graph.h
        main.cpp
        Airport.cpp
        Graph.cpp
        Airlines.cpp
        AuxiliarFunctions.cpp)

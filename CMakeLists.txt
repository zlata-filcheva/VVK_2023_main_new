cmake_minimum_required(VERSION 3.24)
project(VVK_2023_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(VVK_2023_main
        Studentas.h
        Studentas.cpp
        StudentuRusiavimas.cpp
        StudentuRusiavimas.h main1.cpp)

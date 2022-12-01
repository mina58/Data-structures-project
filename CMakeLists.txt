cmake_minimum_required(VERSION 3.22)
project(data_structures_project)

set(CMAKE_CXX_STANDARD 14
        AVL.h
        AVL.cpp
        )

add_executable(data_structures_project main.cpp AVL.cpp)

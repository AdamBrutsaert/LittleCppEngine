cmake_minimum_required(VERSION 3.22)

project (Genesis,
        VERSION 1.0
        DESCRIPTION "A simple self-made engine for learning purposes"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Genesis)
add_subdirectory(Sandbox)

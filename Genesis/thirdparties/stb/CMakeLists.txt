cmake_minimum_required(VERSION 3.22)
project(stb)

add_library(stb src/stb_image.cpp include/stb_image.h)
target_include_directories(stb PUBLIC include)

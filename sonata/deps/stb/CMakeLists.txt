cmake_minimum_required(VERSION 3.31.6)
project(stb LANGUAGES C)

add_library(stb STATIC
        include/stb_image.cpp)
target_include_directories(stb PUBLIC include)
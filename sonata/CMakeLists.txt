cmake_minimum_required(VERSION 3.31.6)

#add_subdirectory(deps)

add_library(sonata
    src/test.cpp
)

target_include_directories(sonata
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(sonata PUBLIC cxx_std_20)

#target_link_libraries(sonata
#        PUBLIC
#
#)

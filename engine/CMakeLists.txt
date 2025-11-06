cmake_minimum_required(VERSION 3.31.6)

#add_subdirectory(deps)

add_library(engine
    src/test.cpp
)

target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(engine PUBLIC cxx_std_20)

#target_link_libraries(engine
#        PUBLIC
#
#)

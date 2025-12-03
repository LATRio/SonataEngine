cmake_minimum_required(VERSION 3.31.6)
project(glad LANGUAGES C)

option(GLAD_BUILD_PIC "Build position independent code (-fPIC)" OFF)

add_library(glad STATIC
        src/gl.c
        include/glad/gl.h
)

target_include_directories(glad PUBLIC include)

target_compile_features(glad PRIVATE cxx_std_20)
set_target_properties(glad PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)


if (MSVC)
    target_compile_options(glad PRIVATE /W4 /WX /EHsc /std:c++20)
else ()
    target_compile_options(glad PRIVATE -Wall -Wextra -Werror)
    if(GLAD_BUILD_PIC)
        target_compile_options(glad PRIVATE -fPIC)
    endif()
endif ()
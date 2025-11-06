cmake_minimum_required(VERSION 3.31.6)

add_executable(sandbox
        src/sandbox.cpp
)

target_include_directories(sandbox
        PRIVATE
        src/
)

target_compile_features(sandbox PRIVATE cxx_std_20)
set_target_properties(sandbox PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

if (MSVC)
    target_compile_options(sandbox PRIVATE /W4 /WX /EHsc /std:c++20)
else ()
    target_compile_options(sandbox PRIVATE -Wall -Wextra -Wpedantic $<IF:$<CONFIG:Debug>,-Og,-O3>)
endif ()

target_link_libraries(sandbox
        PRIVATE
        sonata
)

cmake_minimum_required(VERSION 3.31.6)

add_subdirectory(deps)

add_library(sonata STATIC
        src/application.cpp
        src/window.cpp
)

target_include_directories(sonata
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(sonata PRIVATE cxx_std_20)
set_target_properties(sonata PROPERTIES
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_compile_definitions(sonata PRIVATE
        $<IF:$<CONFIG:Debug>,SONATA_DEBUG=1,SONATA_RELEASE=1>
)

if (MSVC)
    target_compile_options(sonata PRIVATE /W4 /WX /EHsc /std:c++20)
else ()
    target_compile_options(sonata PRIVATE -Wall -Wextra -Wpedantic $<IF:$<CONFIG:Debug>,-Og,-O3>)
endif ()

target_link_libraries(sonata
        PRIVATE
        glad
        glfw
)

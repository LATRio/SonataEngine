cmake_minimum_required(VERSION 3.31.6)

add_subdirectory(deps)

add_library(sonata STATIC
        src/application.cpp
        src/window.cpp
        src/log.cpp
        src/events/event.h
)

target_compile_features(sonata PRIVATE cxx_std_20)

enable_sanitizers(sonata)
set_project_warnings(sonata)

target_include_directories(sonata
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(sonata
        PRIVATE
        glad
        glfw
        spdlog::spdlog
)

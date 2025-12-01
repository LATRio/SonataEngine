cmake_minimum_required(VERSION 3.31.6)

add_subdirectory(deps)

add_library(sonata STATIC
        src/application.cpp
        src/application.hpp
        src/window.cpp
        src/window.hpp
        src/log.cpp
        src/log.hpp
        src/core.hpp
        src/sonata.hpp
        src/entry_point.hpp
        src/events/event.hpp
        src/events/app_event.hpp
        src/events/key_event.hpp
        src/events/mouse_event.hpp
        src/layers/layer.cpp
        src/layers/layer.hpp
        src/layers/layer_stack.cpp
        src/layers/layer_stack.hpp
        src/layers/imgui_layer.cpp
        src/layers/imgui_layer.hpp
        src/input.cpp
        src/input.hpp
        src/input_codes.hpp
)

target_compile_features(sonata PRIVATE cxx_std_20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_sanitizers(sonata)
set_project_warnings(sonata)

target_include_directories(sonata
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

message(STATUS "Flags CXX:                  ${CMAKE_CXX_FLAGS}")
message(STATUS "Flags CXX Debug:            ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Flags CXX RelWithDebInfo:   ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "Flags CXX Release:          ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "Flags CXX MinSizeRel:       ${CMAKE_CXX_FLAGS_MINSIZEREL}")

target_precompile_headers(sonata PRIVATE
        <functional>
        <memory>
        <string>
        <string_view>
        <format>
        <glad/gl.h>
        <GLFW/glfw3.h>
        <imgui.h>
)

target_link_libraries(sonata
        PRIVATE
        glad
        imgui
        spdlog::spdlog
)

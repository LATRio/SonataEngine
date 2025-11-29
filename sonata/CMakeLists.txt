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
)

target_compile_features(sonata PRIVATE cxx_std_20)

enable_sanitizers(sonata)
set_project_warnings(sonata)

target_include_directories(sonata
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

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

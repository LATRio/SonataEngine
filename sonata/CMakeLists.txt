option(SONATA_BUILD_SHARED "Build as shared library" FALSE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_subdirectory(deps)

if(SONATA_BUILD_SHARED)
    set(LIB_BUILD_TYPE "SHARED")
else()
    set(LIB_BUILD_TYPE "STATIC")
endif()

add_library(sonata ${LIB_BUILD_TYPE}
        src/application.cpp
        src/application.hpp
        src/window.cpp
        src/window.hpp
        src/core.hpp
        src/sonata.hpp
        src/entry_point.hpp
        src/input.cpp
        src/input.hpp
        src/input_codes.hpp
        src/glm_wrapper.hpp
        src/imgui_wrapper.hpp
        src/core/timestep.cpp
        src/core/timestep.hpp
        src/logger/log.cpp
        src/logger/log.hpp
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
        src/rendering/renderer.cpp
        src/rendering/renderer.hpp
        src/rendering/renderer_api.cpp
        src/rendering/renderer_api.hpp
        src/rendering/render_command.cpp
        src/rendering/render_command.hpp
        src/rendering/render_context.cpp
        src/rendering/render_context.hpp
        src/rendering/shader.cpp
        src/rendering/shader.hpp
        src/rendering/buffer.cpp
        src/rendering/buffer.hpp
        src/rendering/vertex_array.cpp
        src/rendering/vertex_array.hpp
        src/rendering/texture.cpp
        src/rendering/texture.hpp
        src/rendering/orthographic_camera.cpp
        src/rendering/orthographic_camera.hpp
        src/rendering/orthographic_camera_controller.cpp
        src/rendering/orthographic_camera_controller.hpp
        src/rendering/opengl/opengl_context.cpp
        src/rendering/opengl/opengl_context.hpp
        src/rendering/opengl/opengl_shader.cpp
        src/rendering/opengl/opengl_shader.hpp
        src/rendering/opengl/opengl_buffer.cpp
        src/rendering/opengl/opengl_buffer.hpp
        src/rendering/opengl/opengl_vertexarray.cpp
        src/rendering/opengl/opengl_vertexarray.hpp
        src/rendering/opengl/opengl_renderer_api.cpp
        src/rendering/opengl/opengl_renderer_api.hpp
        src/rendering/opengl/opengl_texture2d.cpp
        src/rendering/opengl/opengl_texture2d.hpp
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

target_precompile_headers(sonata PRIVATE
        <functional>
        <memory>
        <string>
        <string_view>
        <format>
        <glad/gl.h>
        <GLFW/glfw3.h>
        <imgui.h>
        <stb_image.h>
)

target_link_libraries(sonata
        PUBLIC
        glad
        imgui
        glm::glm
        spdlog::spdlog
        stb
)

cmake_minimum_required(VERSION 3.31.6)
project(imgui
        VERSION 1.92.5
        LANGUAGES C CXX
)

set(IMGUI_PLATFORM_BACKEND "glfw" CACHE STRING "Specify which imgui platform backend to use")
set(IMGUI_RENDERER_BACKEND "opengl3" CACHE STRING "Specify which imgui renderer backend to use")

set(IMGUI_SOURCES
    imgui.cpp
    imgui.h
    imconfig.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
)

set(IMGUI_PLATFORM_SOURCES
    backends/imgui_impl_${IMGUI_PLATFORM_BACKEND}.cpp
    backends/imgui_impl_${IMGUI_PLATFORM_BACKEND}.h
)

set(IMGUI_RENDERER_SOURCES
    backends/imgui_impl_${IMGUI_RENDERER_BACKEND}.cpp
    backends/imgui_impl_${IMGUI_RENDERER_BACKEND}.h
)

add_library(imgui STATIC
    ${IMGUI_SOURCES}
    ${IMGUI_PLATFORM_SOURCES}
    ${IMGUI_RENDERER_SOURCES}
)

target_compile_features(imgui PRIVATE cxx_std_20)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends
    ${IMGUI_GLFW_PATH}/include
)

target_link_libraries(imgui PRIVATE
    glfw
)
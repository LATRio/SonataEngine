#GLAD | 4.6 | Core
#spdlog | 1.16.0
#imgui | 1.92.5 | docking
#glm | 1.0.2
#stb_image | 2.3
#sdl3 | 3.4.0
#tracy | 0.13.1

if(SONATA_BUILD_SHARED)
    set(GLAD_BUILD_PIC ON)
endif()
add_subdirectory(glad)
target_precompile_headers(sonata PUBLIC <glad/gl.h>)
target_link_libraries(sonata PUBLIC glad)

#set(SPDLOG_USE_STD_FORMAT ON)
if(SONATA_BUILD_SHARED)
    set(SPDLOG_BUILD_PIC ON)
endif()
add_subdirectory(spdlog)
target_precompile_headers(sonata PUBLIC <spdlog/spdlog.h>)
target_link_libraries(sonata PUBLIC spdlog::spdlog)

if(SONATA_BUILD_SHARED)
    set(IMGUI_BUILD_PIC ON)
endif()
set(IMGUI_PLATFORM_BACKEND "sdl3")
set(IMGUI_RENDERER_BACKENDS "opengl3" "vulkan")
add_subdirectory(imgui)
target_precompile_headers(sonata PUBLIC <imgui.h>)
target_link_libraries(sonata PUBLIC imgui)

set(GLM_ENABLE_CXX_20 ON CACHE BOOL "Enable C++ 20" FORCE)
add_subdirectory(glm)
target_link_libraries(sonata PUBLIC glm::glm)

add_subdirectory(stb)
target_precompile_headers(sonata PUBLIC <stb_image.h>)
target_link_libraries(sonata PUBLIC stb)

set(SDL_CCACHE ON CACHE BOOL "Use Ccache to speed up build" FORCE)
set(SDL_OPENGL)
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(sdl3)
target_precompile_headers(sonata PUBLIC <SDL3/SDL.h>)
target_link_libraries(sonata PUBLIC SDL3::SDL3)

option(TRACY_ENABLE "" OFF)
option(TRACY_ON_DEMAND "" OFF)
add_subdirectory(tracy)
#target_compile_options(sonata PUBLIC <tracy/Tracy.hpp>)
target_link_libraries(sonata PUBLIC Tracy::TracyClient)

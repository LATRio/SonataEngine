#GLAD | 4.6 | Core
#spdlog | 1.16.0
#imgui | 1.92.5 | docking
#glm | 1.0.2
#stb_image | 2.3
#sdl3 | 3.4.0

if(SONATA_BUILD_SHARED)
    set(GLAD_BUILD_PIC ON)
endif()
add_subdirectory(glad)

#set(SPDLOG_USE_STD_FORMAT ON)
if(SONATA_BUILD_SHARED)
    set(SPDLOG_BUILD_PIC ON)
endif()
add_subdirectory(spdlog)

if(SONATA_BUILD_SHARED)
    set(IMGUI_BUILD_PIC ON)
endif()
set(IMGUI_PLATFORM_BACKEND "sdl3")
set(IMGUI_RENDERER_BACKEND "opengl3")
add_subdirectory(imgui)

set(GLM_ENABLE_CXX_20 ON CACHE BOOL "Enable C++ 20" FORCE)
add_subdirectory(glm)

add_subdirectory(stb)

set(SDL_CCACHE ON CACHE BOOL "Use Ccache to speed up build" FORCE)
set(SDL_OPENGL)
add_subdirectory(sdl3)

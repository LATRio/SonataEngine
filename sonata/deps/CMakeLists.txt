#GLAD | 4.6 | Core
#GLFW | 3.4
#spdlog | 1.16.0
#imgui | 1.92.5 | docking
#glm | 1.0.2
#stb_image | 2.3

if(SONATA_BUILD_SHARED)
    set(GLAD_BUILD_PIC ON)
endif()
add_subdirectory(glad)

set(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

#set(SPDLOG_USE_STD_FORMAT ON)
if(SONATA_BUILD_SHARED)
    set(SPDLOG_BUILD_PIC ON)
endif()
add_subdirectory(spdlog)

set(IMGUI_GLFW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
if(SONATA_BUILD_SHARED)
    set(IMGUI_BUILD_PIC ON)
endif()
add_subdirectory(imgui)

set(GLM_ENABLE_CXX_20 ON)
add_subdirectory(glm)

add_subdirectory(stb)

#GLAD | 4.6 | Core
#GLFW | 3.4
#spdlog | 1.16.0
#imgui | 1.92.5
#glm | 1.0.2

add_subdirectory(glad)

set(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

#set(SPDLOG_USE_STD_FORMAT ON)
add_subdirectory(spdlog)

set(IMGUI_GLFW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(imgui)

set(GLM_ENABLE_CXX_20 ON)
add_subdirectory(glm)

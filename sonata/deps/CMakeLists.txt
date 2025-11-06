#GLAD | 4.6 | Core
#GLFW | 3.4
#spdlog | 1.16.0

add_subdirectory(glad)

set(GLFW_BUILD_DOCS OFF)
add_subdirectory(glfw)

#set(SPDLOG_USE_STD_FORMAT ON)
add_subdirectory(spdlog)

cmake_minimum_required(VERSION 3.31.6)
project(SonataEngine
        VERSION 0.0.1
        LANGUAGES C CXX
)

include(cmake/Cache.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/StaticAnalyzers.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/DefaultProjectSettings.cmake)

add_subdirectory(sonata)
add_subdirectory(sandbox)

message(STATUS "Flags CXX:                  ${CMAKE_CXX_FLAGS}")
message(STATUS "Flags CXX Debug:            ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Flags CXX RelWithDebInfo:   ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "Flags CXX Release:          ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "Flags CXX MinSizeRel:       ${CMAKE_CXX_FLAGS_MINSIZEREL}")

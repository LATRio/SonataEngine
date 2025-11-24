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

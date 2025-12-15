set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(sandbox
        src/sandbox.cpp
        src/sandbox_2d.cpp
        src/sandbox_2d.hpp
)

target_compile_features(sandbox PRIVATE cxx_std_20)

enable_sanitizers(sandbox)
set_project_warnings(sandbox)

target_include_directories(sandbox
        PRIVATE
        src/
)

target_link_libraries(sandbox
        PRIVATE
        sonata
)

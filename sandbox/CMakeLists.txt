cmake_minimum_required(VERSION 3.31.6)

add_executable(Sandbox
        src/main.cpp
)

target_include_directories(Sandbox
        PRIVATE
        src/
)

target_compile_features(Sandbox PRIVATE cxx_std_20)

target_link_libraries(Sandbox
        PRIVATE
        engine
)

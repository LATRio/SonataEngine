option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)

if(ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --suppress=missingIncludeSystem --suppress=syntaxError
                --suppress=unmatchedSuppression --enable=all --inline-suppr --inconclusive
                --suppress=*:*_deps/* --suppress=*:*deps/*)
        message(STATUS "Cppcheck: ${CMAKE_CXX_CPPCHECK}")
    else()
        message(SEND_ERROR "cppcheck is not found")
    endif()
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY cppcheck)
    if(CLANG_TIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY} -extra-arg=-Wno-unknown-warning-option)
    else()
        message(SEND_ERROR "clang-tidy is not found")
    endif()
endif()

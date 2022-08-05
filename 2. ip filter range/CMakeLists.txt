cmake_minimum_required(VERSION 3.20)
project(task2)

include(conanbuildinfo.cmake)
conan_basic_setup()

set (SRC_DIR        ${PROJECT_SOURCE_DIR}/src)

set (SOURCES
    ${SRC_DIR}/main.cpp
)

add_executable(main ${SOURCES})
add_executable(test ${SRC_DIR}/test.cpp)

set_target_properties(main test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
cmake_minimum_required(VERSION 3.20)
project(test)

set (SRC_DIR        ${PROJECT_SOURCE_DIR}/src)

set (SOURCES
    ${SRC_DIR}/main.cpp
)

add_executable(main ${SOURCES}) 
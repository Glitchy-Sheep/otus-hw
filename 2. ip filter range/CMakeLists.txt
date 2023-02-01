cmake_minimum_required(VERSION 3.20)
project(ip_filter_conan)

include(conanbuildinfo.cmake)
conan_basic_setup()


set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)

set (TEST_DATA_DIRECTORY ${PROJECT_SOURCE_DIR}/test_data)

set (SOURCES
    ${SRC_DIR}/main.cpp
)

add_executable(main ${SOURCES})
add_executable(ip_data_test ${SRC_DIR}/test.cpp)

add_test(
    NAME ip_filter_test
    COMMAND ip_data_test
    WORKING_DIRECTORY ${TEST_DATA_DIRECTORY}
    )

enable_testing()


set_target_properties(main ip_data_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(MSVC)
  target_compile_options(main PRIVATE /W4 /WX)
else()
  target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
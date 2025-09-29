cmake_minimum_required(VERSION 4.0)
project(linkit)

set(CMAKE_CXX_STANDARD 26)

add_library(linkit INTERFACE
    include/linkit/precision.h
    include/linkit/vector3.h
    include/linkit/linkit.h
)

target_include_directories(linkit
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# For testing a header-only library
add_executable(test_linkit tests/test_main.cpp)
target_link_libraries(test_linkit PRIVATE linkit)
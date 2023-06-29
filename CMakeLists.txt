cmake_minimum_required(VERSION 3.25)
project(vt_serializer)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(test benchmark/benchmark.cpp)
add_executable(benchmark benchmark/benchmark.cpp)
add_executable(build_serializer example.cpp)
add_executable(test_membuf test/test_membuf.cpp)
cmake_minimum_required(VERSION 3.24)
project(vnet_serializer)

set(CMAKE_CXX_STANDARD 11)

add_executable(test benchmark/benchmark.cpp)
add_executable(benchmark benchmark/benchmark.cpp)
add_executable(build_serializer build_serializer.cpp)
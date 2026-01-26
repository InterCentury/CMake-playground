cmake_minimum_required(VERSION 3.20)

project(dxgi_gpu_name LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dxgi_gpu_name main.cpp)

target_link_libraries(dxgi_gpu_name PRIVATE dxgi)

cmake_minimum_required(VERSION 3.10)
project(NvapiLinkTest)

# Ensure we are building for x64 to match nvapi64.lib
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "This project requires a 64-bit compiler for nvapi64.lib")
endif()

add_executable(NvapiLinkTest main.cpp)

# Link the static library located in the root of the project
target_link_libraries(NvapiLinkTest 
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/nvapi64.lib"
)
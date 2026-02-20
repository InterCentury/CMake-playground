cmake_minimum_required(VERSION 3.10)
project(NvapiDetector CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force 64-bit check
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "NVAPI 64-bit requires an x64 target.")
endif()

add_executable(NvapiDetector main.cpp)

# Link the library directly from the root
target_link_libraries(NvapiDetector 
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/nvapi64.lib"
)
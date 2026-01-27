cmake_minimum_required(VERSION 3.20)

project(nvapi_test LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(nvapi_test main.cpp)

# NVAPI paths
set(NVAPI_DIR ${CMAKE_SOURCE_DIR}/Nvidia)

# Include nvapi.h
target_include_directories(nvapi_test PRIVATE
    ${NVAPI_DIR}
)

# Link nvapi library (64-bit)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_link_libraries(nvapi_test PRIVATE
        ${NVAPI_DIR}/nvapi64.lib
    )
else()
    target_link_libraries(nvapi_test PRIVATE
        ${NVAPI_DIR}/nvapi.lib
    )
endif()

# Windows system libs (safe + required)
target_link_libraries(nvapi_test PRIVATE
    user32
    gdi32
)

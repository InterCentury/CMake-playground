cmake_minimum_required(VERSION 3.10)
project(NvapiLinkTest)

set(CMAKE_CXX_STANDARD 17)

# Create the executable from your main.cpp
add_executable(NvapiLinkTest main.cpp)

# Link the 64-bit library located in your project root
target_link_libraries(NvapiLinkTest 
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/nvapi64.lib"
)
# CMake Commands Reference Guide

## Table of Contents
- [Basic Commands](#basic-commands)
- [Project Configuration](#project-configuration)
- [Variables and Cache](#variables-and-cache)
- [Target Commands](#target-commands)
- [File Operations](#file-operations)
- [Installation Commands](#installation-commands)
- [Testing Commands](#testing-commands)
- [Generator Expressions](#generator-expressions)
- [Control Flow](#control-flow)
- [Useful CMake Command Line Options](#useful-cmake-command-line-options)

## Basic Commands

### `cmake_minimum_required()`
```cmake
# Specifies the minimum required version of CMake
# Syntax: cmake_minimum_required(VERSION <major.minor[.patch]> [FATAL_ERROR])
cmake_minimum_required(VERSION 3.20)
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)  # Shows fatal error if version mismatch
```

### `project()`
```cmake
# Defines project name and languages
# Syntax: project(<PROJECT-NAME> [<language-name>...])
#        project(<PROJECT-NAME> [VERSION <major>[.<minor>[.<patch>]]] [DESCRIPTION <text>] [LANGUAGES <language-name>...])

project(MyProject)  # Basic project definition
project(MyProject VERSION 1.0.0)  # With version
project(MyProject LANGUAGES CXX C)  # With specific languages
project(MyProject LANGUAGES NONE)  # No languages
```

## Project Configuration

### `add_executable()`
```cmake
# Creates an executable target
# Syntax: add_executable(<name> [WIN32] [MACOSX_BUNDLE] [EXCLUDE_FROM_ALL] source1 [source2 ...])
#        add_executable(<name> IMPORTED [GLOBAL])

add_executable(myapp main.cpp utils.cpp)  # Basic executable
add_executable(myapp WIN32 main.cpp)  # Windows GUI application
add_executable(myapp MACOSX_BUNDLE main.cpp)  # macOS bundle
```

### `add_library()`
```cmake
# Creates a library target
# Syntax: add_library(<name> [STATIC | SHARED | MODULE] [EXCLUDE_FROM_ALL] source1 [source2 ...])

add_library(mylib STATIC lib.cpp)  # Static library
add_library(mylib SHARED lib.cpp)  # Shared library
add_library(mylib OBJECT lib.cpp)  # Object library (no linking, just objects)
add_library(mylib INTERFACE)  # Interface library (header-only, no sources)
```

### `add_subdirectory()`
```cmake
# Adds a subdirectory to the build
# Syntax: add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL])

add_subdirectory(src)  # Basic subdirectory
add_subdirectory(external/somelib build/somelib)  # With separate binary dir
add_subdirectory(tests EXCLUDE_FROM_ALL)  # Exclude from default build
```

## Variables and Cache

### `set()`
```cmake
# Sets a variable to the given value
# Syntax: set(<variable> <value>... [PARENT_SCOPE])
#        set(<variable> <value>... CACHE <type> <docstring> [FORCE])

set(SOURCES main.cpp utils.cpp)  # Normal variable
set(CMAKE_CXX_STANDARD 17)  # Setting CMake variable
set(MY_PATH "C:/Program Files/MyLib" CACHE PATH "Path to MyLib")  # Cache variable
set(MY_VAR "value" PARENT_SCOPE)  # Set in parent scope
```

### `option()`
```cmake
# Provides an option for the user to select
# Syntax: option(<variable> "<help_text>" [initial_value])

option(BUILD_TESTS "Build the tests" ON)  # ON by default
option(USE_OPENMP "Enable OpenMP parallelization" OFF)  # OFF by default
```

### `message()`
```cmake
# Displays a message to the user
# Syntax: message([<mode>] "message text")

message("Building project...")  # Simple message
message(STATUS "Found library: ${LIBRARY_PATH}")  # Status message
message(WARNING "This is deprecated")  # Warning message
message(AUTHOR_WARNING "Fix this later")  # Warning only for devs
message(SEND_ERROR "Fatal error")  # Error, continues but stops generation
message(FATAL_ERROR "Stop now")  # Fatal error, stops processing
```

## Target Commands

### `target_include_directories()`
```cmake
# Adds include directories to a target
# Syntax: target_include_directories(<target> [SYSTEM] [AFTER|BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...])

target_include_directories(myapp PRIVATE src/include)  # Private includes
target_include_directories(mylib PUBLIC include)  # Public includes (propagated)
target_include_directories(mylib INTERFACE include)  # Interface includes
target_include_directories(myapp SYSTEM PRIVATE /usr/include/boost)  # System includes (no warnings)
```

### `target_link_libraries()`
```cmake
# Specifies libraries to link against
# Syntax: target_link_libraries(<target> <item>...)
#        target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> <item>...)

target_link_libraries(myapp PRIVATE mylib)  # Link private dependency
target_link_libraries(mylib PUBLIC anotherlib)  # Propagate to dependents
target_link_libraries(myapp pthread)  # Link system library
target_link_libraries(myapp ${Boost_LIBRARIES})  # Link variable libraries
```

### `target_compile_definitions()`
```cmake
# Adds compile definitions to a target
# Syntax: target_compile_definitions(<target> <INTERFACE|PUBLIC|PRIVATE> [items1...])

target_compile_definitions(myapp PRIVATE DEBUG_MODE=1)  # Definition with value
target_compile_definitions(myapp PRIVATE USE_SSE)  # Simple definition
target_compile_definitions(mylib PUBLIC EXPORT_API)  # Propagated definition
```

### `target_compile_options()`
```cmake
# Adds compile options to a target
# Syntax: target_compile_options(<target> [BEFORE] <INTERFACE|PUBLIC|PRIVATE> [items1...])

target_compile_options(myapp PRIVATE -Wall -Wextra)  # GCC/Clang warnings
target_compile_options(myapp PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4>)  # Conditional MSVC option
```

### `target_sources()`
```cmake
# Adds sources to a target
# Syntax: target_sources(<target> <INTERFACE|PUBLIC|PRIVATE> [items1...])

target_sources(myapp PRIVATE newfile.cpp)  # Add source to existing target
target_sources(mylib PRIVATE ${SOURCES})  # Add from variable
```

### `target_properties`
```cmake
# Various target properties
set_target_properties(myapp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set_target_properties(mylib PROPERTIES
    OUTPUT_NAME "mylib_custom_name"
    POSITION_INDEPENDENT_CODE ON
)
```

## File Operations

### `file()`
```cmake
# File manipulation commands
# Syntax: file(<command> <arguments>)

file(GLOB SOURCES "src/*.cpp")  # Glob sources (avoid in modern CMake)
file(GLOB_RECURSE HEADERS "include/**/*.h")  # Recursive glob

file(READ "version.txt" VERSION_CONTENT)  # Read file contents
file(WRITE "output.txt" "Hello World")  # Write to file
file(APPEND "log.txt" "New entry\n")  # Append to file

file(COPY "config.json" DESTINATION "${CMAKE_BINARY_DIR}")  # Copy file
file(REMOVE "temp.txt")  # Delete file

file(MAKE_DIRECTORY "output")  # Create directory
file(DOWNLOAD "http://example.com/file.zip" "file.zip")  # Download file
```

### `configure_file()`
```cmake
# Copies a file and replaces variables
# Syntax: configure_file(<input> <output> [@ONLY] [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF]])

configure_file(config.h.in config.h)  # Configure header file
configure_file(version.txt.in version.txt @ONLY)  # Use @VAR@ instead of ${VAR}
```

### `include_directories()`
```cmake
# Old style, adds include directories globally (avoid if possible)
include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
```

## Installation Commands

### `install()`
```cmake
# Specifies installation rules
# Syntax: install(TARGETS <target>... [...])
#        install(FILES <file>... [...])

# Install targets
install(TARGETS myapp mylib
    RUNTIME DESTINATION bin  # Executables
    LIBRARY DESTINATION lib  # Shared libraries
    ARCHIVE DESTINATION lib  # Static libraries
)

# Install files
install(FILES "README.md" "LICENSE" DESTINATION "doc")

# Install directories
install(DIRECTORY "include/" DESTINATION "include"
    FILES_MATCHING PATTERN "*.h"
)

# Install scripts
install(SCRIPT "cmake/post_install.cmake")
```

## Testing Commands

### `enable_testing()` and `add_test()`
```cmake
# Enable testing for this directory and below
enable_testing()

# Add a test
add_test(NAME MyTest COMMAND myapp --test)

# Add test with arguments
add_test(NAME MathTest COMMAND test_math 5 10)

# Set test properties
set_tests_properties(MyTest PROPERTIES
    TIMEOUT 30
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)
```

## Generator Expressions

```cmake
# Generator expressions allow per-configuration values
# Syntax: $<condition:true_string>

target_compile_definitions(myapp PRIVATE
    $<$<CONFIG:Debug>:DEBUG_MODE>  # Only in Debug
    $<$<CONFIG:Release>:NDEBUG>    # Only in Release
)

target_include_directories(myapp PRIVATE
    $<$<PLATFORM_ID:Windows>:${WIN_INCLUDES}>
    $<$<PLATFORM_ID:Linux>:${LINUX_INCLUDES}>
)

target_link_libraries(myapp PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:shlwapi.lib>
)

# Complex condition
target_compile_options(myapp PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:-g3>
)
```

## Control Flow

### Conditional Statements
```cmake
# if/elseif/else/endif
if(BUILD_TESTS)
    add_subdirectory(tests)
elseif(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
else()
    message(STATUS "Not building tests or benchmarks")
endif()

# Check for variable
if(DEFINED MY_VAR)
    message("MY_VAR is defined")
endif()

# Check for command
if(COMMAND target_sources)
    message("Modern CMake detected")
endif()

# Check for platform
if(WIN32)
    message("Building on Windows")
elseif(APPLE)
    message("Building on macOS")
elseif(UNIX)
    message("Building on Unix/Linux")
endif()
```

### Loops
```cmake
# foreach
foreach(file ${SOURCE_FILES})
    message("Processing ${file}")
endforeach()

foreach(i RANGE 1 10)
    message("Number ${i}")
endforeach()

# while
set(counter 0)
while(counter LESS 5)
    message("Counter: ${counter}")
    math(EXPR counter "${counter} + 1")
endwhile()
```

### Functions and Macros
```cmake
# Function (new scope)
function(add_my_library NAME SOURCES)
    add_library(${NAME} ${SOURCES})
    target_include_directories(${NAME} PUBLIC include)
    
    # Set output variable
    set(${NAME}_UPPER "${NAME}" PARENT_SCOPE)
endfunction()

# Macro (no new scope)
macro(print_variable VAR)
    message("${VAR} = ${${VAR}}")
endmacro()
```

## Useful CMake Command Line Options

```bash
# Generate build system
cmake -S . -B build                    # Source dir, binary dir
cmake -S . -B build -G "Ninja"         # Use Ninja generator
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug  # Set variable

# Build the project
cmake --build build                     # Build default target
cmake --build build --target install    # Build install target
cmake --build build -- -j4              # Pass arguments to build tool

# Install
cmake --install build --prefix /usr/local  # Install with prefix

# Other useful commands
cmake --help                             # General help
cmake --help-command-list                 # List all commands
cmake --help-command add_library          # Help for specific command
cmake --system-information                # System information dump
```

## Common Variables

```cmake
# Project variables
${CMAKE_PROJECT_NAME}           # Name of the top-level project
${PROJECT_NAME}                  # Name of the current project
${PROJECT_SOURCE_DIR}            # Source directory of current project
${PROJECT_BINARY_DIR}            # Binary directory of current project

# Current context
${CMAKE_CURRENT_SOURCE_DIR}      # Current source directory
${CMAKE_CURRENT_BINARY_DIR}      # Current binary directory
${CMAKE_CURRENT_LIST_DIR}         # Directory of the current CMake file
${CMAKE_CURRENT_LIST_FILE}        # Current CMake file

# System
${CMAKE_SYSTEM_NAME}              # System name (Windows, Linux, Darwin)
${CMAKE_CXX_COMPILER_ID}          # Compiler ID (GNU, Clang, MSVC)
${CMAKE_BUILD_TYPE}                # Build type (Debug, Release)

# Paths
${CMAKE_SOURCE_DIR}                # Top-level source directory
${CMAKE_BINARY_DIR}                 # Top-level binary directory
${CMAKE_INSTALL_PREFIX}             # Installation prefix
```

---

## Best Practices Summary

1. **Modern CMake**: Use targets, avoid global commands
2. **Minimum required**: Always specify minimum version
3. **Avoid `file(GLOB)`**: Explicitly list sources
4. **Use `PRIVATE`/`PUBLIC`/`INTERFACE`**: Specify visibility correctly
5. **Use generator expressions**: For per-config settings
6. **Don't use global include/link directories**: Use target-specific commands
7. **Organize with functions**: Encapsulate reusable logic

This reference covers the most commonly used CMake commands. For complete documentation, refer to the official [CMake documentation](https://cmake.org/documentation/).
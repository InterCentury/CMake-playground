# CMake Build and Run Commands Guide

## Table of Contents
- [Basic CMake Commands](#basic-cmake-commands)
- [Build Commands](#build-commands)
- [Run/Execute Commands](#runexecute-commands)
- [Different Build Types](#different-build-types)
- [Clean Commands](#clean-commands)
- [Install Commands](#install-commands)
- [Platform Specific](#platform-specific)
- [Common Examples](#common-examples)
- [Troubleshooting](#troubleshooting)

## Basic CMake Commands

### Generate Build System
```bash
# Basic generation (in-source build - NOT RECOMMENDED)
cmake .

# Out-of-source build (RECOMMENDED)
mkdir build && cd build
cmake ..

# Specify source and build directories
cmake -S . -B build

# Specify generator
cmake -S . -B build -G "Unix Makefiles"
cmake -S . -B build -G "Ninja"
cmake -S . -B build -G "Visual Studio 17 2022"

# Set build type
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Set install prefix
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local

# With options
cmake -S . -B build -DBUILD_TESTS=ON -DUSE_OPENMP=OFF
```

## Build Commands

### Using CMake Build Command (Cross-Platform)
```bash
# Build default target
cmake --build build

# Build with specific config (multi-config generators like VS)
cmake --build build --config Release
cmake --build build --config Debug

# Build specific target
cmake --build build --target myapp
cmake --build build --target tests
cmake --build build --target install

# Build with parallel jobs
cmake --build build -j 4
cmake --build build --parallel 4

# Build with verbose output
cmake --build build --verbose

# Clean then build
cmake --build build --clean-first

# Pass arguments to underlying build tool
cmake --build build -- -j4  # For Makefiles/Ninja
```

### Using Generated Build Files

#### Makefiles (Unix/Linux/macOS)
```bash
cd build
make                   # Build default target
make -j4               # Build with 4 parallel jobs
make myapp             # Build specific target
make VERBOSE=1         # Build with verbose output
make clean             # Clean build files
```

#### Ninja
```bash
cd build
ninja                  # Build default target
ninja -j4              # Build with 4 parallel jobs
ninja myapp            # Build specific target
ninja -v               # Build with verbose output
ninja -t clean         # Clean build files
```

#### Visual Studio
```bash
# Using MSBuild
cd build
msbuild MyProject.sln /p:Configuration=Release
msbuild MyProject.sln /p:Configuration=Debug /m:4

# Using cmake build
cmake --build . --config Release
```

## Run/Execute Commands

### Run Executable After Build

#### Linux/macOS
```bash
# Run from build directory
cd build
./myapp
./myapp arg1 arg2

# Run with specific library path
LD_LIBRARY_PATH=./lib ./myapp

# Run and debug
gdb ./myapp
valgrind ./myapp
```

#### Windows
```bash
cd build
.\Release\myapp.exe
.\Debug\myapp.exe arg1 arg2

# Set PATH for DLLs
set PATH=%PATH%;%CD%\Release
myapp.exe
```

#### Combined Build and Run
```bash
# Build and run in one line
cmake --build build && ./build/myapp

# Build specific config and run
cmake --build build --config Release && ./build/Release/myapp

# With arguments
cmake --build build && ./build/myapp --test --verbose
```

## Different Build Types

### Debug Build
```bash
# Configure
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build/debug

# Run with debugging symbols
gdb ./build/debug/myapp
```

### Release Build
```bash
# Configure
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build/release

# Run optimized version
./build/release/myapp
```

### RelWithDebInfo Build
```bash
# Configure (optimized with debug symbols)
cmake -S . -B build/relwithdebug -DCMAKE_BUILD_TYPE=RelWithDebInfo

# Build
cmake --build build/relwithdebug
```

### MinSizeRel Build
```bash
# Configure (minimize size)
cmake -S . -B build/minsize -DCMAKE_BUILD_TYPE=MinSizeRel

# Build
cmake --build build/minsize
```

## Clean Commands

### Clean Build Files
```bash
# Remove build directory entirely (most thorough)
rm -rf build/
mkdir build && cd build

# Clean using CMake
cmake --build build --target clean

# Clean using build tool
cd build && make clean
cd build && ninja -t clean

# Clean specific target
cmake --build build --target clean-myapp
```

### Clean and Rebuild
```bash
# Clean first then build
cmake --build build --clean-first

# Or manually
rm -rf build/
cmake -S . -B build
cmake --build build
```

## Install Commands

### Install Built Files
```bash
# Install to default location
cmake --install build

# Install to specific prefix
cmake --install build --prefix /usr/local

# Install specific component
cmake --install build --component runtime

# Install with build tool
cd build && make install
cd build && ninja install
```

## Platform Specific

### Linux/macOS
```bash
# Configure and build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j $(nproc)  # Use all cores

# Run
./build/myapp

# Install
sudo cmake --install build
```

### Windows (Command Prompt)
```batch
:: Configure
cmake -S . -B build -G "Visual Studio 17 2022"

:: Build Release
cmake --build build --config Release -- /m

:: Run
build\Release\myapp.exe

:: Build Debug
cmake --build build --config Debug
```

### Windows (PowerShell)
```powershell
# Configure
cmake -S . -B build -G "Visual Studio 17 2022"

# Build
cmake --build build --config Release -- -m

# Run
.\build\Release\myapp.exe
```

### macOS (Xcode)
```bash
# Generate Xcode project
cmake -S . -B build -G Xcode

# Build with xcodebuild
xcodebuild -project build/myapp.xcodeproj -configuration Release

# Or use CMake
cmake --build build --config Release
```

## Common Examples

### Simple C++ Project
```bash
# 1. Configure
cmake -S . -B build

# 2. Build
cmake --build build

# 3. Run
./build/myapp

# One-liner
cmake -S . -B build && cmake --build build && ./build/myapp
```

### Project with Tests
```bash
# Configure with tests
cmake -S . -B build -DBUILD_TESTS=ON

# Build
cmake --build build

# Run tests
cd build && ctest
# or
cmake --build build --target test

# Run specific test
cd build && ctest -R TestName
```

### Multi-Config Project (Visual Studio/Xcode)
```bash
# Configure
cmake -S . -B build

# Build multiple configs
cmake --build build --config Debug
cmake --build build --config Release

# Run different configs
./build/Debug/myapp.exe
./build/Release/myapp.exe
```

### Cross-Compilation
```bash
# Using toolchain file
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=arm-linux-gnueabihf.cmake

# Build for target
cmake --build build

# Run on target (if possible)
qemu-arm ./build/myapp
```

## Troubleshooting

### Verbose Output
```bash
# See exact compiler commands
cmake --build build --verbose

# With make
make VERBOSE=1

# With ninja
ninja -v

# See CMake configuration details
cmake -S . -B build --trace
cmake -S . -B build --trace-expand  # Expand variables
```

### Common Issues and Solutions

```bash
# Problem: Cache issues
# Solution: Remove cache and reconfigure
rm -rf build/CMakeCache.txt build/CMakeFiles/
cmake -S . -B build

# Problem: Wrong generator
# Solution: Specify correct generator
cmake -S . -B build -G "Ninja"

# Problem: Missing dependencies
# Solution: Check and install dependencies
cmake -S . -B build 2>&1 | grep error

# Problem: Linker errors
# Solution: Verbose build to see link command
cmake --build build --verbose
```

### Useful CMake Flags
```bash
# Debug CMake variables
cmake -S . -B build -LAH  # List all cached variables with help

# Print variables without generating
cmake -S . -B build --graphviz=graph.dot

# Dry run
cmake -S . -B build --trace --trace-expand
```

## Quick Reference Card

### Most Used Commands
```bash
# Configure
cmake -S . -B build

# Build (Debug)
cmake --build build

# Build (Release)
cmake --build build --config Release

# Run
./build/myapp

# Clean
rm -rf build

# Install
cmake --install build

# Test
cd build && ctest
```

### Directory Structure Best Practice
```
project/
├── CMakeLists.txt
├── src/
├── include/
├── build/           # Ignored in git
│   ├── debug/
│   └── release/
└── myapp           # Built executable
```

### One-Line Build and Run
```bash
# Linux/macOS
cmake -S . -B build && cmake --build build && ./build/myapp

# Windows
cmake -S . -B build && cmake --build build --config Release && build\Release\myapp.exe
```

This guide covers the essential CMake commands for building and running projects. The actual commands may vary based on your specific project structure and requirements.
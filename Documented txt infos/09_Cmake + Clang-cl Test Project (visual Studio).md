# Creating a Test Project with CMake + clang-cl in Visual Studio

This guide walks you through creating and running a **minimal test C++ project** using:

* Visual Studio
* CMake
* clang-cl (LLVM)

No guesswork, no magic — just a clean, reproducible setup.

---

## What You’ll End Up With

* A simple CMake-based C++ project
* Built using **clang-cl**
* Opened and run directly inside **Visual Studio**

---

## Prerequisites

Make sure the following are installed:

### 1. Visual Studio

Install with these components:

* Desktop development with C++
* C++ CMake tools for Windows
* C++ Clang tools for Windows
* Windows 10/11 SDK

### 2. CMake

* Visual Studio already ships with CMake
* Optional: install standalone CMake for CLI usage

### 3. LLVM / clang-cl

* Installed automatically via Visual Studio Installer

---

## Step 1: Create Project Folder

Create a new empty folder anywhere you like:

```
clang-cl-test/
```

Inside it, create two files:

```
clang-cl-test/
├── CMakeLists.txt
└── main.cpp
```

---

## Step 2: Write main.cpp

```cpp
#include <iostream>

int main() {
    std::cout << "Hello from clang-cl + CMake + Visual Studio!" << std::endl;
    return 0;
}
```

Keep it simple — this is just a compiler test.

---

## Step 3: Write CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)

project(ClangCLTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(clang_cl_test main.cpp)
```

No toolchain yet — Visual Studio will handle that.

---

## Step 4: Open Project in Visual Studio (Correct Way)

This is important.

1. Open **Visual Studio**
2. Click **File → Open → Folder**
3. Select the `clang-cl-test` folder

Visual Studio will detect **CMakeLists.txt automatically**.

---

## Step 5: Select clang-cl Toolchain

1. In Visual Studio, open:

   * **Project → CMake Settings**
2. Select your active configuration (x64-Debug, x64-Release, etc.)
3. Set:

   * **Toolset** → `LLVM (clang-cl)`
4. Save settings

Visual Studio will reconfigure CMake.

---

## Step 6: Build the Project

Use any of the following:

* `Ctrl + Shift + B`
* Build → Build All

You should see Clang in the output logs:

```
clang-cl.exe /std:c++20 ...
```

That confirms clang-cl is active.

---

## Step 7: Run the Program

1. Set the executable as startup (usually automatic)
2. Press **Ctrl + F5** (Run without debugger)

Expected output:

```
Hello from clang-cl + CMake + Visual Studio!
```

Mission successful.

---

## Verifying clang-cl Is Actually Used

Check the build output for:

* `clang-cl.exe`
* `lld-link.exe` or `link.exe`

If you see `cl.exe`, you’re still on MSVC.

---

## Optional: Add Clang Warnings (Recommended)

Add this to `CMakeLists.txt`:

```cmake
if (MSVC)
    target_compile_options(clang_cl_test PRIVATE /W4 /permissive-)
endif()
```

This gives you stricter, cleaner diagnostics.

---

## Common Mistakes

### ❌ Opening as a Visual Studio Project

Do NOT use “New Project → Console App”.
Always open the **folder**, not a `.vcxproj`.

### ❌ Forgetting Toolset Switch

CMake defaults to MSVC unless explicitly changed.

### ❌ Missing Windows SDK

clang-cl still depends on MSVC libraries.

---

## Next Steps

Once this works, you can:

* Add more source files
* Enable AddressSanitizer
* Convert existing MSVC projects to CMake
* Move BinaryFetch to a cross-platform build system

---

## Summary

This setup gives you:

* Visual Studio UI
* CMake-based builds
* LLVM clang-cl compiler

Clean. Modern. Professional.

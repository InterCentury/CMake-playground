


# **BinaryFetch — Current Issue Documentation**

**Project:** BinaryFetch
**Author / Owner:** InterCentury
**Date:** 28 Jan 2026
**Purpose:** Track current development issues, blockers, and limitations for BinaryFetch.

---

## **1. Project Overview**

BinaryFetch is a **system information tool** written in C++ with a Windows focus, using Visual Studio / MSVC for development. It collects hardware and OS-level info, supports ASCII art display, and is being developed as a cross-platform tool eventually.

---

## **2. Current Issues / Pain Points**

### **2.1 Compiler / Build Issues**

**Problem:** Difficulty integrating BinaryFetch with compilers other than MSVC (GCC, Clang).

* **MSVC:** Works well natively (Visual Studio project).
* **GCC / MinGW / Clang:**

  * NVAPI integration fails — these compilers cannot link with NVIDIA NVAPI headers/libs easily.
  * Build scripts (`CMakeLists.txt`) aren’t fully compatible; manual tweaks needed.
  * Some Windows-specific APIs require MSVC-specific flags or runtime libraries.

**Status:**

* Project cannot be built reliably with GCC or Clang yet.
* Clang-cl (MSVC-compatible Clang) partially works but requires custom setup.

---

### **2.2 Linking Issues**

**Problem:** Linking with NVAPI and Windows system libraries is tricky outside Visual Studio.

* Static vs dynamic linking confusion: MSVC uses `.lib` and `.dll` differently than GCC/Clang.
* CMake sometimes fails to detect NVAPI `.lib` properly.
* Other system libraries may throw unresolved symbol errors.

**Impact:**

* Developers can’t experiment with non-MSVC compilers easily.
* Cross-platform goals are blocked.

---

### **2.3 Version Control / Project Management Frustrations**

**Problem:** Manual version control is heavy and disk-consuming.

* Each version is saved in a separate folder (`folder1`, `version1`, `folder2`, etc.).
* No Git or GitHub workflow implemented yet (planning post-exams).
* Risk of losing or overwriting changes is high.

**Impact:**

* Time is wasted managing versions instead of coding.
* Disk space consumption is unnecessarily high.

---

### **2.4 ASCII Art Integration**

**Problem:** ASCII art display in BinaryFetch sometimes causes formatting issues.

* Terminal/console width differences break alignment.
* Unicode / ANSI sequences may not render consistently across Windows consoles.

**Impact:**

* Visual output may appear broken on some systems.
* Requires testing across multiple consoles (Windows Terminal, PowerShell, cmd.exe).

---

### **2.5 Cross-Platform Goals**

**Problem:** Current project structure is heavily Windows-centric.

* Linux / macOS support is planned but not feasible now due to:

  * NVAPI dependency (Windows-only)
  * MSVC-specific build files
  * Platform-specific system calls

**Impact:**

* Limits audience to Windows users.
* Cross-platform abstraction layer needed in future.

---

### **2.6 Experimental / Developer Issues**

* **CMake analysis:** Needs proper setup to support multiple compilers.
* **Snapshot system:** Manual backups needed before experiments, otherwise crashes may lose work.
* **Error handling / debug output:** Currently verbose and sometimes cryptic for non-MSVC environments.

---

## **3. Summary of Struggles**

| Area               | Issue                      | Impact                                   |
| ------------------ | -------------------------- | ---------------------------------------- |
| Compiler           | GCC / Clang compatibility  | Cannot build outside MSVC                |
| Linking            | NVAPI and system libraries | Unresolved symbols, build fails          |
| Version Control    | Manual snapshot system     | Time-consuming, disk-heavy               |
| ASCII Art          | Console alignment          | Broken output on some terminals          |
| Cross-Platform     | Windows-centric design     | Cannot run on Linux/macOS                |
| Developer Workflow | CMake + debugging          | Risk of lost experiments, verbose errors |

---

## **4. Recommended Next Steps**

1. **Investigate Clang-cl / MinGW builds** to allow experimental non-MSVC compilation.
2. **Improve CMakeLists.txt** to handle library paths and NVAPI linking automatically.
3. **Consider Git integration** (even locally) to replace manual folder snapshots.
4. **Add terminal width detection** for ASCII art formatting.
5. **Plan cross-platform abstraction layer** for Linux/macOS support.

---

This document can serve as a **living issue tracker**. Every time a new blocker appears, you can add a line under “Current Issues” so it’s all in one place instead of scattered notes 😎.






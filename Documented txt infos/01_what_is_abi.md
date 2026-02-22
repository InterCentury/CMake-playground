# What is ABI?

ABI means **Application Binary Interface**.

An ABI is a set of rules that define how **compiled programs and libraries**
interact with each other at the **binary (machine code) level**.

ABI matters **after compilation**, not while writing code.

---

## What an ABI defines

An ABI specifies things like:

- How functions are called  
  (which registers are used, how arguments are passed, who cleans the stack)

- How function names appear in the binary  
  (name mangling)

- How data is laid out in memory  
  (structure padding, alignment, size)

- How classes work internally  
  (virtual tables, inheritance layout)

- How exceptions and RTTI behave

- How object files and libraries are linked

If two binaries do **not** follow the same ABI, they **cannot safely work together**.
Even if the source code looks correct, the program may:
- Fail to link
- Crash at runtime
- Behave incorrectly

---

## ABI vs API

API (Application Programming Interface):
- Source-level contract
- Defines how code is written and used

ABI (Application Binary Interface):
- Binary-level contract
- Defines how compiled code communicates

You can have the same API but a different ABI.

---

## Why ABI causes pain on Windows

On Windows, most precompiled libraries (like **NVAPI**) are built using
**MSVC’s ABI**.

That means:

- MSVC ✅ works with `nvapi.lib`
- clang-cl ✅ works with `nvapi.lib`
- clang++ (MinGW) ❌ does NOT work with `nvapi.lib`

Even though clang and clang-cl use the same frontend,
they generate **different ABIs**.

---

## Why C++ ABI is fragile

C++ ABI is complex because it includes:
- Name mangling
- Classes and templates
- Virtual functions
- Exceptions

C ABI is simpler and more stable, which is why C libraries are easier to link.

---

## Short version

ABI is the **binary contract** between compiled code.
If both sides don’t follow the same contract, nothing works.

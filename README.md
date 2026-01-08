
# C++ Cross-Platform Starter (CMake + vcpkg + Ninja + VS Code)

This template lets you build and debug a portable C++ project on **Windows (MinGW/Clang)** and **Linux (GCC/Clang)** with:

- **CMake** (with **Presets**) + **Ninja** generator
- Dependencies via **vcpkg manifest** (`vcpkg.json`)
- **VS Code** tasks & launch configs (C/C++ extension)
- **gdb** debugging on both Windows (MinGW) and Linux

> Main target: `cpp_starter`  
> Test target: `unit_tests` (Catch2 + CTest)

---

## Prerequisites

- **CMake ≥ 3.21**, **Ninja**, **Git**
- **VS Code** with **C/C++ extension**. (Optional but recommended: **CMake Tools** and **CodeLLDB**) 
- **Windows:** MinGW (providing `gcc/g++/gdb`) **or** LLVM Clang with `gdb` available in PATH. Set `VCPKG_ROOT` to `C:\vcpkg` (already encoded in Windows presets).
- **Linux:** `gcc/g++` (or `clang/clang++`) + `gdb` in PATH. Set `VCPKG_ROOT` to your vcpkg folder (e.g. `$HOME/vcpkg`).

Ensure `ninja` and your compiler are on `PATH`.

## Configure & Build (Terminal)

Pick a preset below (build directories live in `build/<preset>`):

```bash
# Windows (MinGW GCC)
cmake --preset win-gcc-debug
cmake --build --preset win-gcc-debug

# Windows (Clang)
cmake --preset win-clang-debug
cmake --build --preset win-clang-debug

# Linux (GCC)
cmake --preset linux-gcc-debug
cmake --build --preset linux-gcc-debug

# Run tests
ctest --preset linux-gcc-debug
```

Run the compiled app:

```bash
# Windows
build\win-gcc-debug\cpp_starter.exe
# Linux
./build/linux-gcc-debug/cpp_starter
```

## VS Code

- **Build:** `Terminal → Run Task…` and pick one of the `build: <preset>` tasks.
- **Debug:** `Run and Debug` panel and select a launch config matching your preset. These use **gdb**.
- **IntelliSense:**
  - If you install **CMake Tools**, IntelliSense is auto-provided from the active preset.
  - Otherwise, update `C_Cpp.default.compileCommands` in `.vscode/settings.json` to the preset you use (path to `compile_commands.json`).

## Dependencies (vcpkg)

Dependencies are declared in `vcpkg.json`. CMake Presets pass the vcpkg toolchain automatically:

- `fmt` for printing in `main.cpp`
- `catch2` for tests discovered by CTest (`catch_discover_tests`).

You can add more packages to `vcpkg.json`, then reconfigure.

## Notes

- On Windows, these presets assume `VCPKG_ROOT=C:\\vcpkg`. Adjust if your path differs.
- If you want to debug with **LLDB** on Windows, install the `CodeLLDB` extension and add a separate `launch.json` entry with `type: lldb` (or keep gdb if you use MinGW).
- To create a Release build, use the `*-release` presets.

## License
MIT


## MSVC (Visual Studio toolchain)

Presets for **MSVC** using the **Visual Studio 17 2022** generator:

```bash
cmake --preset win-msvc-vs-debug
cmake --build --preset win-msvc-vs-debug
ctest --preset win-msvc-vs-debug
```

- vcpkg triplet for MSVC is **`x64-windows`** (dynamic). Use `x64-windows-static` if you prefer static linking.
- Visual Studio generator is **multi-config**; binaries are under `build/win-msvc-vs-debug/Debug/` or `.../Release/`.
- `compile_commands.json` is **not** produced by VS generator; IntelliSense is provided by **CMake Tools**.
- Debug via **cppvsdbg** from `Run and Debug` → *Launch (Windows MSVC / Visual Studio)*.

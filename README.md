
# Developer README — Build & Debug Guide 🔧

A concise checklist and step-by-step instructions to set up, compile, test, and debug this project on Windows and Linux.

---

## ✅ What this project uses

- C++20
- CMake (Presets) — configured for multiple toolchains
- Ninja (default generator in presets)
- vcpkg (manifest mode) for dependency management (`vcpkg.json`)
- Dependencies: `fmt` (runtime), `catch2` (unit tests)

---

## 🚨 Minimum requirements

- **CMake ≥ 3.21** (required by `CMakePresets.json`)
- **Ninja** (default generator)
- **Git**
- A C++20-capable toolchain:
  - **Windows:** Visual Studio 2022 (MSVC), or MinGW-w64 (gcc/g++), or LLVM/Clang (clang/clang-cl)
  - **Linux:** gcc/g++ (build-essential) or clang/clang++
- **vcpkg** (cloned & bootstrapped) — required by presets to provide `fmt` and `catch2`
- Debuggers: **gdb** (MinGW/Linux), **cppvsdbg** (Visual Studio), or **lldb** (optional)
- **VS Code** (optional but highly recommended) with **C/C++** extension

---

## 📥 Downloads & Installation

### 1. **CMake** (≥ 3.21)

- **Windows & Linux:** https://cmake.org/download/
  - Windows: Download `.msi` (installer) or `.zip` (portable)
  - Linux: Use package manager (`sudo apt install cmake` on Ubuntu/Debian) or download from above
- **Verify:** `cmake --version`

### 2. **Ninja** (build generator)

- **Windows & Linux:** https://github.com/ninja-build/ninja/releases
  - Download the latest release binary for your OS
  - Extract and add to PATH
- **macOS:** `brew install ninja`
- **Linux:** `sudo apt install ninja-build` (Ubuntu/Debian)
- **Verify:** `ninja --version`

### 3. **Git**

- **Windows:** https://git-scm.com/download/win (installer)
- **Linux:** `sudo apt install git` (Ubuntu/Debian)
- **macOS:** `brew install git`
- **Verify:** `git --version`

### 4. **Compiler Toolchain**

#### Option A: **Visual Studio 2022 (MSVC)** — Windows only

- Download: https://visualstudio.microsoft.com/vs/
- Install "Desktop development with C++" workload
- Includes compiler, debugger (cppvsdbg), and linker
- **Verify:** `cl.exe /?` in Visual Studio Command Prompt

#### Option B: **MinGW-w64 (gcc/g++/gdb)** — Windows

- Download: https://www.mingw-w64.org/ or https://winlibs.com/
- Popular builds: WinLibs standalone, MSYS2, or TDM-GCC
- **Quick (WinLibs):**
  1. Download latest release from https://winlibs.com/
  2. Extract to a folder (e.g., `C:\mingw64`)
  3. Add `C:\mingw64\bin` to PATH
- **Verify:** `gcc --version`, `g++ --version`, `gdb --version`

#### Option C: **LLVM/Clang** — Windows/Linux

- Download: https://releases.llvm.org/
  - Windows: `.exe` installer or `.zip`
  - Linux: Pre-built binaries or use package manager (`sudo apt install clang`)
- Extract/install and add to PATH
- **Verify:** `clang --version`, `clang++ --version`

#### Option D: **GCC/G++/GDB** — Linux (most common)

- **Ubuntu/Debian:**
  ```bash
  sudo apt update
  sudo apt install build-essential gdb
  ```
- **Fedora/RHEL:**
  ```bash
  sudo dnf install gcc g++ gdb
  ```
- **Verify:** `gcc --version`, `g++ --version`, `gdb --version`

### 5. **vcpkg** (dependency manager)

- **Clone from GitHub:**
  ```bash
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  ```

- **Bootstrap (required once):**
  - **Windows:** `.\bootstrap-vcpkg.bat`
  - **Linux/macOS:** `./bootstrap-vcpkg.sh`

- **Set `VCPKG_ROOT` environment variable:**
  - **Windows (Command Prompt):**
    ```cmd
    setx VCPKG_ROOT C:\vcpkg
    ```
  - **Windows (PowerShell):**
    ```powershell
    [Environment]::SetEnvironmentVariable("VCPKG_ROOT", "C:\vcpkg", "User")
    ```
  - **Linux/macOS (add to `~/.bashrc` or `~/.zshrc`):**
    ```bash
    export VCPKG_ROOT=$HOME/vcpkg
    ```

- **Verify:** `$env:VCPKG_ROOT` (Windows PowerShell) or `echo $VCPKG_ROOT` (Linux/bash)
- **Manual package install (optional):**
  ```bash
  vcpkg install fmt catch2 --triplet x64-windows  # Windows MSVC
  vcpkg install fmt catch2 --triplet x64-mingw-dynamic  # Windows MinGW
  vcpkg install fmt catch2 --triplet x64-linux  # Linux
  ```

### 6. **VS Code** (optional, recommended)

- Download: https://code.visualstudio.com/
- Install these extensions:
  - **C/C++** (Publisher: Microsoft) — `ms-vscode.cpptools`
  - **CMake Tools** (Publisher: Microsoft) — `ms-vscode.cmake-tools`
  - **CodeLLDB** (Publisher: Vadim Chugunov, optional) — `vadimcn.vscode-lldb`
- Via CLI: `code --install-extension ms-vscode.cpptools ms-vscode.cmake-tools`

---

## ✔️ Setup checklist (Windows with MSVC + vcpkg)

- [ ] CMake ≥ 3.21 installed and in PATH
- [ ] Ninja installed and in PATH
- [ ] Git installed
- [ ] Visual Studio 2022 installed with C++ tools
- [ ] vcpkg cloned to `C:\vcpkg` and bootstrapped
- [ ] `VCPKG_ROOT=C:\vcpkg` environment variable set
- [ ] (Optional) VS Code with C/C++ extension installed

Then run: `cmake --preset win-msvc-vs-debug` to test

---

## ✔️ Setup checklist (Linux with GCC + vcpkg)

- [ ] `sudo apt install cmake ninja-build git build-essential gdb` (Ubuntu/Debian)
- [ ] vcpkg cloned to `$HOME/vcpkg` and bootstrapped
- [ ] `VCPKG_ROOT=$HOME/vcpkg` in shell config (`~/.bashrc`, `~/.zshrc`, etc.)
- [ ] (Optional) VS Code with C/C++ extension installed

Then run: `cmake --preset linux-gcc-debug` to test

---

## 🔧 Install vcpkg (quick)

1. Clone vcpkg:

   ```bash
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   # Windows
   .\bootstrap-vcpkg.bat
   # Linux/macOS
   ./bootstrap-vcpkg.sh
   ```

2. (Optional) Install packages manually for your triplet:

   ```bash
   # example (Windows MSVC)
   .\vcpkg.exe install fmt catch2 --triplet x64-windows
   ```

3. Set `VCPKG_ROOT` environment variable (or update presets):

   - Windows: `VCPKG_ROOT=C:\vcpkg` (presets assume this path)
   - Linux: `VCPKG_ROOT=$HOME/vcpkg`

Note: You can rely on manifest mode; if `vcpkg` is available and `CMAKE_TOOLCHAIN_FILE` points to `vcpkg.cmake`, the required packages from `vcpkg.json` are installed automatically when configuring.

---

## 📂 Project Structure Explained

```
.
├── CMakeLists.txt              # Build configuration (CMake recipe)
├── CMakePresets.json           # Build presets (compiler, generator, settings)
├── vcpkg.json                  # Dependencies manifest (fmt, catch2)
├── src/
│   └── main.cpp                # Your application code (entry point)
├── tests/
│   ├── CMakeLists.txt          # Test build configuration
│   └── test_example.cpp        # Example unit tests (Catch2)
├── build/                      # Generated build output (created by CMake)
│   ├── win-msvc-vs-debug/      # MSVC Debug build folder
│   ├── win-gcc-debug/          # MinGW Debug build folder
│   └── ...                     # Other preset build folders
└── .vscode/
    ├── launch.json             # Debug launch configurations
    └── tasks.json              # Build tasks for VS Code
```

**Key files for beginners:**
- `src/main.cpp` — Your application starts here; edit this to change program behavior
- `vcpkg.json` — Add libraries here (e.g., `"boost"` for Boost libraries)
- `CMakeLists.txt` — Defines how to build; add new source files here
- `tests/test_example.cpp` — Example unit tests; add your own tests here

---

## 🚀 First-Time Quick Start (Windows MSVC)

1. **Install everything** (see "📥 Downloads & Installation" section above)
   - Visual Studio 2022 (with C++ tools)
   - CMake, Ninja, Git, vcpkg

2. **Set `VCPKG_ROOT` environment variable:**
   ```powershell
   [Environment]::SetEnvironmentVariable("VCPKG_ROOT", "C:\vcpkg", "User")
   # Then restart VS Code / terminal
   ```

3. **Open VS Code and open this folder** (File → Open Folder)

4. **Configure the build:**
   ```bash
   cmake --preset win-msvc-vs-debug
   ```
   This creates a `build/win-msvc-vs-debug/` folder with Visual Studio project files.

5. **Build the project:**
   ```bash
   cmake --build --preset win-msvc-vs-debug
   ```
   Compiles the code; output is `build/win-msvc-vs-debug/Debug/cpp_starter.exe`

6. **Run the executable:**
   ```bash
   .\build\win-msvc-vs-debug\Debug\cpp_starter.exe
   ```
   You should see output from the program.

7. **Run tests:**
   ```bash
   ctest --preset win-msvc-vs-debug
   ```
   Runs all unit tests in the `tests/` folder.

8. **Debug in VS Code:**
   - Press Ctrl+Shift+D (Run and Debug)
   - Select "Debug (Windows MSVC / Visual Studio)"
   - Press F5
   - VS Code will build, run, and stop at breakpoints

---

## 🚀 First-Time Quick Start (Linux GCC)

1. **Install everything:**
   ```bash
   sudo apt update
   sudo apt install cmake ninja-build git build-essential gdb
   git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
   cd ~/vcpkg && ./bootstrap-vcpkg.sh
   ```

2. **Set `VCPKG_ROOT`:**
   ```bash
   echo 'export VCPKG_ROOT=$HOME/vcpkg' >> ~/.bashrc
   source ~/.bashrc
   ```

3. **Open this folder in VS Code**

4. **Configure:**
   ```bash
   cmake --preset linux-gcc-debug
   ```

5. **Build:**
   ```bash
   cmake --build --preset linux-gcc-debug
   ```
   Output: `build/linux-gcc-debug/cpp_starter`

6. **Run:**
   ```bash
   ./build/linux-gcc-debug/cpp_starter
   ```

7. **Debug in VS Code:**
   - Ctrl+Shift+D → Select "Debug (Linux GCC + gdb)" → F5

---

## 💡 Understanding the Code

### main.cpp (Your Application)

```cpp
#include <fmt/core.h>  // Library for formatted printing

int main() {
    fmt::println("Hello, C++!");  // Print to console
    return 0;  // Exit successfully
}
```

**To modify:**
1. Edit `src/main.cpp`
2. Save
3. Run `cmake --build --preset <your-preset>`
4. Run the executable

### test_example.cpp (Unit Tests)

```cpp
#include <catch2/catch_test_macros.hpp>

TEST_CASE("string size", "[string]") {
    std::string s = "abc";
    REQUIRE(s.size() == 3);  // Test passes if size == 3
}
```

**To add more tests:**
1. Edit `tests/test_example.cpp`
2. Add more `TEST_CASE(...)` blocks
3. Run `ctest --preset <your-preset>` to run all tests

---

## 📦 Adding Dependencies (vcpkg)

### Example: Add the Boost library

1. **Edit `vcpkg.json`:**
   ```json
   {
     "name": "cpp-starter",
     "dependencies": [
       "fmt",
       "catch2",
       "boost"  // Add this line
     ]
   }
   ```

2. **Reconfigure (this auto-installs the package):**
   ```bash
   cmake --preset linux-gcc-debug
   ```

3. **Use in code (`src/main.cpp`):**
   ```cpp
   #include <boost/version.hpp>
   #include <fmt/core.h>
   
   int main() {
       fmt::println("Boost version: {}", BOOST_LIB_VERSION);
   }
   ```

4. **Update CMakeLists.txt to link the library:**
   ```cmake
   find_package(boost CONFIG REQUIRED)
   target_link_libraries(cpp_starter PRIVATE boost::boost)
   ```

5. **Rebuild:**
   ```bash
   cmake --build --preset linux-gcc-debug
   ```

**Popular packages:** `boost`, `sqlite3`, `curl`, `json`, `spdlog`, `nlohmann-json`

Browse available packages: https://vcpkg.io/

---

## ➕ Adding New Source Files

### Scenario: Add `utils.cpp` and `utils.h`

1. **Create files:**
   - `src/utils.h`
   - `src/utils.cpp`

2. **Edit `src/utils.h`:**
   ```cpp
   #pragma once
   
   int add(int a, int b);
   ```

3. **Edit `src/utils.cpp`:**
   ```cpp
   #include "utils.h"
   
   int add(int a, int b) {
       return a + b;
   }
   ```

4. **Edit `CMakeLists.txt`:**
   ```cmake
   add_executable(cpp_starter src/main.cpp src/utils.cpp)  # Add src/utils.cpp
   ```

5. **Edit `src/main.cpp`:**
   ```cpp
   #include "utils.h"
   #include <fmt/core.h>
   
   int main() {
       int result = add(2, 3);
       fmt::println("2 + 3 = {}", result);
   }
   ```

6. **Rebuild:**
   ```bash
   cmake --build --preset linux-gcc-debug
   ```

---

## ❌ Troubleshooting Common Issues

| Problem | Cause | Solution |
|---------|-------|----------|
| `cmake: command not found` | CMake not installed or not in PATH | Install CMake (see 📥 section) and add to PATH |
| `ninja: command not found` | Ninja not installed or not in PATH | Install Ninja and add to PATH |
| `vcpkg.cmake not found` | `VCPKG_ROOT` not set or invalid | Set `VCPKG_ROOT` environment variable and restart terminal |
| `fmt not found` | vcpkg packages not installed | Run `cmake --preset <preset>` to auto-install (manifest mode) |
| Build fails: `cannot find -lgcc_s` (MinGW) | MinGW not in PATH or incompatible version | Add MinGW `bin` folder to PATH; ensure 64-bit version |
| Debugger won't start | Wrong debugger path or binary not built | Ensure preset was built first; check `miDebuggerPath` in `launch.json` |
| `gdb: command not found` (Linux) | gdb not installed | Run `sudo apt install gdb` |
| Linker errors (MSVC) | Incompatible architecture or toolset | Ensure preset matches (x64-windows); rebuild with `--clean-first` |

---

## 📚 Glossary for Beginners

| Term | Meaning |
|------|---------|
| **CMake** | Build system that generates compiler-specific project files |
| **Preset** | Pre-configured build settings (compiler, flags, output folder) |
| **Ninja** | Fast build tool (alternative to Make, Visual Studio) |
| **vcpkg** | Package manager for C++ libraries (like npm for C++) |
| **Toolchain** | Collection of tools: compiler (gcc/clang/msvc), linker, debugger |
| **Manifest mode** | Auto-install dependencies from `vcpkg.json` during CMake configure |
| **Triplet** | vcpkg's way to specify target (e.g., `x64-windows`, `x64-linux`) |
| **Debug** | Build with symbols for debugging; slower, larger binary |
| **Release** | Build optimized for speed; no debug symbols |
| **CTest** | CMake's testing tool (runs all `add_test()` targets) |
| **gdb** | GNU debugger (command-line tool) |
| **cppvsdbg** | Visual Studio C++ debugger |
| **lldb** | LLVM debugger (alternative to gdb) |

---

## 🎓 Next Steps (Learning Path)

1. **Modify `main.cpp`** — Change the output message, add variables, use loops
2. **Add a new source file** — Practice with `utils.cpp` as shown above
3. **Add dependencies** — Try adding `spdlog` (logging library) or `json` (JSON parsing)
4. **Write unit tests** — Add `TEST_CASE` entries in `tests/test_example.cpp`
5. **Use VS Code debugger** — Set breakpoints and step through code
6. **Try different presets** — Compile with GCC, Clang, MSVC to compare
7. **Read CMakeLists.txt** — Understand how the build is configured
8. **Explore C++20 features** — Lambda expressions, concepts, ranges, coroutines

---

## ⚙️ Configure & build (recommended workflow)

Run these from the repository root.

- Configure + generate using a preset (examples):

  ```bash
  cmake --preset win-gcc-debug        # Windows, MinGW (Debug)
  cmake --preset win-clang-debug      # Windows, clang-cl (Debug)
  cmake --preset linux-gcc-debug      # Linux, gcc (Debug)
  cmake --preset win-msvc-vs-debug    # Windows, Visual Studio generator
  ```

- Build:

  ```bash
  cmake --build --preset linux-gcc-debug
  # or for MSVC multi-config (Debug/Release):
  cmake --build --preset win-msvc-vs-debug --config Debug
  ```

- Run tests:

  ```bash
  ctest --preset linux-gcc-debug
  # or for a specific config when using MSVC: ctest --preset win-msvc-vs-debug --config Debug
  ```

- Run the executable:

  - Windows (MinGW/Clang): `build\<preset>\cpp_starter.exe`
  - Linux: `./build/<preset>/cpp_starter`
  - MSVC (multi-config): `build/win-msvc-vs-debug/Debug/cpp_starter.exe`

---

## 🧭 Debugging

- Visual Studio (MSVC): Open `build/win-msvc-vs-debug/CppStarter.sln` or use `cmake --preset win-msvc-vs-debug` and then **Open Folder** in VS 2022; run with the built-in debugger (cppvsdbg).

- VS Code (recommended):
  - Install extensions: **C/C++** (ms-vscode.cpptools), **CMake Tools** (ms-vscode.cmake-tools), and **CodeLLDB** (vadimcn.vscode-lldb) if you need LLDB.
  - Use the `Terminal → Run Task…` items (these map to the included presets) or the **CMake Tools** UI to select a preset and build.
  - Add a `launch.json` entry pointing to the built binary if one is not present (type `cppdbg` for gdb/cppvsdbg or `lldb` for lldb).

- gdb/LLDB (CLI): `gdb --args ./build/linux-gcc-debug/cpp_starter` or `lldb ./build/linux-clang-debug/cpp_starter`.

---

## ✔️ Common troubleshooting

- CMake complains about `CMAKE_TOOLCHAIN_FILE` or missing packages: ensure `VCPKG_ROOT` points to a bootstrapped vcpkg directory and that `vcpkg` is bootstrapped.
- `ninja: error: unknown target` or `ninja not found`: install `ninja` and add to PATH.
- On Windows with MinGW: add the MinGW `bin` folder to PATH so `gcc`, `g++`, and `gdb` are found.
- If using MSVC presets but `compile_commands.json` is required: use a Ninja or Make generator variant or rely on the CMake Tools for IntelliSense.

---

## Quick commands summary

- Configure: `cmake --preset <preset>`
- Build: `cmake --build --preset <preset>`
- Test: `ctest --preset <preset>`
- Install (if needed): `cmake --install build/<preset>`

---

---

## 📝 VS Code Configurations (Pre-configured)

This project already includes `.vscode/launch.json` and `.vscode/tasks.json` with build and debug configurations.

### Launch Configurations (Debug)

The `.vscode/launch.json` includes:

| Name | Debugger | Preset | Binary Path |
|------|----------|--------|-------------|
| Debug (Windows MSVC / Visual Studio) | cppvsdbg | win-msvc-vs-debug | `build/win-msvc-vs-debug/Debug/cpp_starter.exe` |
| Debug (Windows MinGW / GCC + gdb) | cppdbg (gdb) | win-gcc-debug | `build/win-gcc-debug/cpp_starter.exe` |
| Debug (Windows Clang + gdb) | cppdbg (gdb) | win-clang-debug | `build/win-clang-debug/cpp_starter.exe` |
| Debug (Linux GCC + gdb) | cppdbg (gdb) | linux-gcc-debug | `build/linux-gcc-debug/cpp_starter` |
| Debug (Linux Clang + gdb) | cppdbg (gdb) | linux-clang-debug | `build/linux-clang-debug/cpp_starter` |

**Usage:** Open VS Code → **Run and Debug** (Ctrl+Shift+D) → Select a configuration → Press **F5**

Each launch config will:
1. Run the corresponding build task first (`preLaunchTask`)
2. Launch the compiled binary in the debugger
3. Display output in the integrated terminal

### Build Tasks (Configure & Build)

The `.vscode/tasks.json` includes tasks for all presets:

**Configure tasks:** `configure: <preset>`
- Example: `configure: linux-gcc-debug`

**Build tasks:** `build: <preset>`
- Example: `build: linux-gcc-debug`

**Test tasks:** `test: <preset>`
- Example: `test: linux-gcc-debug`

**Composite tasks:** `build-and-run: <preset>` (configure + build in sequence)
- Example: `build-and-run: win-msvc-vs-debug`

**Usage:** 
- Terminal → Run Task (Ctrl+Shift+P → "Tasks: Run Task")
- Or use the terminal directly: `cmake --preset linux-gcc-debug`

### Quick Start (VS Code)

1. Install extensions: **C/C++**, **CMake Tools**, (optional: **CodeLLDB**)
2. Open the project folder in VS Code
3. Select a debug configuration from **Run and Debug** panel (Ctrl+Shift+D)
4. Press **F5** to build and debug
5. Or run build tasks manually from **Terminal → Run Task**

---

## 🔍 Customizing Configurations

- **MinGW path:** Edit `launch.json` → search for `C:\\mingw64` and replace with your MinGW path
- **GDB path:** For Linux, if gdb is not in the default location, update `miDebuggerPath`
- **Additional compilers:** Add new entries in `.vscode/tasks.json` for additional presets or compilers
- **Environment variables:** Modify `environment` sections in `launch.json` if needed

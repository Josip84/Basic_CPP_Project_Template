# 1. Clean the old build directory
Remove-Item -Recurse -Force build\win-clang-debug -ErrorAction SilentlyContinue

# 2. Configure (generate build files)
cmake --preset win-clang-debug

# 3. Build
cmake --build --preset win-clang-debug


# Common CMake Workflow

Remember this pattern for CMake presets:

Configure (generates build system):     cmake --preset <preset-name>
Build (compiles code):                  cmake --build --preset <preset-name>
Test (runs tests):                      ctest --preset <preset-name>

cmake_minimum_required(VERSION 3.21)

# Project
project(CppStarter VERSION 0.1.0 LANGUAGES CXX)

# Options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing via CTest
include(CTest)

# Dependencies via vcpkg (manifest mode automatically picks this up)
# Example dependency: fmt
find_package(fmt CONFIG REQUIRED)

# Main executable
add_executable(cpp_starter src/main.cpp)

# Include directories
target_include_directories(cpp_starter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(cpp_starter PRIVATE fmt::fmt)

# Stricter warnings (GCC/Clang) and MSVC equivalents
if(MSVC)
  target_compile_options(cpp_starter PRIVATE /W4 /permissive-)
else()
  target_compile_options(cpp_starter PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Install rule
install(TARGETS cpp_starter RUNTIME DESTINATION bin)

# Tests
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

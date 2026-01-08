#include <iostream>
#include <fmt/core.h>

using namespace std;

int main() {
    fmt::print("Hello, cross-platform C++ (via CMake + vcpkg + Ninja)!\n");

    std::cout << "This is a simple C++ application using fmt library.\n";

    int x = 1;
    int y = 2;
    fmt::print("The sum of {} and {} is {}.\n", x, y, x + y);

    std::cin.get();

    return 0;
}

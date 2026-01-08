
# Tests setup
find_package(Catch2 CONFIG REQUIRED)

add_executable(unit_tests test_example.cpp)

target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain fmt::fmt)

# Enable CTest discovery for Catch2
include(Catch)
catch_discover_tests(unit_tests)

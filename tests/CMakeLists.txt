
# Tests setup
find_package(Catch2 CONFIG QUIET)

if(Catch2_FOUND)
  add_executable(unit_tests test_example.cpp)
  target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain fmt::fmt)
  
  # Add test without discovery to avoid DLL path issues during build
  add_test(NAME unit_tests COMMAND unit_tests)
endif()


#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("string size is computed", "[string]") {
    std::string s = "abc";
    REQUIRE(s.size() == 3);
}

#include <iostream>
#include <string>
#include "maylee/maylee/catch.hpp"
#include "maylee/utilities/variant.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variant_constructor", "[variant]") {
  SECTION("single") {
    variant<int> v;
    REQUIRE(v.get_which() == 0);
    REQUIRE(check_which<int>(v));
    get<int>(v);
  }
  SECTION("double") {
    variant<int, std::string> v("hello");
    REQUIRE(v.get_which() == 1);
    REQUIRE(check_which<std::string>(v));
  }
}

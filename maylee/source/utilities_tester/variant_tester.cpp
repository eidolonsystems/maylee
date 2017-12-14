#include <string>
#include "maylee/maylee/catch.hpp"
#include "maylee/utilities/variant.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_apply_unit_variant", "[variant]") {
  variant<int> v;
  REQUIRE(v.apply(
    [] (int value) {
      return 123;
    }) == 123);
  REQUIRE(v.apply(
    [] (auto value) {
      return 321;
    }) == 321);
}

TEST_CASE("test_apply_double_variant", "[variant]") {
  variant<int, string> v;
  REQUIRE(v.apply(
    [] (const string& value) {
      return 321;
    }));
}

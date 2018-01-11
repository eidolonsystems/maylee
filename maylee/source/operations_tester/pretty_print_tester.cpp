#include <sstream>
#include "maylee/maylee/catch.hpp"
#include "maylee/operations/pretty_print.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_pretty_print_let", "[pretty_print]") {
  SECTION("Int literal") {
    std::stringstream ss;
    auto l = std::make_unique<literal_expression>(
      literal("123", scalar_data_type::get_int()));
    pretty_print(*l, ss);
    REQUIRE(ss.str() == "123");
  }
  SECTION("Bool literal") {
    std::stringstream ss;
    auto l = std::make_unique<literal_expression>(
      literal("true", bool_data_type::get_instance()));
    pretty_print(*l, ss);
    REQUIRE(ss.str() == "true");
  }
  SECTION("String literal") {
    std::stringstream ss;
    auto l = std::make_unique<literal_expression>(
      literal("hello", string_lit_data_type::get_instance()));
    pretty_print(*l, ss);
    REQUIRE(ss.str() == "\"hello\"");
  }
}

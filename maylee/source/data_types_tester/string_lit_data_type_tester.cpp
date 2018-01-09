#include "maylee/data_types/string_lit_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_string_lit_name", "[string_lit_data_type]") {
  REQUIRE(string_lit_data_type().get_name() == "StringLit");
}

TEST_CASE("test_string_lit_equality", "[string_lit_data_type]") {
  REQUIRE(string_lit_data_type() == string_lit_data_type());
  REQUIRE(*string_lit_data_type::get_instance() ==
    *string_lit_data_type::get_instance());
  REQUIRE(*string_lit_data_type::get_instance() !=
    *char_data_type::get_instance());
}

#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_char_name", "[char_data_type]") {
  REQUIRE(char_data_type().get_name() == "Char");
}

TEST_CASE("test_char_equality", "[char_data_type]") {
  REQUIRE(char_data_type() == char_data_type());
  REQUIRE(*char_data_type::get_instance() == *char_data_type::get_instance());
  REQUIRE(*char_data_type::get_instance() != *bool_data_type::get_instance());
}

#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_bool_name", "[bool_data_type]") {
  REQUIRE(bool_data_type().get_name() == "Bool");
}

TEST_CASE("test_bool_equality", "[bool_data_type]") {
  REQUIRE(bool_data_type() == bool_data_type());
  REQUIRE(*bool_data_type::get_instance() == *bool_data_type::get_instance());
  REQUIRE(*bool_data_type::get_instance() != *char_data_type::get_instance());
}

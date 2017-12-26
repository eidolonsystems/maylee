#include "maylee/data_types/array_data_type.hpp"
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_array_name", "[array_data_type]") {
  array_data_type t1(bool_data_type::get_instance(), 10);
  REQUIRE(t1.get_name() == "[10]Bool");
}

TEST_CASE("test_array_equality", "[array_data_type]") {
  REQUIRE(array_data_type(bool_data_type::get_instance(), 10) ==
    array_data_type(bool_data_type::get_instance(), 10));
  REQUIRE(array_data_type(char_data_type::get_instance(), 10) !=
    array_data_type(bool_data_type::get_instance(), 10));
  REQUIRE(array_data_type(bool_data_type::get_instance(), 10) !=
    array_data_type(bool_data_type::get_instance(), 11));
  REQUIRE(array_data_type(bool_data_type::get_instance(), 10) !=
    *bool_data_type::get_instance());
}

#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/variable_array_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_bool_variable_array", "[variable_array_data_type]") {
  variable_array_data_type t1(std::make_shared<bool_data_type>());
  REQUIRE(t1.get_name() == "[]Bool");
}

TEST_CASE("test_variable_array_equality", "[variable_array_data_type]") {
  REQUIRE(variable_array_data_type(bool_data_type::get_instance()) ==
    variable_array_data_type(bool_data_type::get_instance()));
  REQUIRE(variable_array_data_type(char_data_type::get_instance()) !=
    variable_array_data_type(bool_data_type::get_instance()));
  REQUIRE(variable_array_data_type(bool_data_type::get_instance()) !=
    *bool_data_type::get_instance());
}

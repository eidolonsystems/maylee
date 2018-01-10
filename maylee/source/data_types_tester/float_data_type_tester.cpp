#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/float_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_float_name", "[float_data_type]") {
  REQUIRE(float_data_type::get_float()->get_name() == "Float");
  REQUIRE(float_data_type::get_double()->get_name() == "Double");
}

TEST_CASE("test_float_equality", "[float_data_type]") {
  REQUIRE(float_data_type(float_data_type::type::FLOAT) ==
    float_data_type(float_data_type::type::FLOAT));
  REQUIRE(float_data_type(float_data_type::type::DOUBLE) ==
    float_data_type(float_data_type::type::DOUBLE));
  REQUIRE(float_data_type(float_data_type::type::FLOAT) !=
    float_data_type(float_data_type::type::DOUBLE));
  REQUIRE(*float_data_type::get_float() != *char_data_type::get_instance());
}

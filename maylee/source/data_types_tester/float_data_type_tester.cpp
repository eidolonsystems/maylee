#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/float_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_float_name", "[float_data_type]") {
  REQUIRE(float_data_type::get_float32()->get_name() == "Float32");
  REQUIRE(float_data_type::get_float64()->get_name() == "Float64");
}

TEST_CASE("test_float_equality", "[float_data_type]") {
  REQUIRE(float_data_type(float_data_type::type::FLOAT32) ==
    float_data_type(float_data_type::type::FLOAT32));
  REQUIRE(float_data_type(float_data_type::type::FLOAT64) ==
    float_data_type(float_data_type::type::FLOAT64));
  REQUIRE(float_data_type(float_data_type::type::FLOAT32) !=
    float_data_type(float_data_type::type::FLOAT64));
  REQUIRE(*float_data_type::get_float32() != *char_data_type::get_instance());
}

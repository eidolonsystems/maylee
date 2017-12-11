#include "maylee/data_types/float_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_float_name", "[float_data_type]") {
  REQUIRE(float_data_type(float_data_type::type::FLOAT32).get_name() ==
    "Float32");
  REQUIRE(float_data_type(float_data_type::type::FLOAT64).get_name() ==
    "Float64");
}

TEST_CASE("test_float_size", "[float_data_type]") {
  REQUIRE(float_data_type(float_data_type::type::FLOAT32).get_size() == 4);
  REQUIRE(float_data_type(float_data_type::type::FLOAT64).get_size() == 8);
}

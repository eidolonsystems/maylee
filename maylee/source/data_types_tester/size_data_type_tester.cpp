#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/size_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_size_name", "[size_data_type]") {
  REQUIRE(size_data_type().get_name() == "Size");
}

TEST_CASE("test_size_equality", "[size_data_type]") {
  REQUIRE(size_data_type() == size_data_type());
  REQUIRE(*size_data_type::get_instance() == *size_data_type::get_instance());
  REQUIRE(*size_data_type::get_instance() != *char_data_type::get_instance());
}

#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_scalar_is_unsigned", "[scalar_data_type]") {
  REQUIRE(!scalar_data_type::get_int8()->is_unsigned());
  REQUIRE(!scalar_data_type::get_int16()->is_unsigned());
  REQUIRE(!scalar_data_type::get_int32()->is_unsigned());
  REQUIRE(!scalar_data_type::get_int64()->is_unsigned());
  REQUIRE(scalar_data_type::get_uint8()->is_unsigned());
  REQUIRE(scalar_data_type::get_uint16()->is_unsigned());
  REQUIRE(scalar_data_type::get_uint32()->is_unsigned());
  REQUIRE(scalar_data_type::get_uint64()->is_unsigned());
}

TEST_CASE("test_scalar_name", "[scalar_data_type]") {
  REQUIRE(scalar_data_type::get_int8()->get_name() == "Int8");
  REQUIRE(scalar_data_type::get_int16()->get_name() == "Int16");
  REQUIRE(scalar_data_type::get_int32()->get_name() == "Int32");
  REQUIRE(scalar_data_type::get_int64()->get_name() == "Int64");
  REQUIRE(scalar_data_type::get_uint8()->get_name() == "UInt8");
  REQUIRE(scalar_data_type::get_uint16()->get_name() == "UInt16");
  REQUIRE(scalar_data_type::get_uint32()->get_name() == "UInt32");
  REQUIRE(scalar_data_type::get_uint64()->get_name() == "UInt64");
}

TEST_CASE("test_scalar_equality", "[scalar_data_type]") {
  REQUIRE(scalar_data_type(scalar_data_type::type::INT32) ==
    scalar_data_type(scalar_data_type::type::INT32));
  REQUIRE(scalar_data_type(scalar_data_type::type::INT64) ==
    scalar_data_type(scalar_data_type::type::INT64));
  REQUIRE(scalar_data_type(scalar_data_type::type::INT32) !=
    scalar_data_type(scalar_data_type::type::UINT32));
  REQUIRE(scalar_data_type(scalar_data_type::type::INT32) !=
    scalar_data_type(scalar_data_type::type::INT64));
  REQUIRE(*scalar_data_type::get_int32() != *char_data_type::get_instance());
}

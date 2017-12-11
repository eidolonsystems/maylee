#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_is_unsigned", "[scalar_data_type]") {
  REQUIRE(!scalar_data_type(scalar_data_type::type::INT8).is_unsigned());
  REQUIRE(!scalar_data_type(scalar_data_type::type::INT16).is_unsigned());
  REQUIRE(!scalar_data_type(scalar_data_type::type::INT32).is_unsigned());
  REQUIRE(!scalar_data_type(scalar_data_type::type::INT64).is_unsigned());
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT8).is_unsigned());
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT16).is_unsigned());
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT32).is_unsigned());
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT64).is_unsigned());
}

TEST_CASE("test_name", "[scalar_data_type]") {
  REQUIRE(scalar_data_type(scalar_data_type::type::INT8).get_name() ==
    "Int8");
  REQUIRE(scalar_data_type(scalar_data_type::type::INT16).get_name() ==
    "Int16");
  REQUIRE(scalar_data_type(scalar_data_type::type::INT32).get_name() ==
    "Int32");
  REQUIRE(scalar_data_type(scalar_data_type::type::INT64).get_name() ==
    "Int64");
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT8).get_name() ==
    "UInt8");
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT16).get_name() ==
    "UInt16");
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT32).get_name() ==
    "UInt32");
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT64).get_name() ==
    "UInt64");
}

TEST_CASE("test_size", "[scalar_data_type]") {
  REQUIRE(scalar_data_type(scalar_data_type::type::INT8).get_size() == 1);
  REQUIRE(scalar_data_type(scalar_data_type::type::INT16).get_size() == 2);
  REQUIRE(scalar_data_type(scalar_data_type::type::INT32).get_size() == 4);
  REQUIRE(scalar_data_type(scalar_data_type::type::INT64).get_size() == 8);
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT8).get_size() == 1);
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT16).get_size() == 2);
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT32).get_size() == 4);
  REQUIRE(scalar_data_type(scalar_data_type::type::UINT64).get_size() == 8);
}

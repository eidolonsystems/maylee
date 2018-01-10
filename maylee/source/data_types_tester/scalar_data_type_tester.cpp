#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_scalar_is_unsigned", "[scalar_data_type]") {
  REQUIRE(!scalar_data_type::get_sbyte()->is_unsigned());
  REQUIRE(!scalar_data_type::get_short()->is_unsigned());
  REQUIRE(!scalar_data_type::get_int()->is_unsigned());
  REQUIRE(!scalar_data_type::get_long()->is_unsigned());
  REQUIRE(scalar_data_type::get_byte()->is_unsigned());
  REQUIRE(scalar_data_type::get_ushort()->is_unsigned());
  REQUIRE(scalar_data_type::get_uint()->is_unsigned());
  REQUIRE(scalar_data_type::get_ulong()->is_unsigned());
}

TEST_CASE("test_scalar_name", "[scalar_data_type]") {
  REQUIRE(scalar_data_type::get_sbyte()->get_name() == "SByte");
  REQUIRE(scalar_data_type::get_short()->get_name() == "Short");
  REQUIRE(scalar_data_type::get_int()->get_name() == "Int");
  REQUIRE(scalar_data_type::get_long()->get_name() == "Long");
  REQUIRE(scalar_data_type::get_byte()->get_name() == "Byte");
  REQUIRE(scalar_data_type::get_ushort()->get_name() == "UShort");
  REQUIRE(scalar_data_type::get_uint()->get_name() == "UInt");
  REQUIRE(scalar_data_type::get_ulong()->get_name() == "ULong");
}

TEST_CASE("test_scalar_equality", "[scalar_data_type]") {
  REQUIRE(scalar_data_type(scalar_data_type::type::INT) ==
    scalar_data_type(scalar_data_type::type::INT));
  REQUIRE(scalar_data_type(scalar_data_type::type::LONG) ==
    scalar_data_type(scalar_data_type::type::LONG));
  REQUIRE(scalar_data_type(scalar_data_type::type::INT) !=
    scalar_data_type(scalar_data_type::type::UINT));
  REQUIRE(scalar_data_type(scalar_data_type::type::INT) !=
    scalar_data_type(scalar_data_type::type::LONG));
  REQUIRE(*scalar_data_type::get_int() != *char_data_type::get_instance());
}

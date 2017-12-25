#include <sstream>
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/lexicon/literal.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

namespace {
  auto parse_literal(const char* source) {
    auto c = source;
    std::size_t s = std::strlen(c) + 1;
    return maylee::parse_literal(c, s);
  }
}

TEST_CASE("test_literal_stream", "[literal]") {
  literal l("5", scalar_data_type::get_int32());
  stringstream ss;
  ss << l;
  REQUIRE(ss.str() == "5");
}

TEST_CASE("test_literal_equality", "[literal]") {
  literal i1("5", scalar_data_type::get_int32());
  literal i2("5", scalar_data_type::get_int64());
  literal f1("3.14", float_data_type::get_float32());
  REQUIRE(i1 == i1);
  REQUIRE(i1 != i2);
  REQUIRE(i1 != f1);
}

TEST_CASE("test_parse_literal", "[literal]") {
  SECTION("Valid Literals") {
    REQUIRE(parse_literal("true") ==
      literal("true", bool_data_type::get_instance()));
    REQUIRE(parse_literal("false") ==
      literal("false", bool_data_type::get_instance()));
    REQUIRE(parse_literal("1") == literal("1", scalar_data_type::get_int32()));
    REQUIRE(parse_literal("1.1") ==
      literal("1.1", float_data_type::get_float64()));
  }
  SECTION("Literal Delimiters") {
    REQUIRE(parse_literal("trues") == nullopt);
    REQUIRE(parse_literal("true5") == nullopt);
    REQUIRE(parse_literal("true.") ==
      literal("true", bool_data_type::get_instance()));
    REQUIRE(parse_literal("true+") ==
      literal("true", bool_data_type::get_instance()));
    REQUIRE(parse_literal("5.5.") ==
      literal("5.5", float_data_type::get_float64()));
  }
  SECTION("Invalid Literals") {
    REQUIRE(parse_literal("abc") == nullopt);
  }
}

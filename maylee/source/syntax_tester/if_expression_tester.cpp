#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/if_expression.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_if_expression", "[if_expression]") {
  SECTION("Consequent and alternative have the same type.") {
    if_expression e(
      std::make_unique<literal_expression>(*parse_literal("true")),
      std::make_unique<literal_expression>(*parse_literal("123")),
      std::make_unique<literal_expression>(*parse_literal("321")));
    REQUIRE(*e.get_evaluation_type() == *scalar_data_type::get_int32());
  }
  SECTION("Consequent and alternative have different types.") {
    if_expression e(
      std::make_unique<literal_expression>(*parse_literal("true")),
      std::make_unique<literal_expression>(*parse_literal("123")),
      std::make_unique<literal_expression>(*parse_literal("false")));
    REQUIRE(*e.get_evaluation_type() ==
      *make_union_data_type({scalar_data_type::get_int32(),
      bool_data_type::get_instance()}));
  }
  SECTION("No alternative provided.") {
    if_expression e(
      std::make_unique<literal_expression>(*parse_literal("true")),
      std::make_unique<literal_expression>(*parse_literal("123")));
    REQUIRE(*e.get_evaluation_type() ==
      *make_union_data_type({scalar_data_type::get_int32(),
      tuple_data_type::get_void()}));
  }
}

#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/let_expression.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_let_expression", "[let_expression]") {
  let_expression e("x", scalar_data_type::get_int32(),
    std::make_unique<literal_expression>(*parse_literal("123")));
  REQUIRE(e.get_name() == "x");
  REQUIRE(*e.get_data_type() == *scalar_data_type::get_int32());
  REQUIRE(*e.get_evaluation_type() == *scalar_data_type::get_int32());
}

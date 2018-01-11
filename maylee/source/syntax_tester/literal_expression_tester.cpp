#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_literal_expression", "[literal_expression]") {
  literal_expression e(location::global(), *parse_literal("3.1415"));
  REQUIRE(e.get_literal().get_value() == "3.1415");
  REQUIRE(*e.get_literal().get_type() ==
    *float_data_type::get_instance(float_data_type::type::DOUBLE));
}

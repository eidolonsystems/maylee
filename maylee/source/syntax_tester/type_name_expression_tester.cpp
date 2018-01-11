#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/type_name_expression.hpp"

using namespace maylee;

TEST_CASE("test_type_name_expression", "[type_name_expression]") {
  type_name_expression e(location::global(), "String");
  REQUIRE(e.get_name() == "String");
}

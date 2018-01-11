#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variable_expression", "[variable_expression]") {
  variable_expression expression(location::global(), "abc");
  REQUIRE(expression.get_name() == "abc");
}

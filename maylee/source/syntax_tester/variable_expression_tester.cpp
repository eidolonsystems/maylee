#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variable_expression", "[variable_expression]") {
  auto v = std::make_shared<variable>("abc");
  variable_expression expression(v);
  REQUIRE(expression.get_variable() == v);
}

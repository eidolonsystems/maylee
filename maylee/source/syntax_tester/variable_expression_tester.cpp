#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variable_expression", "[variable_expression]") {
  auto v = std::make_shared<variable>("abc", bool_data_type::get_instance());
  variable_expression expression(v);
  REQUIRE(expression.get_variable() == v);
  REQUIRE(*expression.get_evaluation_type() == bool_data_type());
}

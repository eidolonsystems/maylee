#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/function_definition.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_function_definition", "[function_definition]") {
  auto f = std::make_shared<variable>("f");
  call_expression call(std::make_unique<variable_expression>(f), {});
  auto fexpr = dynamic_cast<const variable_expression*>(&call.get_callable());
  REQUIRE(fexpr != nullptr);
  REQUIRE(fexpr->get_variable() == f);
  REQUIRE(call.get_parameters().empty());
}

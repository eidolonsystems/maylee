#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/call_expression.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_call_expression", "[call_expression]") {
  call_expression call(location::global(),
    std::make_unique<variable_expression>(location::global(), "f"), {});
  auto fexpr = dynamic_cast<const variable_expression*>(&call.get_callable());
  REQUIRE(fexpr != nullptr);
  REQUIRE(fexpr->get_name() == "f");
  REQUIRE(call.get_parameters().empty());
}

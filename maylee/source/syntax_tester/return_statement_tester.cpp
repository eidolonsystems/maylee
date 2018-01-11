#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/return_statement.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_return_statement", "[return_statement]") {
  SECTION("Test returning an Int value.") {
    return_statement e(location::global(),
      std::make_unique<literal_expression>(location::global(),
      *parse_literal("123")));
  }
  SECTION("Test no return value.") {
    return_statement e(location::global());
  }
}

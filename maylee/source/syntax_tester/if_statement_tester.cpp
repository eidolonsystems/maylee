#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/if_statement.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_if_statement", "[if_statement]") {
  SECTION("Test both a consequent and alternative.") {
    if_statement e(
      std::make_unique<literal_expression>(*parse_literal("true")),
      std::make_unique<literal_expression>(*parse_literal("123")),
      std::make_unique<literal_expression>(*parse_literal("false")));
  }
  SECTION("No alternative provided.") {
    if_statement e(
      std::make_unique<literal_expression>(*parse_literal("true")),
      std::make_unique<literal_expression>(*parse_literal("123")));
  }
}

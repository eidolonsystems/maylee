#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/block_statement.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_block_statement", "[block_statement]") {
  block_statement b(std::make_unique<scope>(), {});
}

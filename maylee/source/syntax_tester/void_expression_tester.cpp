#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/void_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_void_expression", "[void_expression]") {
  void_expression e(location::global());
}

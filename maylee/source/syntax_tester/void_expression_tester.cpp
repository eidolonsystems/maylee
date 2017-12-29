#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/void_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_void_expression", "[void_expression]") {
  void_expression e;
  REQUIRE(*e.get_evaluation_type() == *tuple_data_type::get_void());
}

#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/assignment_statement.hpp"
#include "maylee/syntax/literal_expression.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_assignment_statement", "[assignment_statement]") {
  assignment_statement s(std::make_unique<variable_expression>("x"),
    std::make_unique<literal_expression>(
    literal("123", scalar_data_type::get_int())));
}

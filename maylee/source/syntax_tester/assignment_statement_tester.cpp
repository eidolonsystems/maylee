#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/assignment_statement.hpp"
#include "maylee/syntax/literal_expression.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_assignment_statement", "[assignment_statement]") {
  assignment_statement s(location::global(),
    std::make_unique<variable_expression>(location::global(), "x"),
    std::make_unique<literal_expression>(location::global(),
    literal("123", scalar_data_type::get_int())));
}

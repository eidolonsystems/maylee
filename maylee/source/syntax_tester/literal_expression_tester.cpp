#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/literal_expression.hpp"

using namespace maylee;
using namespace std;

namespace {
  auto parse_literal(const char* source) {
    auto c = source;
    std::size_t s = std::strlen(c) + 1;
    return maylee::parse_literal(c, s);
  }
}

TEST_CASE("test_literal_expression", "[literal_expression]") {
  literal_expression e(*parse_literal("3.1415"));
  REQUIRE(e.get_literal().get_value() == "3.1415");
  REQUIRE(*e.get_literal().get_type() ==
    *float_data_type::get_instance(float_data_type::type::FLOAT64));
  REQUIRE(*e.get_evaluation_type() == *e.get_literal().get_type());
}
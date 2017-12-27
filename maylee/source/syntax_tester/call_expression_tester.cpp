#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/function_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/call_expression.hpp"
#include "maylee/syntax/literal_expression.hpp"
#include "maylee/syntax/variable.hpp"
#include "maylee/syntax/variable_expression.hpp"

using namespace maylee;
using namespace std;

namespace {
  auto parse_literal(const char* source) {
    auto c = source;
    std::size_t s = std::strlen(c) + 1;
    return maylee::parse_literal(c, s);
  }
}

TEST_CASE("test_call_expression", "[call_expression]") {
  std::shared_ptr<variable> f = std::make_shared<variable>("f",
    std::make_shared<function_data_type>(
    std::vector<function_data_type::parameter>(),
    bool_data_type::get_instance()));
  call_expression call(std::make_unique<variable_expression>(f), {},
    bool_data_type::get_instance());
  auto fexpr = dynamic_cast<const variable_expression*>(&call.get_callable());
  REQUIRE(fexpr != nullptr);
  REQUIRE(fexpr->get_variable() == f);
  REQUIRE(call.get_parameters().empty());
  REQUIRE(*call.get_evaluation_type() == bool_data_type());
}

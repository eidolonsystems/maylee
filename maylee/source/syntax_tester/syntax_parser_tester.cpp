#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/lexicon/token_parser.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/syntax_parser.hpp"

using namespace maylee;
using namespace std;

namespace {
  template<std::size_t N>
  void feed(syntax_parser& p, const char (&s)[N]) {
    token_parser t;
    t.feed(s);
    t.feed("\0");
    while(auto token = t.parse_token()) {
      if(match(*token, terminal())) {
        p.feed(std::move(*token));
        break;
      }
      p.feed(std::move(*token));
    }
  }
}

TEST_CASE("test_parsing_terminal", "[syntax_parser]") {
  syntax_parser p;
  feed(p, "");
  auto expression = p.parse_node();
  REQUIRE(dynamic_cast<terminal_node*>(expression.get()) != nullptr);
}

TEST_CASE("test_parsing_literal_expression", "[syntax_parser]") {
  syntax_parser p;
  feed(p, "123");
  auto expression = p.parse_node();
  auto literal = dynamic_cast<literal_expression*>(expression.get());
  REQUIRE(literal != nullptr);
  REQUIRE(literal->get_literal().get_value() == "123");
  REQUIRE(*literal->get_literal().get_type() == *scalar_data_type::get_int32());
  REQUIRE(*literal->get_evaluation_type() ==
    *literal->get_literal().get_type());
}

TEST_CASE("test_parsing_let_expression", "[syntax_parser]") {
  syntax_parser p;
  feed(p, "let x = 321");
  auto expression = p.parse_node();
  auto let = dynamic_cast<let_expression*>(expression.get());
  REQUIRE(let != nullptr);
  REQUIRE(let->get_name() == "x");
  REQUIRE(*let->get_data_type() == *scalar_data_type::get_int32());
  REQUIRE(*let->get_evaluation_type() == *let->get_data_type());
  auto initializer = dynamic_cast<const literal_expression*>(
    &let->get_initializer());
  REQUIRE(initializer->get_literal().get_value() == "321");
  REQUIRE(*initializer->get_literal().get_type() ==
    *scalar_data_type::get_int32());
  REQUIRE(*initializer->get_evaluation_type() ==
    *initializer->get_literal().get_type());
}

TEST_CASE("test_parsing_variable_expression", "[syntax_parser]") {
  syntax_parser p;
  feed(p, "let y = false\ny");
  auto let = p.parse_node();
  auto expression = p.parse_node();
  auto variable = dynamic_cast<variable_expression*>(expression.get());
  REQUIRE(variable != nullptr);
  REQUIRE(variable->get_variable()->get_name() == "y");
  REQUIRE(*variable->get_variable()->get_data_type() ==
    *bool_data_type::get_instance());
  REQUIRE(*variable->get_evaluation_type() ==
    *variable->get_variable()->get_data_type());
}

TEST_CASE("test_parsing_arithmetic_expression", "[syntax_parser]") {
  SECTION("Parse literal expression") {
    syntax_parser p;
    feed(p, "1 + 2 * 3");
    auto e = p.parse_node();
  }
  SECTION("Parse variable expression") {
    syntax_parser p;
    feed(p,
      "let x = 1\n"
      "let y = 2\n"
      "let z = 3\n"
      "x + y * z");
    auto let_x = p.parse_node();
    auto let_y = p.parse_node();
    auto let_z = p.parse_node();
    auto expression = p.parse_node();
  }
}

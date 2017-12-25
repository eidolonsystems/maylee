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
  REQUIRE(expression != nullptr);
}

TEST_CASE("test_parsing_let_expression", "[syntax_parser]") {
  syntax_parser p;
  feed(p, "let x = 123");
  auto expression = p.parse_node();
  REQUIRE(expression != nullptr);
}

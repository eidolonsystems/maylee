#include "maylee/lexicon/token_parser.hpp"
#include "maylee/data_types/tuple_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/syntax_parser.hpp"
#include "maylee/operations/type_checker.hpp"

using namespace maylee;
using namespace std;

namespace {
  template<std::size_t N>
  void incremental_feed(syntax_parser& p, const char (&s)[N]) {
    token_parser t;
    t.feed(s);
    while(auto token = t.parse_token()) {
      if(match(*token, terminal::type::end_of_file)) {
        p.feed(std::move(*token));
        break;
      }
      p.feed(std::move(*token));
    }
  }

  template<std::size_t N>
  void feed(syntax_parser& p, const char (&s)[N]) {
    char q[N + 1];
    std::copy(begin(s), end(s), begin(q));
    q[N] = '\0';
    incremental_feed(p, q);
  }
}

TEST_CASE("test_type_check_literals", "[type_checker]") {
  SECTION("Test bool.") {
    syntax_parser p;
    feed(p, "true");
    auto node = p.parse_node();
    type_checker checker;
    auto type = checker.get_data_type(*node);
    REQUIRE(*type == *bool_data_type::get_instance());
  }
  SECTION("Test Int.") {
    syntax_parser p;
    feed(p, "321");
    auto node = p.parse_node();
    type_checker checker;
    auto type = checker.get_data_type(*node);
    REQUIRE(*type == *scalar_data_type::get_int());
  }
}

TEST_CASE("test_type_check_arithmetic", "[type_checker]") {
  SECTION("Test addition.") {
    syntax_parser p;
    feed(p, "1 + 1");
    auto node = p.parse_node();
    type_checker checker;
    auto type = checker.get_data_type(*node);
    REQUIRE(*type == *scalar_data_type::get_int());
  }
}

#include "maylee/lexicon/token_parser.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_keyword_token_parser", "[token_parser]") {
  token_parser parser;
  parser.feed("return");
  {
    auto t = parser.parse_token();
    REQUIRE(!t.has_value());
  }
  parser.feed("\n");
  {
    auto t = parser.parse_token();
    REQUIRE(t.has_value());
  }
}

TEST_CASE("test_identifier_token_parser", "[token_parser]") {
  token_parser parser;
  parser.feed("abc ");
  {
    auto t = parser.parse_token();
    REQUIRE(t.has_value());
  }
}

TEST_CASE("test_spaces_token_parser", "[token_parser]") {
  token_parser parser;
  parser.feed("   \nreturn  \n  \r\n   return ");
  {
    auto t = parser.parse_token();
    REQUIRE(t.has_value());
    REQUIRE(match(*t, keyword(keyword::word::RETURN)));
    REQUIRE(t->get_line_number() == 1);
    REQUIRE(t->get_column_number() == 0);
  }
  {
    auto t = parser.parse_token();
    REQUIRE(t.has_value());
    REQUIRE(match(*t, terminal::type::new_line));
    REQUIRE(t->get_line_number() == 1);
    REQUIRE(t->get_column_number() == 8);
  }
  {
    auto t = parser.parse_token();
    REQUIRE(t.has_value());
    REQUIRE(match(*t, keyword(keyword::word::RETURN)));
    REQUIRE(t->get_line_number() == 3);
    REQUIRE(t->get_column_number() == 3);
  }
}

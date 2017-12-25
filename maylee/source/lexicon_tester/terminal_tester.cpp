#include <sstream>
#include "maylee/lexicon/terminal.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

namespace {
  template<std::size_t N>
  auto parse_terminal(const char (&source)[N]) {
    auto c = source;
    std::size_t s = N;
    return maylee::parse_terminal(c, s);
  }
}

TEST_CASE("test_terminal_stream", "[terminal]") {
  terminal t;
  stringstream ss;
  ss << t;
  REQUIRE(ss.str().empty());
}

TEST_CASE("test_terminal_equality", "[terminal]") {
  terminal t1;
  terminal t2;
  REQUIRE(t1 == t2);
  REQUIRE(!(t1 != t2));
}

TEST_CASE("test_parse_terminal", "[terminal]") {
  SECTION("Valid Terminal") {
    REQUIRE(parse_terminal("\0") == terminal());
  }
  SECTION("Delimiters") {
    REQUIRE(parse_terminal("\09") == terminal());
    REQUIRE(parse_terminal("\0+") == terminal());
    REQUIRE(parse_terminal("\0:") == terminal());
    REQUIRE(parse_terminal("\0,") == terminal());
    REQUIRE(parse_terminal("\0a") == terminal());
  }
  SECTION("Invalid Punctuation") {
    REQUIRE(parse_terminal("abc\0") == std::nullopt);
  }
}

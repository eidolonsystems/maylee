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
  SECTION("New line") {
    terminal t(terminal::type::new_line);
    stringstream ss;
    ss << t;
    REQUIRE(ss.str() == "\n");
  }
  SECTION("End of file") {
    terminal t(terminal::type::end_of_file);
    stringstream ss;
    ss << t;
    REQUIRE(ss.str().empty());
  }
}

TEST_CASE("test_terminal_equality", "[terminal]") {
  terminal t1(terminal::type::end_of_file);
  terminal t2(terminal::type::new_line);
  REQUIRE(t1 == t1);
  REQUIRE(t1 == terminal::type::end_of_file);
  REQUIRE(t1 != t2);
  REQUIRE(t2 == terminal::type::new_line);
}

TEST_CASE("test_parse_terminal", "[terminal]") {
  SECTION("Valid Terminal") {
    REQUIRE(parse_terminal("\0") == terminal::type::end_of_file);
    REQUIRE(parse_terminal("\n") == terminal::type::new_line);
  }
  SECTION("Delimiters") {
    REQUIRE(parse_terminal("\09") == terminal::type::end_of_file);
    REQUIRE(parse_terminal("\0+") == terminal::type::end_of_file);
    REQUIRE(parse_terminal("\0:") == terminal::type::end_of_file);
    REQUIRE(parse_terminal("\0,") == terminal::type::end_of_file);
    REQUIRE(parse_terminal("\0a") == terminal::type::end_of_file);
  }
  SECTION("Invalid Punctuation") {
    REQUIRE(parse_terminal("abc\0") == std::nullopt);
  }
}

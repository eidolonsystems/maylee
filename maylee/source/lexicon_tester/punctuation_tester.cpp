#include <sstream>
#include "maylee/lexicon/punctuation.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

namespace {
  auto parse_punctuation(const char* source) {
    auto c = source;
    std::size_t s = std::strlen(c) + 1;
    return maylee::parse_punctuation(c, s);
  }
}

TEST_CASE("test_punctuation_stream", "[punctuation]") {
  SECTION("Open bracket") {
    punctuation p(punctuation::mark::OPEN_BRACKET);
    stringstream ss;
    ss << p;
    REQUIRE(ss.str() == "(");
  }
  SECTION("Close bracket") {
    punctuation p(punctuation::mark::CLOSE_BRACKET);
    stringstream ss;
    ss << p;
    REQUIRE(ss.str() == ")");
  }
  SECTION("Colon") {
    punctuation p(punctuation::mark::COLON);
    stringstream ss;
    ss << p;
    REQUIRE(ss.str() == ":");
  }
  SECTION("Comma") {
    punctuation p(punctuation::mark::COMMA);
    stringstream ss;
    ss << p;
    REQUIRE(ss.str() == ",");
  }
  SECTION("Dot") {
    punctuation p(punctuation::mark::DOT);
    stringstream ss;
    ss << p;
    REQUIRE(ss.str() == ".");
  }
}

TEST_CASE("test_punctuation_equality", "[punctuation]") {
  punctuation p1(punctuation::mark::COLON);
  punctuation p2(punctuation::mark::OPEN_BRACKET);
  REQUIRE(p1 == p1);
  REQUIRE(p1 != p2);
  REQUIRE(p1 == punctuation::mark::COLON);
  REQUIRE(p2 != punctuation::mark::COLON);
}

TEST_CASE("test_parse_punctuation", "[punctuation]") {
  SECTION("Valid Punctuation") {
    REQUIRE(parse_punctuation("(") == punctuation::mark::OPEN_BRACKET);
    REQUIRE(parse_punctuation(")") == punctuation::mark::CLOSE_BRACKET);
    REQUIRE(parse_punctuation(":") == punctuation::mark::COLON);
    REQUIRE(parse_punctuation(",") == punctuation::mark::COMMA);
    REQUIRE(parse_punctuation(".") == punctuation::mark::DOT);
  }
  SECTION("Delimiters") {
    REQUIRE(parse_punctuation(":5") == punctuation::mark::COLON);
    REQUIRE(parse_punctuation(":+") == punctuation::mark::COLON);
    REQUIRE(parse_punctuation("::") == punctuation::mark::COLON);
    REQUIRE(parse_punctuation(":,") == punctuation::mark::COLON);
    REQUIRE(parse_punctuation(":a") == punctuation::mark::COLON);
  }
  SECTION("Invalid Punctuation") {
    REQUIRE(parse_punctuation("abc") == std::nullopt);
  }
}

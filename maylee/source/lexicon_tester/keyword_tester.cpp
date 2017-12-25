#include <sstream>
#include "maylee/lexicon/keyword.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

namespace {
  auto parse_keyword(const char* source) {
    auto c = source;
    std::size_t s = std::strlen(c) + 1;
    return maylee::parse_keyword(c, s);
  }
}

TEST_CASE("test_keyword_stream", "[keyword]") {
  SECTION("define") {
    keyword k(keyword::word::DEFINE);
    stringstream ss;
    ss << k;
    REQUIRE(ss.str() == "def");
  }
  SECTION("end") {
    keyword k(keyword::word::END);
    stringstream ss;
    ss << k;
    REQUIRE(ss.str() == "end");
  }
  SECTION("let") {
    keyword k(keyword::word::LET);
    stringstream ss;
    ss << k;
    REQUIRE(ss.str() == "let");
  }
  SECTION("return") {
    keyword k(keyword::word::RETURN);
    stringstream ss;
    ss << k;
    REQUIRE(ss.str() == "return");
  }
}

TEST_CASE("test_keyword_equality", "[keyword]") {
  keyword k1(keyword::word::DEFINE);
  keyword k2(keyword::word::LET);
  REQUIRE(k1 == k1);
  REQUIRE(k1 != k2);
  REQUIRE(k1 == keyword::word::DEFINE);
  REQUIRE(k2 != keyword::word::DEFINE);
}

TEST_CASE("test_parse_keyword", "[keyword]") {
  SECTION("Valid Keywords") {
    REQUIRE(parse_keyword("def") == keyword::word::DEFINE);
    REQUIRE(parse_keyword("end") == keyword::word::END);
    REQUIRE(parse_keyword("let") == keyword::word::LET);
    REQUIRE(parse_keyword("return") == keyword::word::RETURN);
  }
  SECTION("Delimiters") {
    REQUIRE(parse_keyword("def+") == keyword::word::DEFINE);
    REQUIRE(parse_keyword("def.") == keyword::word::DEFINE);
    REQUIRE(parse_keyword("def5") == nullopt);
    REQUIRE(parse_keyword("defs") == std::nullopt);
  }
  SECTION("Invalid Keywords") {
    REQUIRE(parse_keyword("abc") == std::nullopt);
    REQUIRE(parse_keyword("123") == std::nullopt);
  }
}

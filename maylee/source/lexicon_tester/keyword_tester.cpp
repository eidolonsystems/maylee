#include "maylee/lexicon/keyword.hpp"
#include <sstream>
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

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

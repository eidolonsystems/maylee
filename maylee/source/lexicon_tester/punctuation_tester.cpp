#include "maylee/lexicon/punctuation.hpp"
#include <sstream>
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

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

#include "maylee/lexicon/token.hpp"
#include <sstream>
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_token_stream", "[token]") {
  SECTION("Keyword") {
    token t(keyword(keyword::word::DEFINE), 0, 0);
    stringstream ss;
    ss << t;
    REQUIRE(ss.str() == "def");
  }
  SECTION("Punctuation") {
    token t(punctuation(punctuation::mark::DOT), 0, 0);
    stringstream ss;
    ss << t;
    REQUIRE(ss.str() == ".");
  }
}

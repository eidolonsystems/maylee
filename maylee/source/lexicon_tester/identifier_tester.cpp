#include "maylee/lexicon/identifier.hpp"
#include <sstream>
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_identifier_stream", "[identifier]") {
  identifier id("hello");
  stringstream ss;
  ss << id;
  REQUIRE(ss.str() == "hello");
}

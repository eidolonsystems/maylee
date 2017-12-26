#include <sstream>
#include "maylee/lexicon/location.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_location_stream", "[location]") {
  location l("/home/maylee/main.may", 5, 12);
  stringstream ss;
  ss << l;
  REQUIRE(ss.str() == "/home/maylee/main.may:5:12");
}

#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/variable.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variable", "[variable]") {
  variable v("abc");
  REQUIRE(v.get_name() == "abc");
}

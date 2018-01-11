#include "maylee/maylee/catch.hpp"
#include "maylee/semantics/function.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_function", "[function]") {
  function f(location::global(), "f");
  REQUIRE(f.get_name() == "f");
}

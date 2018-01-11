#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/semantics/variable.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variable", "[variable]") {
  variable v(location::global(), "abc", scalar_data_type::get_int());
  REQUIRE(v.get_name() == "abc");
}

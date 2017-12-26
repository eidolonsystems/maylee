#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/variable.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_variable", "[variable]") {
  variable v("abc", bool_data_type::get_instance());
  REQUIRE(v.get_name() == "abc");
  REQUIRE(*v.get_data_type() == bool_data_type());
}

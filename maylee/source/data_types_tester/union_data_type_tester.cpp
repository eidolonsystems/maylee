#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/union_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_bottom_union", "[union_data_type]") {
  auto b = union_data_type::get_bottom();
  REQUIRE(b->get_name() == "(|)");
  REQUIRE(*b == union_data_type({}));
}

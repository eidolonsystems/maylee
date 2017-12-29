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

TEST_CASE("test_double_union", "[union_data_type]") {
  union_data_type b(std::vector<std::shared_ptr<data_type>>({
    bool_data_type::get_instance(), char_data_type::get_instance()}));
  REQUIRE(b.get_name() == "(Bool | Char)");
  REQUIRE(b == b);
}

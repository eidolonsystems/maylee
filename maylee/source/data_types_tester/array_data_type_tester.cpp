#include "maylee/data_types/array_data_type.hpp"
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_bool_array", "[array_data_type]") {
  array_data_type t1(std::make_shared<bool_data_type>(), 10);
  REQUIRE(t1.get_name() == "[10]Bool");
  REQUIRE(t1.get_size() == 10 + size_data_type::SIZE);
}

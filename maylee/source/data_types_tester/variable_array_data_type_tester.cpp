#include "maylee/data_types/variable_array_data_type.hpp"
#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_bool_variable_array", "[variable_array_data_type]") {
  variable_array_data_type t1(std::make_shared<bool_data_type>());
  REQUIRE(t1.get_name() == "[]Bool");
  REQUIRE(t1.get_size() == size_data_type::SIZE());
}

#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_bool_name", "[bool_data_type]") {
  REQUIRE(bool_data_type().get_name() == "Bool");
}

TEST_CASE("test_bool_size", "[bool_data_type]") {
  REQUIRE(bool_data_type().get_size() == 1);
}

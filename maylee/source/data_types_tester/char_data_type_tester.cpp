#include "maylee/data_types/char_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_char_name", "[char_data_type]") {
  REQUIRE(char_data_type().get_name() == "Char");
}

TEST_CASE("test_char_size", "[char_data_type]") {
  REQUIRE(char_data_type().get_size() == 1);
}

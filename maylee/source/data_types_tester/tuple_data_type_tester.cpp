#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/data_types/char_data_type.hpp"
#include "maylee/data_types/tuple_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_void_tuple", "[tuple_data_type]") {
  auto v = tuple_data_type::get_void();
  REQUIRE(v->get_name() == "()");
  REQUIRE(*v == tuple_data_type({}));
}

TEST_CASE("test_pair", "[tuple_data_type]") {
  tuple_data_type t(std::vector<tuple_data_type::member>(
    {{"x", bool_data_type::get_instance()},
    {"y", char_data_type::get_instance()}}));
  REQUIRE(t.get_name() == "(Bool x, Char y)");
  REQUIRE(t == t);
}

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

TEST_CASE("test_make_union", "[union_data_type]") {
  SECTION("Make a bottom type.") {
    auto b = make_union_data_type({});
    REQUIRE(*b == *union_data_type::get_bottom());
  }
  SECTION("Make a union with one element.") {
    auto b = make_union_data_type({bool_data_type::get_instance()});
    REQUIRE(*b == *bool_data_type::get_instance());
  }
  SECTION("Make a union with two redundant elements.") {
    auto b = make_union_data_type({bool_data_type::get_instance(),
      bool_data_type::get_instance()});
    REQUIRE(*b == *bool_data_type::get_instance());
  }
  SECTION("Make a union with two unique elements.") {
    auto b = make_union_data_type({bool_data_type::get_instance(),
      char_data_type::get_instance()});
    auto u = std::dynamic_pointer_cast<union_data_type>(b);
    REQUIRE(u != nullptr);
    REQUIRE(u->get_variants().size() == 2);
    REQUIRE(*u->get_variants()[0] == bool_data_type());
    REQUIRE(*u->get_variants()[1] == char_data_type());
  }
  SECTION("Make a union with unique and redundant elements.") {
    auto b = make_union_data_type({char_data_type::get_instance(),
      char_data_type::get_instance(), bool_data_type::get_instance(),
      char_data_type::get_instance(), bool_data_type::get_instance()});
    auto u = std::dynamic_pointer_cast<union_data_type>(b);
    REQUIRE(u != nullptr);
    REQUIRE(u->get_variants().size() == 2);
    REQUIRE(*u->get_variants()[0] == char_data_type());
    REQUIRE(*u->get_variants()[1] == bool_data_type());
  }
}

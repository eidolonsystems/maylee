#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/scope.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_scope_lookup", "[scope]") {
  scope s1;
  {
    REQUIRE(s1.add(element(std::make_shared<variable>(
      "abc", bool_data_type::get_instance()), location::global())));
    REQUIRE(!s1.add(element(std::make_shared<variable>(
      "abc", bool_data_type::get_instance()), location::global())));
    REQUIRE(s1.contains("abc"));
    auto abc_index = s1.find("abc");
    REQUIRE(abc_index.has_value());
    auto abc = std::get_if<std::shared_ptr<variable>>(
      &abc_index->get_instance());
    REQUIRE(abc != nullptr);
    REQUIRE((*abc)->get_name() == "abc");
    REQUIRE(*(*abc)->get_data_type() == *bool_data_type::get_instance());
    REQUIRE(s1.find_within("abc") == *abc_index);
  }
  {
    scope s2(&s1);
    REQUIRE(!s2.contains("abc"));
    REQUIRE(!s2.find_within("abc").has_value());
    auto abc_index = s2.find("abc");
    REQUIRE(abc_index.has_value());
    auto abc = std::get_if<std::shared_ptr<variable>>(
      &abc_index->get_instance());
    REQUIRE(abc != nullptr);
    REQUIRE((*abc)->get_name() == "abc");
    REQUIRE(*(*abc)->get_data_type() == *bool_data_type::get_instance());
  }
}

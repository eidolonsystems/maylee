#include "maylee/maylee/catch.hpp"
#include "maylee/semantics/scope.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_scope_lookup", "[scope]") {
  scope s1;
  {
    REQUIRE(s1.add(std::make_shared<variable>(location::global(), "abc",
      scalar_data_type::get_int())));
    REQUIRE(!s1.add(std::make_shared<variable>(location::global(), "abc",
      scalar_data_type::get_int())));
    REQUIRE(s1.contains("abc"));
    auto abc_index = s1.find("abc");
    REQUIRE(abc_index != nullptr);
    auto abc = std::dynamic_pointer_cast<variable>(abc_index);
    REQUIRE(abc != nullptr);
    REQUIRE(abc->get_name() == "abc");
    REQUIRE(s1.find_within("abc") == abc_index);
  }
  {
    scope s2(&s1);
    REQUIRE(!s2.contains("abc"));
    REQUIRE(s2.find_within("abc") == nullptr);
    auto abc_index = s2.find("abc");
    REQUIRE(abc_index != nullptr);
    auto abc = std::dynamic_pointer_cast<variable>(abc_index);
    REQUIRE(abc != nullptr);
    REQUIRE(abc->get_name() == "abc");
  }
}

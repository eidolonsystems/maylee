#include "maylee/data_types/tuple_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/semantics/function.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_function", "[function]") {
  function f(location::global(), "f", std::make_shared<function_data_type>(
    std::vector<function_data_type::parameter>(), tuple_data_type::get_void()));
  REQUIRE(f.get_name() == "f");
}

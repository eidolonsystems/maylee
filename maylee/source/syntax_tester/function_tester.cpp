#include "maylee/data_types/bool_data_type.hpp"
#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/function.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_function", "[function]") {
  auto signature = std::make_shared<function_data_type>(
    std::vector<function_data_type::parameter>(),
    bool_data_type::get_instance());
  function f("f", signature);
  REQUIRE(f.get_name() == "f");
  REQUIRE(*f.get_signature() == *signature);
}

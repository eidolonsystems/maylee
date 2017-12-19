#include <iostream>
#include <string>
#include "maylee/maylee/catch.hpp"
#include "maylee/utilities/variant.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_apply_two_variant", "[variant]") {
  variant<double, std::string> v("hello");
  std::string r = "goodbye";
  auto s = v.apply(
    [&] (auto& value) {
      return r;
    });
  std::cout << s << std::endl;
}

#include <iostream>
#include <string>
#include "maylee/maylee/catch.hpp"
#include "maylee/utilities/fixed_variant.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_apply_two_fixed_variant", "[fixed_variant]") {
  fixed_variant<double, std::string> v(5);
  std::cout << (int)(v.get_which()) << std::endl;
}

#include <iostream>
#include <string>
#include "maylee/maylee/catch.hpp"
#include "maylee/utilities/variant.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_apply_unit_variant", "[variant]") {
}

TEST_CASE("test_apply_double_variant", "[variant]") {
  variant<int, double> v = 5.0;
  v.apply(
    [] (int x) {
      std::cout << "int" << std::endl;
    });
}

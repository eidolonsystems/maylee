#include "maylee/lexicon/literal.hpp"
#include <sstream>
#include "maylee/data_types/scalar_data_type.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_literal_stream", "[literal]") {
  literal l("5", scalar_data_type::get_instance(scalar_data_type::type::INT32));
  stringstream ss;
  ss << l;
  REQUIRE(ss.str() == "5");
}

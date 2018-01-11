#include "maylee/maylee/catch.hpp"
#include "maylee/semantics/element.hpp"
#include "maylee/semantics/variable.hpp"

using namespace maylee;
using namespace std;

TEST_CASE("test_element", "[element]") {
  auto e = std::make_shared<element>(std::make_shared<variable>("x"),
    location::global());
  REQUIRE(e->get_name() == "x");
  REQUIRE(std::get_if<std::shared_ptr<variable>>(
    &e->get_instance()) != nullptr);
}

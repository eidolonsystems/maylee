#include "maylee/maylee/catch.hpp"
#include "maylee/syntax/terminal_node.hpp"

using namespace maylee;

TEST_CASE("test_terminal_node", "[test_terminal_node]") {
  terminal_node n(location::global());
}

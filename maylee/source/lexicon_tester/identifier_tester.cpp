#include <sstream>
#include "maylee/lexicon/identifier.hpp"
#include "maylee/maylee/catch.hpp"

using namespace maylee;
using namespace std;

namespace {
  auto parse_identifier(const char* source) {
    auto c = source;
    std::size_t s = std::strlen(c) + 1;
    return maylee::parse_identifier(c, s);
  }
}

TEST_CASE("test_identifier_stream", "[identifier]") {
  identifier id("hello");
  stringstream ss;
  ss << id;
  REQUIRE(ss.str() == "hello");
}

TEST_CASE("test_identifier_equality", "[identifier]") {
  identifier id1("hello");
  identifier id2("goodbye");
  REQUIRE(id1 == id1);
  REQUIRE(id1 != id2);
}

TEST_CASE("test_parse_identifier", "[identifier]") {
  REQUIRE(parse_identifier("abc") == std::string("abc"));
  REQUIRE(parse_identifier("_abc") == std::string("_abc"));
  REQUIRE(parse_identifier("abc_") == std::string("abc_"));
  REQUIRE(parse_identifier("a_bc") == std::string("a_bc"));
  REQUIRE(parse_identifier("5abc") == std::nullopt);
  REQUIRE(parse_identifier(".abc") == std::nullopt);
  REQUIRE(parse_identifier("+abc") == std::nullopt);
  REQUIRE(parse_identifier("abc5") == std::string("abc5"));
  REQUIRE(parse_identifier("ab5c") == std::string("ab5c"));
  REQUIRE(parse_identifier("abc+") == std::string("abc"));
  REQUIRE(parse_identifier("abc.") == std::string("abc"));
}

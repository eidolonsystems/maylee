#ifndef MAYLEE_TOKEN_PARSER_HPP
#define MAYLEE_TOKEN_PARSER_HPP
#include <memory>
#include "maylee/lexicon/lexicon.hpp"
#include "maylee/lexicon/token.hpp"

namespace maylee {
  class token_parser {
    public:
      token_parser() = default;

      void feed(const char* data, int size);

      std::unique_ptr<token> parse_token();

    private:
  };

  inline void token_parser::feed(const char* data, int size) {
  }

  inline std::unique_ptr<token> token_parser::parse_token() {
    return nullptr;
  }
}

#endif

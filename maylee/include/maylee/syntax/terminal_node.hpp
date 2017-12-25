#ifndef MAYLEE_TERMINAL_NODE_HPP
#define MAYLEE_TERMINAL_NODE_HPP
#include "maylee/lexicon/terminal.hpp"
#include "maylee/syntax/syntax.hpp"
#include "maylee/syntax/syntax_node.hpp"

namespace maylee {

  //! Represents a terminal token.
  class terminal_node : public syntax_node {
    public:

      //! Constructs a terminal node.
      terminal_node() = default;
  };
}

#endif

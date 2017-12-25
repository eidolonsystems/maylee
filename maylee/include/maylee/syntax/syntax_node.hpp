#ifndef MAYLEE_SYNTAX_NODE_HPP
#define MAYLEE_SYNTAX_NODE_HPP
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! The base class for a syntax node.
  class syntax_node {
    public:
      virtual ~syntax_node() = default;

    protected:

      //! Constructs a syntax_node.
      syntax_node() = default;

    private:
      syntax_node(const syntax_node&) = delete;
      syntax_node& operator =(const syntax_node&) = delete;
  };
}

#endif

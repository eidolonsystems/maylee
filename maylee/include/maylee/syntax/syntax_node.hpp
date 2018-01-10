#ifndef MAYLEE_SYNTAX_NODE_HPP
#define MAYLEE_SYNTAX_NODE_HPP
#include "maylee/syntax/syntax.hpp"

namespace maylee {

  //! The base class for a syntax node.
  class syntax_node {
    public:
      virtual ~syntax_node() = default;

      //! Applies a syntax_node_visitor to this instance.
      /*!
        \param visitor The visitor to apply.
      */
      virtual void apply(syntax_node_visitor& visitor) const = 0;

    protected:

      //! Constructs a syntax_node.
      syntax_node() = default;

    private:
      syntax_node(const syntax_node&) = delete;
      syntax_node& operator =(const syntax_node&) = delete;
  };
}

#endif

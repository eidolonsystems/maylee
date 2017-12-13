#ifndef MAYLEE_PUNCTUATION_HPP
#define MAYLEE_PUNCTUATION_HPP
#include <ostream>
#include <stdexcept>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores a punctuation mark.
  class punctuation {
    public:

      //! The list of punctuation marks.
      enum class mark {

        //! '('
        OPEN_BRACKET,

        //! ')'
        CLOSE_BRACKET,

        //! ':'
        COLON,

        //! ','
        COMMA,

        //! '.'
        DOT
      };

      //! Constructs a punctuation.
      /*!
        \param mark The mark to represent.
      */
      punctuation(mark mark);

      //! Returns the punctuation mark represented.
      mark get_mark() const;

    private:
      mark m_mark;
  };

  inline std::ostream& operator <<(std::ostream& out,
      const punctuation& value) {
    switch(value.get_mark()) {
      case punctuation::mark::OPEN_BRACKET:
        return out << '(';
      case punctuation::mark::CLOSE_BRACKET:
        return out << ')';
      case punctuation::mark::COLON:
        return out << ':';
      case punctuation::mark::COMMA:
        return out << ',';
      case punctuation::mark::DOT:
        return out << '.';
      default:
        throw std::runtime_error("Invalid punctuation mark.");
    }
  }

  inline punctuation::punctuation(mark mark)
      : m_mark(mark) {}

  inline punctuation::mark punctuation::get_mark() const {
    return m_mark;
  }
}

#endif

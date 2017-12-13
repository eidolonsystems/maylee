#ifndef MAYLEE_KEYWORD_HPP
#define MAYLEE_KEYWORD_HPP
#include <ostream>
#include <stdexcept>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores a keyword token.
  class keyword {
    public:

      //! The list of keywords.
      enum class word {

        //! def
        DEFINE,

        //! end
        END,

        //! let
        LET,

        //! return
        RETURN
      };

      //! Constructs a keyword.
      /*!
        \param word The word to represent.
      */
      keyword(word word);

      //! Returns the word represented.
      word get_word() const;

    private:
      word m_word;
  };

  inline std::ostream& operator <<(std::ostream& out, const keyword& value) {
    switch(value.get_word()) {
      case keyword::word::DEFINE:
        return out << "def";
      case keyword::word::END:
        return out << "end";
      case keyword::word::LET:
        return out << "let";
      case keyword::word::RETURN:
        return out << "return";
      default:
        throw std::runtime_error("Invalid keyword.");
    }
  }

  inline keyword::keyword(word word)
      : m_word(word) {}

  inline keyword::word keyword::get_word() const {
    return m_word;
  }
}

#endif

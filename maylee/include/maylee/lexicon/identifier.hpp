#ifndef MAYLEE_IDENTIFIER_HPP
#define MAYLEE_IDENTIFIER_HPP
#include <memory>
#include <ostream>
#include <string>
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores an identifier.
  class identifier {
    public:

      //! Constructs an identifier.
      /*!
        \param symbol The identifier's symbol.
      */
      identifier(std::string symbol);

      //! Returns the symbol.
      const std::string& get_symbol() const;

    private:
      std::shared_ptr<std::string> m_symbol;
  };

  inline std::ostream& operator <<(std::ostream& out, const identifier& value) {
    return out << value.get_symbol();
  }

  inline identifier::identifier(std::string symbol)
      : m_symbol(std::make_shared<std::string>(std::move(symbol))) {}

  inline const std::string& identifier::get_symbol() const {
    return *m_symbol;
  }
}

#endif

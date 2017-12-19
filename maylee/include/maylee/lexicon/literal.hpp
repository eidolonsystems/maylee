#ifndef MAYLEE_LITERAL_HPP
#define MAYLEE_LITERAL_HPP
#include <memory>
#include <ostream>
#include <string>
#include "maylee/data_types/data_type.hpp"
#include "maylee/lexicon/lexicon.hpp"

namespace maylee {

  //! Stores a literal token.
  class literal {
    public:

      //! Constructs a literal.
      /*!
        \param value The string representation of the value.
        \param type The literal value's data type.
      */
      literal(std::string value, std::shared_ptr<data_type> type);

      //! Returns the string representation of the value.
      const std::string& get_value() const;

      //! Returns the literal value's data type.
      const std::shared_ptr<data_type>& get_type() const;

    private:
      std::string m_value;
      std::shared_ptr<data_type> m_type;
  };

  inline std::ostream& operator <<(std::ostream& out, const literal& value) {
    return out << value.get_value();
  }

  inline literal::literal(std::string value, std::shared_ptr<data_type> type)
      : m_value(std::move(value)),
        m_type(std::move(type)) {}

  inline const std::string& literal::get_value() const {
    return m_value;
  }

  inline const std::shared_ptr<data_type>& literal::get_type() const {
    return m_type;
  }
}

#endif

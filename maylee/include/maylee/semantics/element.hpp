#ifndef MAYLEE_ELEMENT_HPP
#define MAYLEE_ELEMENT_HPP
#include <memory>
#include <string>
#include <type_traits>
#include <variant>
#include "maylee/data_types/data_type.hpp"
#include "maylee/lexicon/location.hpp"
#include "maylee/semantics/function.hpp"
#include "maylee/semantics/semantics.hpp"
#include "maylee/semantics/variable.hpp"

namespace maylee {

  //! Abstracts over any named element of the language that can be placed in a
  //! scope.
  class element {
    public:

      //! Specifies the types of named elements.
      using instance = std::variant<std::shared_ptr<variable>,
        std::shared_ptr<data_type>>;

      //! Constructs an element.
      /*!
        \param instance The instance to represent.
        \param location The location where the element was defined.
      */
      element(instance instance, location location);

      //! Returns the instance.
      const instance& get_instance() const;

      //! Returns the name of the element.
      const std::string& get_name() const;

      //! Returns the location where the element was defined.
      const location& get_location() const;

    private:
      instance m_instance;
      location m_location;
  };

  //! Tests if two elements refer to the same instance.
  /*!
    \param lhs The left hand side of the comparison.
    \param rhs The right hand side of the comparison.
    \return <code>true</code> iff the two elements are identical.
  */
  inline bool operator ==(const element& lhs, const element& rhs) {
    return lhs.get_instance() == rhs.get_instance();
  }

  //! Tests if two elements refer to different instances.
  /*!
    \param lhs The left hand side of the comparison.
    \param rhs The right hand side of the comparison.
    \return <code>true</code> iff the two elements are distinct.
  */
  inline bool operator !=(const element& lhs, const element& rhs) {
    return !(lhs == rhs);
  }

  inline element::element(instance instance, location location)
      : m_instance(std::move(instance)),
        m_location(std::move(location)) {}

  inline const element::instance& element::get_instance() const {
    return m_instance;
  }

  inline const std::string& element::get_name() const {
    return std::visit(
      [] (auto&& instance) -> decltype(auto) {
        return instance->get_name();
      }, m_instance);
  }

  inline const location& element::get_location() const {
    return m_location;
  }
}

#endif

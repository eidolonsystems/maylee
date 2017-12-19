#ifndef MAYLEE_VARIANT_HPP
#define MAYLEE_VARIANT_HPP
#include <ostream>
#include "maylee/utilities/variant_details.hpp"
#include "maylee/utilities/utilities.hpp"

namespace maylee {

  /*! \brief A class that stores a single value among a list of data types.
             Unlike a traditional union or variant, the value must be
             initialized on construction and the type can not change.
      \tparam T... The list of data types that can be stored.
   */
  template<typename... T>
  class variant {
    public:

      //! Constructs a variant representing a value of the first type in the
      //! template parameter pack T.
      variant();

      //! Constructs a variant representing a value constructible from a value
      //! of type <i>U</i>.
      template<typename U, typename = std::enable_if_t<
        !std::is_same<std::decay_t<U>, variant>::value>>
      variant(U&& value);

      //! Copies a variant.
      /*!
        \param v The value to copy.
      */
      variant(const variant& v);

      ~variant();

      //! Returns the index of the type stored.
      std::uint8_t get_which() const;

      //! Applies a function to the value stored by this variant.
      /*!
        \param f The list of functions to apply, the specific <i>f</i> chosen
                 is the one that best matches the value stored.
        \return The result of applying the chosen <i>f</i> to the stored value.
      */
      template<typename F1, typename... F>
      decltype(auto) apply(F1&& f1, F&&... f);

      //! Applies a function to the value stored by this variant.
      /*!
        \param f The list of functions to apply, the specific <i>f</i> chosen
                 is the one that best matches the value stored.
        \return The result of applying the chosen <i>f</i> to the stored value.
      */
      template<typename F1, typename... F>
      decltype(auto) apply(F1&& f1, F&&... f) const;

    private:
      using variant_union = details::get_variant_union_t<T...>;
      std::uint8_t m_which;
      variant_union m_value;
  };

  template<typename... T>
  std::ostream& operator <<(std::ostream& out, const variant<T...>& value) {
    return value.apply(
      [&] (auto& value) -> decltype(auto) {
        return (out << value);
      });
  }

  template<typename... T>
  variant<T...>::variant()
      : m_which(0) {
    new (&m_value) typename details::get_first<T...>::type();
  }

  template<typename... T>
  template<typename U, typename>
  variant<T...>::variant(U&& value) {
    m_which = details::construct_variant<0, T...>()(m_value,
      std::forward<U>(value));
  }

  template<typename... T>
  variant<T...>::variant(const variant& v) {
    v.apply(
      [&] (auto& v) {
        m_which = details::construct_variant<0, T...>()(m_value, v);
      });
  }

  template<typename... T>
  variant<T...>::~variant() {
    apply(
      [] (auto& value) {
        using U = std::decay_t<decltype(value)>;
        value.~U();
      });
  }

  template<typename... T>
  std::uint8_t variant<T...>::get_which() const {
    return m_which;
  }

  template<typename... T>
  template<typename F1, typename... F>
  decltype(auto) variant<T...>::apply(F1&& f1, F&&... f) {
    return details::apply_variant(m_which, m_value,
      [&] (auto& value) -> decltype(auto) {
        using U = decltype(value);
        return details::overload_variant<U, F1>()(value, f1,
          std::forward<F>(f)...);
      });
  }

  template<typename... T>
  template<typename F1, typename... F>
  decltype(auto) variant<T...>::apply(F1&& f1, F&&... f) const {
    return details::apply_variant(m_which, m_value,
      [&] (auto& value) -> decltype(auto) {
        using U = decltype(value);
        return details::overload_variant<U, F1>()(value, f1,
          std::forward<F>(f)...);
      });
  }
}

#endif

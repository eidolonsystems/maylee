#ifndef MAYLEE_FIXED_VARIANT_HPP
#define MAYLEE_FIXED_VARIANT_HPP
#include <cstdint>
#include <type_traits>
#include <utility>
#include "maylee/utilities/utilities.hpp"


#include <iostream>

template<typename T, typename F, typename = void>
struct InvokeVariant {
  template<typename H1, typename... H>
  decltype(auto) operator ()(const T& value, F&& f, H1&& h1, H&&... h) const {
    return InvokeVariant<T, std::decay_t<H1>>()(value, std::forward<H1>(h1),
      std::forward<H>(h)...);
  }

  template<typename H1, typename... H>
  decltype(auto) operator ()(T& value, F&& f, H1&& h1, H&&... h) const {
    return InvokeVariant<T, std::decay_t<H1>>()(value, std::forward<H1>(h1),
      std::forward<H>(h)...);
  }
};

template<typename T, typename F>
struct InvokeVariant<T, F,
    std::void_t<decltype(std::declval<F&&>()(std::declval<T&&>()))>> {
  template<typename... H>
  decltype(auto) operator ()(const T& value, F&& f, H&&... h) const {
    return f(value);
  }

  template<typename... H>
  decltype(auto) operator ()(T& value, F&& f, H&&... h) const {
    return f(value);
  }
};

template<typename T, typename F1, typename... F>
decltype(auto) invoke(T&& value, F1&& f1, F&&... f) {
  return InvokeVariant<T, std::decay_t<F1>>()(std::forward<T>(value),
    std::forward<F1>(f1), std::forward<F>(f)...);
}

auto h(int value) {
  std::cout << "h" << std::endl;
  return 123;
}

auto g(const std::string& value) {
  std::cout << "g" << std::endl;
  return 321;
}

int main(int argc, const char** argv) {
  auto r1 = invoke(std::string("hi"), g, h);
  std::cout << r1 << std::endl;
  auto r2 = invoke(123, g, h);
  std::cout << r2 << std::endl;
}


namespace maylee {
namespace details {
  template<typename T1, typename T2>
  union variant_union {
    T1 m_first;
    T2 m_second;

    variant_union() {}
    ~variant_union() {}
  };

  template<typename... T>
  struct get_variant_union;

  template<typename T>
  struct get_variant_union<T> {
    using type = T;
  };

  template<typename T1, typename... T2>
  struct get_variant_union<T1, T2...> {
    using type = variant_union<T1, typename get_variant_union<T2...>::type>;
  };

  template<std::uint8_t W, typename... T>
  struct construct_variant;

  template<std::uint8_t W, typename T>
  struct construct_variant<W, T> {
    template<typename V>
    std::uint8_t operator ()(V& lhs, const T& rhs) const {
      new (&lhs) T(rhs);
      return W;
    }

    template<typename V>
    std::uint8_t operator ()(V& lhs, T&& rhs) const {
      new (&lhs) T(std::move(rhs));
      return W;
    }
  };

  template<std::uint8_t W, typename T1, typename... T>
  struct construct_variant<W, T1, T...> : construct_variant<W, T1>,
      construct_variant<W + 1, T...> {
    using construct_variant<W, T1>::operator ();
    using construct_variant<W + 1, T...>::operator ();
  };

  template<typename... T>
  struct apply_variant;

  template<typename T>
  struct apply_variant<T> {
    template<typename V, typename F>
    std::void_t<decltype(std::declval<F&&>()(std::declval<const T&>()))> operator ()(V& lhs, F&& f) const {
      std::cout << typeid(const T&).name() << std::endl;
    }

//    template<typename V, typename F>
//    auto operator ()(V& lhs, F&& f) ->
//        std::enable_if_t<decltype(f(std::declval<T&>()))> {
//      std::cout << typeid(T&).name() << std::endl;
//    }
  };

  template<typename T1, typename... T>
  struct apply_variant<T1, T...> : apply_variant<T1>, apply_variant<T...> {
    using apply_variant<T1>::operator ();
    using apply_variant<T...>::operator ();
  };
}

  /*! \brief A class that stores a single value among a list of data types.
             Unlike a traditional union or variant, the value must be
             initialized on construction and the type can not change.
      \tparam T... The list of data types that can be stored.
   */
  template<typename... T>
  class fixed_variant {
    public:

      //! Constructs a fixed_variant representing a value of the first type in
      //! the template parameter pack T.
      fixed_variant();

      //! Constructs a fixed_variant representing a value constructible from a
      //! value of type <i>U</i>.
      template<typename U>
      fixed_variant(U&& value);

      ~fixed_variant();

      //! Returns the index of the type stored.
      std::uint8_t get_which() const;

      template<typename F>
      decltype(auto) apply(F&& f);

    private:
      using variant_union = typename details::get_variant_union<T...>::type;
      std::uint8_t m_which;
      variant_union m_value;
  };

  template<typename... T>
  fixed_variant<T...>::fixed_variant()
      : m_which(0) {
//    new (&m_value) T();
  }

  template<typename... T>
  template<typename U>
  fixed_variant<T...>::fixed_variant(U&& value) {
    m_which = details::construct_variant<0, T...>()(m_value,
      std::forward<U>(value));
  }

  template<typename... T>
  fixed_variant<T...>::~fixed_variant() {
    apply(
      [] (auto& value) {
        using T = std::decay_t<decltype(value)>;
        value.~T();
      });
  }

  template<typename... T>
  std::uint8_t fixed_variant<T...>::get_which() const {
    return m_which;
  }

  template<typename... T>
  template<typename F>
  decltype(auto) fixed_variant<T...>::apply(F&& f) {
    return details::apply_variant<T...>()(m_value, std::forward<F>(f));
  }
}

#endif

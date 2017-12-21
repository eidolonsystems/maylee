#ifndef MAYLEE_VARIANT_DETAILS_HPP
#define MAYLEE_VARIANT_DETAILS_HPP
#include <cstdint>
#include <type_traits>
#include "maylee/utilities/utilities.hpp"

namespace maylee {
namespace details {
  template<typename T1, typename T2>
  union variant_union {
    T1 m_first;
    T2 m_second;

    variant_union() {}
    variant_union(const variant_union&) {}
    ~variant_union() {}
  };

  template<typename T1, typename... T2>
  struct get_variant_union {
    using type = variant_union<T1, typename get_variant_union<T2...>::type>;
  };

  template<typename T>
  struct get_variant_union<T> {
    using type = T;
  };

  template<typename... T>
  using get_variant_union_t = typename get_variant_union<T...>::type;

  template<typename T1, typename... T2>
  struct get_first {
    using type = T1;
  };

  template<typename... T>
  using get_first_t = typename get_first<T...>::type;

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

  template<typename T, typename F>
  decltype(auto) apply_variant(std::uint8_t which, T& value, F&& f) {
    return f(value);
  }

  template<typename T, typename F>
  decltype(auto) apply_variant(std::uint8_t which, const T& value, F&& f) {
    return f(value);
  }

  template<typename T1, typename T2, typename F>
  decltype(auto) apply_variant(std::uint8_t which, variant_union<T1, T2>& value,
      F&& f) {
    if(which == 0) {
      return f(value.m_first);
    } else {
      return apply_variant(which - 1, value.m_second, std::forward<F>(f));
    }
  }

  template<typename T1, typename T2, typename F>
  decltype(auto) apply_variant(std::uint8_t which,
      const variant_union<T1, T2>& value, F&& f) {
    if(which == 0) {
      return f(value.m_first);
    } else {
      return apply_variant(which - 1, value.m_second, std::forward<F>(f));
    }
  }

  template<typename T, typename F, typename = void>
  struct overload_variant {
    template<typename H1, typename... H>
    decltype(auto) operator ()(T value, F f, H1&& h1, H&&... h) const {
      return overload_variant<T, std::decay_t<H1>>()(value,
        std::forward<H1>(h1), std::forward<H>(h)...);
    }
  };

  template<typename T, typename F>
  struct overload_variant<T, F,
      std::void_t<decltype(std::declval<F>()(std::declval<T>()))>> {
    template<typename... H>
    decltype(auto) operator ()(T value, F f, H&&... h) const {
      return f(value);
    }
  };
}
}

#endif

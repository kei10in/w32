#pragma once

#include <type_traits>

/// The macro `W32_DEFINE_ENUM_FLAG_OPERATORS` defines bit operators for enum
/// class used as bitflags.
#define W32_DEFINE_ENUM_FLAG_OPERATORS(ENUM_TYPE)                             \
                                                                              \
  constexpr ENUM_TYPE operator|(ENUM_TYPE lhs, ENUM_TYPE rhs) noexcept {      \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return static_cast<ENUM_TYPE>(static_cast<value_type>(lhs) |              \
                                  static_cast<value_type>(rhs));              \
  }                                                                           \
                                                                              \
  constexpr ENUM_TYPE operator&(ENUM_TYPE lhs, ENUM_TYPE rhs) noexcept {      \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return static_cast<ENUM_TYPE>(static_cast<value_type>(lhs) &              \
                                  static_cast<value_type>(rhs));              \
  }                                                                           \
                                                                              \
  constexpr ENUM_TYPE operator^(ENUM_TYPE lhs, ENUM_TYPE rhs) noexcept {      \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return static_cast<ENUM_TYPE>(static_cast<value_type>(lhs) ^              \
                                  static_cast<value_type>(rhs));              \
  }                                                                           \
                                                                              \
  inline ENUM_TYPE& operator|=(ENUM_TYPE& lhs, ENUM_TYPE rhs) noexcept {      \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return reinterpret_cast<ENUM_TYPE&>(reinterpret_cast<value_type&>(lhs) |= \
                                        static_cast<value_type>(rhs));        \
  }                                                                           \
                                                                              \
  inline ENUM_TYPE& operator&=(ENUM_TYPE& lhs, ENUM_TYPE rhs) noexcept {      \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return reinterpret_cast<ENUM_TYPE&>(reinterpret_cast<value_type&>(lhs) &= \
                                        static_cast<value_type>(rhs));        \
  }                                                                           \
                                                                              \
  inline ENUM_TYPE& operator^=(ENUM_TYPE& lhs, ENUM_TYPE rhs) noexcept {      \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return reinterpret_cast<ENUM_TYPE&>(reinterpret_cast<value_type&>(lhs) ^= \
                                        static_cast<value_type>(rhs));        \
  }                                                                           \
                                                                              \
  constexpr ENUM_TYPE operator~(ENUM_TYPE value) noexcept {                   \
    using value_type = std::underlying_type_t<ENUM_TYPE>;                     \
    return static_cast<ENUM_TYPE>(~static_cast<value_type>(value));           \
  }

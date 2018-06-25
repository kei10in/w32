#pragma once

#include <exception>
#include <variant>

namespace w32 {

class bad_result_access : public std::exception {
 public:
  char const* what() const noexcept override { return "bad_result_access"; }
};

template <class T>
class ok_t {
  T value_;

 public:
  using value_type = T;

  ok_t() : value_{} {}
  explicit ok_t(T v) : value_(std::move(v)) {}

  ok_t(ok_t const& rhs) = default;
  ok_t& operator=(ok_t const& rhs) = default;

  ok_t(ok_t&& rhs) = default;
  ok_t& operator=(ok_t&& rhs) = default;

  bool is_ok() const { return true; }
  bool is_err() const { return false; }

  value_type const& value() const { return value_; }
  value_type& value() { return value_; }
};

template <class T>
inline ok_t<T> ok(T&& value) {
  return ok_t<T>{std::forward<T>(value)};
}

template <class E>
class err_t {
  E value_;

 public:
  using value_type = E;

  explicit err_t(E v) : value_(std::move(v)) {}

  err_t(err_t const& rhs) = default;
  err_t& operator=(err_t const& rhs) = default;

  err_t(err_t&& rhs) = default;
  err_t& operator=(err_t&& rhs) = default;

  bool is_ok() const { return false; }
  bool is_err() const { return true; }

  value_type const& value() const { return value_; }
  value_type& value() { return value_; }
};

template <class E>
inline err_t<E> err(E&& value) {
  return err_t<E>{std::forward<E>(value)};
}

template <class T, class E>
class result {
  std::variant<ok_t<T>, err_t<E>> value_;

 public:
  using ok_type = T;
  using err_type = E;

  result() : value_(ok_t<T>{}) noexcept {}

  result(result const& rhs) = default;
  result& operator=(result const& rhs) = default;

  result(result&& rhs) = default;
  result& operator=(result&& rhs) = default;

  /// Construct from an ok value.
  result(ok_t<T> v) : value_(std::move(v)) {}

  /// Construct from an error value.
  result(err_t<E> v) : value_(std::move(v)) {}

  /// Return true if result is ok.
  operator bool() const noexcept { return is_ok(); }

  /// Return true if result is ok.
  bool is_ok() const noexcept {
    return std::visit([](auto const& v) -> bool { return v.is_ok(); }, value_);
  }

  /// Return true if result is err.
  bool is_err() const noexcept {
    return std::visit([](auto const& v) -> bool { return v.is_err(); }, value_);
  }

  ok_type const& operator*() const { return ok(); }

  ok_type& operator*() { return ok(); }

  ok_type const& ok() const {
    if (!is_ok()) {
      throw bad_result_access();
    }

    return std::get<0>(value_).value();
  }

  ok_type& ok() {
    if (!is_ok()) {
      throw bad_result_access();
    }

    return std::get<0>(value_).value();
  }

  err_type const& err() const {
    if (!is_err()) {
      throw bad_result_access();
    }

    return std::get<1>(value_).value();
  }

  err_type& err() {
    if (!is_err()) {
      throw bad_result_access();
    }

    return std::get<1>(value_).value();
  }
};

}  // namespace w32;

#pragma once

#include <Unknwn.h>

#include <cassert>
#include <cstdint>
#include <type_traits>

#include "com.hpp"
#include "com_ptr.hpp"

namespace w32::com {

namespace internal {

template <class T>
class unknown_t {
  template <class U>
  friend class unknown_t;

 protected:
  com_ptr<T> p_;

 public:
  using interface_type = T;
  using pointer = interface_type*;

  unknown_t() noexcept = default;

  unknown_t(unknown_t const& rhs) noexcept = default;
  unknown_t& operator=(unknown_t const& rhs) noexcept = default;

  unknown_t(unknown_t&& rhs) noexcept = default;
  unknown_t& operator=(unknown_t&& rhs) noexcept = default;

  unknown_t(interface_type* p) noexcept : p_(p) { assert(p_); }

  unknown_t& operator=(interface_type* p) noexcept {
    unknown_t(p).swap(*this);
    return *this;
  }

  unknown_t(com_ptr<interface_type> const& p) noexcept : p_(p) { assert(p_); }

  unknown_t& operator=(com_ptr<interface_type> const& p) noexcept {
    unknown_t(p).swap(*this);
    return *this;
  }

  unknown_t(com_ptr<interface_type>&& p) noexcept : p_(std::move(p)) {
    assert(p_);
  }

  unknown_t& operator=(com_ptr<interface_type>&& p) {
    unknown_t(std::move(p)).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t(unknown_t<U> const& rhs) noexcept : p_(rhs.p_) {}

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t& operator=(unknown_t<U> const& rhs) noexcept {
    unknown_t(rhs).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t(unknown_t<U>&& rhs) noexcept : p_(std::move(rhs.p_)){};

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t& operator=(unknown_t<U>&& rhs) noexcept {
    unknown_t(std::move(rhs)).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t(U* p) noexcept : p_(p) {
    assert(p_);
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t& operator=(U* p) noexcept {
    unknown_t(p).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t(com_ptr<U> const& p) noexcept : p_(p) {
    assert(p_);
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t& operator=(com_ptr<U> const& p) noexcept {
    unknown_t(p).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t(com_ptr<U>&& p) noexcept : p_(std::move(p)) {
    assert(p_);
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  unknown_t& operator=(com_ptr<U>&& p) {
    unknown_t(std::move(p)).swap(*this);
    return *this;
  }

  unknown_t(CLSID const& clsid, class_context context) noexcept
      : p_(make_com<interface_type>(clsid, context)) {
    assert(p_);
  }

  void swap(unknown_t& rhs) noexcept { p_.swap(rhs.p_); }

  pointer get() const { return p_.get(); }
};

}  // namespace internal

using unknown = internal::unknown_t<IUnknown>;

}  // namespace w32::com

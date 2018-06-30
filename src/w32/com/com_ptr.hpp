#pragma once

#include <Objbase.h>

#include <type_traits>

#include "error.hpp"

namespace w32::com {

template <class T>
class com_ptr {
 public:
  using interface_type = T;
  using pointer = interface_type*;

 private:
  pointer p_;

 public:
  constexpr com_ptr() noexcept : p_(nullptr) {}

  ~com_ptr() { reset(); }

  com_ptr(com_ptr const& rhs) noexcept : p_(rhs.p_) { add_ref(); }

  com_ptr& operator=(com_ptr const& rhs) noexcept {
    com_ptr(rhs).swap(*this);
    return *this;
  }

  com_ptr(com_ptr&& rhs) noexcept : p_(rhs.p_) { rhs.p_ = nullptr; }

  com_ptr& operator=(com_ptr&& rhs) noexcept {
    com_ptr(std::move(rhs)).swap(*this);
    return *this;
  }

  /// Construct from a raw pointer without incrementing reference counter.
  com_ptr(pointer p) noexcept : p_(p) {}

  /// Assign a raw pointer without incrementing reference counter.
  com_ptr& operator=(pointer p) noexcept {
    com_ptr(p).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  com_ptr(com_ptr<U> const& rhs) noexcept : p_(rhs.get()) {
    add_ref();
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  com_ptr& operator=(com_ptr<U> const& rhs) noexcept {
    com_ptr(rhs).swap(*this);
    return *this;
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  com_ptr(com_ptr<U>&& rhs) noexcept : p_(rhs.get()) {
    rhs.release();
  }

  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  com_ptr& operator=(com_ptr<U>&& rhs) noexcept {
    com_ptr(std::move(rhs)).swap(*this);
    return *this;
  }

  /// Construct from a raw pointer without incrementing reference counter.
  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  com_ptr(U* p) noexcept : p_(p) {}

  /// Assign a raw pointer without incrementing reference counter.
  template <class U, std::enable_if_t<std::is_convertible_v<U*, T*>>* = nullptr>
  com_ptr& operator=(U* p) noexcept {
    com_ptr(p).swap(*this);
    return *this;
  }

  /// Determine where owning valid resource.
  operator bool() const noexcept { return p_ != nullptr; }

  interface_type* operator->() const noexcept { return p_; }

  /// Return the address of internal pointer. This is useful when passing to the
  /// com object factory method
  interface_type** operator&() const noexcept {
    reset();
    return &p_;
  }

  /// Return a raw pointer.
  interface_type* get() const noexcept { return p_; }

  void swap(com_ptr& rhs) noexcept { std::swap(p_, rhs.p_); }

  /// Release ownership without decrement reference counter.
  pointer release() noexcept {
    auto old_p = p_;
    p_ = nullptr;
    return old_p;
  }

  /// Release ownership and own new resource without increment reference
  /// counter.
  void reset(pointer p) noexcept {
    if (p_ != nullptr) {
      p_->Release();
    }

    p_ = p;
  }

  /// Release ownership.
  void reset() noexcept { reset(pointer()); }

 private:
  void add_ref() {
    if (p_ != nullptr) {
      p_->AddRef();
    }
  }
};

template <class T, class U>
inline bool operator==(com_ptr<T> const& lhs, com_ptr<T> const& rhs) {
  return lhs.get() == rhs.get()
}

template <class T, class U>
inline bool operator!=(com_ptr<T> const& lhs, com_ptr<T> const& rhs) {
  return lhs.get() != rhs.get()
}

template <class Char, class Traits, class T>
inline std::basic_ostream<Char, Traits>& operator<<(
    std::basic_ostream<Char, Traits>& os,
    com_ptr<T> const& p) {
  os << p.get();
  return os;
}

enum class class_context : std::uint32_t {
  inproc_server = CLSCTX_INPROC_SERVER,
  inproc_handler = CLSCTX_INPROC_HANDLER,
  local_server = CLSCTX_LOCAL_SERVER,
  inproc_server16 = CLSCTX_INPROC_SERVER16,
  remote_server = CLSCTX_REMOTE_SERVER,
  inproc_handler16 = CLSCTX_INPROC_HANDLER16,
  reserved1 = CLSCTX_RESERVED1,
  reserved2 = CLSCTX_RESERVED2,
  reserved3 = CLSCTX_RESERVED3,
  reserved4 = CLSCTX_RESERVED4,
  no_code_download = CLSCTX_NO_CODE_DOWNLOAD,
  reserved5 = CLSCTX_RESERVED5,
  no_custom_marshal = CLSCTX_NO_CUSTOM_MARSHAL,
  enable_code_download = CLSCTX_ENABLE_CODE_DOWNLOAD,
  no_failure_log = CLSCTX_NO_FAILURE_LOG,
  disable_aaa = CLSCTX_DISABLE_AAA,
  enable_aaa = CLSCTX_ENABLE_AAA,
  from_default_context = CLSCTX_FROM_DEFAULT_CONTEXT,
  activate_32_bit_server = CLSCTX_ACTIVATE_32_BIT_SERVER,
  activate_64_bit_server = CLSCTX_ACTIVATE_64_BIT_SERVER,
  enable_cloaking = CLSCTX_ENABLE_CLOAKING,
  appcontainer = CLSCTX_APPCONTAINER,
  activate_aaa_as_iu = CLSCTX_ACTIVATE_AAA_AS_IU,
  ps_dll = static_cast<std::uint32_t>(CLSCTX_PS_DLL),
  all = CLSCTX_ALL,
};

template <class T>
com_ptr<T> make_com(CLSID const& clsid, class_context context) {
  T* p;

  HRESULT const hr =
      CoCreateInstance(clsid, nullptr, static_cast<std::uint32_t>(context),
                       __uuidof(T), reinterpret_cast<void**>(&p));

  raise_if_failed(hr);

  return p;
}

}  // namespace w32::com

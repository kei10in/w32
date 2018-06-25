#pragma once

#define WIN32WIN32_LEAN_AND_MEAN
#include <WinBase.h>

#include <exception>
#include <memory>
#include <string>

namespace w32::com {

namespace internal {

struct local_free_delete {
  void operator()(void* p) const {
    if (p != nullptr) {
      LocalFree(p);
    }
  }
};

}  // namespace internal

class error : public std::exception {
  HRESULT hr_;

 public:
  error(HRESULT hr) noexcept : hr_(hr) {}

  error(error const& rhs) = default;
  error& operator=(error const& rhs) = default;

  error(error&& rhs) = default;
  error& operator=(error&& rhs) = default;

  char const* what() const noexcept override { return "w32::com::error"; }

  /// The message member function returns system message for the error.
  std::wstring message() const {
    wchar_t* message = nullptr;

    std::uint32_t length = FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr,
        hr_, 0, (LPWSTR)&message, 0, nullptr);

    if (message != nullptr) {
      if (length > 1 && message[length - 1] == L'\n') {
        message[length - 1] = 0;
        if (message[length - 2] == L'\r') {
          message[length - 2] = 0;
        }
      }
    }

    std::unique_ptr<wchar_t, internal::local_free_delete> p{message};

    return message;
  }
};

[[noreturn]] inline void raise_error(HRESULT hr) {
  throw error(hr);
}

inline void raise_if_failed(HRESULT hr) {
  if (FAILED(hr)) {
    raise_error(hr);
  }
}

}  // namespace w32::com

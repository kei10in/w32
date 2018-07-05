#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Objbase.h>

#include <cstdint>
#include <type_traits>
#include <vector>

namespace w32::com {

using clsid = CLSID;

enum class co_init : std::uint32_t {
  multi_threaded = COINIT_MULTITHREADED,
  apartment_threaded = COINIT_APARTMENTTHREADED,
  disable_ole1_dde = COINIT_DISABLE_OLE1DDE,
  speed_over_memory = COINIT_SPEED_OVER_MEMORY,
};

inline co_init operator|(co_init lhs, co_init rhs) {
  using value_type = std::underlying_type_t<co_init>;
  return static_cast<co_init>(static_cast<value_type>(lhs) |
                              static_cast<value_type>(rhs));
}

class com {
 public:
  com() noexcept {
    CoInitializeEx(nullptr,
                   static_cast<std::uint32_t>(co_init::multi_threaded));
  }
  ~com() noexcept { CoUninitialize(); }
};

}  // namespace w32::com

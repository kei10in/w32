#pragma once

#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class component_info_t : com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;
};

}  // namespacde w32::wic::internal

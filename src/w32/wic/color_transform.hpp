#pragma once

#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class color_transform_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;
};

}  // namespace w32::wic::internal

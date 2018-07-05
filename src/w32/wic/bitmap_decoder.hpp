#pragma once

#include <Wincodec.h>

#include "wic_fwd.hpp"

namespace w32::wic {

enum class decode_options {
  cache_on_demand = WICDecodeMetadataCacheOnDemand,
  cache_on_load = WICDecodeMetadataCacheOnLoad,
};

namespace internal {

template <class T>
class bitmap_decoder_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;
};

}  // namespace internal
}  // namespace w32::wic

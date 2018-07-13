#pragma once

#include <Wincodec.h>

#include "../fundamentals.hpp"
#include "bitmap_view.hpp"
#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class bitmap_lock_t : public com::internal::unknown_t<T> {
 public:
  com::internal::unknown_t<T>::unknown_t;

  bitmap_view get_view() {
    HRESULT hr;
    bitmap_view result;

    hr = p_->GetSize(&result.size.width, &result.size.height);
    com::raise_if_failed(hr);

    std::uint32_t stride;
    hr = p_->GetStride(&stride);
    com::raise_if_failed(hr);
    result.stride = stride;

    hr = p_->GetPixelFormat(&result.pixel_format);
    com::raise_if_failed(hr);

    std::uint32_t buffer_size;
    hr = p_->GetDataPointer(&buffer_size, &result.data);
    com::raise_if_failed(hr);
    result.buffer_size = buffer_size;

    return result;
  }
};

}  // namespace w32::wic::internal

#pragma once

#include <Wincodec.h>

#include "../com/unknown.hpp"
#include "../fundamentals.hpp"
#include "bitmap_view.hpp"

namespace w32::wic {

enum class bitmap_lock_mode : std::uint32_t {
  read = WICBitmapLockRead,
  write = WICBitmapLockWrite,
  read_and_write = WICBitmapLockRead | WICBitmapLockWrite,
};

namespace internal {

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

}  // namespace internal

using bitmap_lock = internal::bitmap_lock_t<IWICBitmapLock>;

}  // namespace w32::wic

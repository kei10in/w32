#pragma once

#include <Wincodec.h>

#include "../com.hpp"
#include "../com/error.hpp"
#include "bitmap.hpp"
#include "pixel_format.hpp"

namespace w32::wic {

namespace internal {

template <class T>
class imaging_factory_t : public w32::com::internal::unknown_t<T> {
 public:
  imaging_factory_t()
      : w32::com::internal::unknown_t<T>(
            CLSID_WICImagingFactory,
            w32::com::class_context::inproc_server) {}

  bitmap create_bitmap(std::uint32_t width,
                       std::uint32_t height,
                       pixel_format_id const& pixel_format,
                       bitmap_create_cache_option option) const {
    IWICBitmap* bmp;
    HRESULT hr =
        p_->CreateBitmap(width, height, pixel_format,
                         static_cast<WICBitmapCreateCacheOption>(option), &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  bitmap create_bitmap(size<std::uint32_t> size,
                       pixel_format_id const& pixel_format,
                       bitmap_create_cache_option option) const {
    return create_bitmap(size.width, size.height, pixel_format, option);
  }
};

}  // namespace internal

using imaging_factory = internal::imaging_factory_t<IWICImagingFactory>;

}  // namespace w32::wic

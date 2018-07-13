#pragma once

#include <Wincodec.h>

#include "../fundamentals.hpp"
#include "palette.hpp"
#include "wic_fwd.hpp"
#include "wic_guids.hpp"

namespace w32::wic {

namespace internal {

template <class T>
class bitmap_source_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  size<std::uint32_t> get_size() const {
    UINT w, h;
    HRESULT hr = p_->GetSize(&w, &h);
    com::raise_if_failed(hr);
    return size<std::uint32_t>{w, h};
  }

  resolution<double> get_resolution() const {
    double dpi_x, dpi_y;
    HRESULT hr = p_->GetResolution(&dpi_x, &dpi_y);
    com::raise_if_failed(hr);
    return resolution<double>{dpi_x, dpi_y};
  }

  pixel_format_id get_pixel_format() const {
    pixel_format_id pixel_format;
    HRESULT hr = p_->GetPixelFormat(&pixel_format);
    com::raise_if_failed(hr);
    return pixel_format_id{pixel_format};
  }

  void copy_pixels(rect<std::int32_t> const& rc,
                   std::uint32_t stride,
                   std::uint32_t size,
                   byte* buffer) const {
    WICRect r{rc.x, rc.y, rc.width, rc.height};
    HRESULT hr = p_->CopyPixels(&r, stride, size, buffer);
    com::raise_if_failed(hr);
  }

  void copy_palette(palette& p) const {
    HRESULT hr = p_->CopyPalette(p.get());
    com::raise_if_failed(hr);
  }
};

}  // namespace internal

using bitmap_source = internal::bitmap_source_t<IWICBitmapSource>;

}  // namespace w32::wic

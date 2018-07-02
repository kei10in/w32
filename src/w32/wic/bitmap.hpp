#pragma once

#include "../fundamentals.hpp"
#include "bitmap_lock.hpp"
#include "wic_fwd.hpp"

namespace w32::wic {

enum class bitmap_create_cache_option {
  no_cache = WICBitmapNoCache,
  cache_on_demand = WICBitmapCacheOnDemand,
  cache_on_load = WICBitmapCacheOnLoad,
};

namespace internal {

template <class T>
class bitmap_t : public bitmap_source_t<T> {
 public:
  using bitmap_source_t<T>::bitmap_source_t;

  void set_resolution(double dpi_x, double dpi_y) {
    HRESULT hr = p_->SetResolution(dpi_x, dpi_y);
    com::raise_if_failed(hr);
  }

  void set_resolution(resolution<double> const& res) {
    set_resolution(res.dpi_x, res.dpi_y)
  }

  void set_palette(palette const& p) {
    HRESULT hr = p_->SetPalette(p.get());
    com::raise_if_failed(hr);
  }

  bitmap_lock lock(rect<std::int32_t> const& rc, bitmap_lock_mode mode) {
    WICRect r{rc.x, rc.y, rc.width, rc.height};
    IWICBitmapLock* lock;
    HRESULT hr = p_->Lock(&r, static_cast<std::uint32_t>(mode), &lock);
    com::raise_if_failed(hr);
    return lock;
  }
};

}  // namespace internal

using bitmap = internal::bitmap_t<IWICBitmap>;

}  // namespace w32::wic

#pragma once

#include "bitmap_source.hpp"
#include "wic_fwd.hpp"

namespace w32::wic {

using color_t = WICColor;

namespace internal {

template <class T>
class palette_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  void initialize_predefined(bitmap_palette_type palette_type,
                             bool add_transparent_color) {
    HRESULT hr = p_->InitializePredefined(
        static_cast<WICBitmapPaletteType>(palette_type), add_transparent_color);
    com::raise_if_failed(hr);
  }

  void initialize_custom(color_t const* colors, std::size_t count) const {
    HRESULT hr = p_->InitializeCustom(const_cast<color_t*>(colors),
                                      static_cast<std::uint32_t>(count));
    com::raise_if_failed(hr);
  }

  void initialize_from_bitmap(bitmap_source const& surface,
                              std::uint32_t count,
                              bool add_transparent_color) const {
    HRESULT hr =
        p_->InitializeFromBitmap(surface.get(), count, add_transparent_color);
    com::raise_if_failed(hr);
  }

  void initialize_from_palette(palette const& palette) {
    HRESULT hr = p_->InitializeFromPalette(palette.get());
    com::raise_if_failed(hr);
  }

  bitmap_palette_type get_type() const {
    WICBitmapPaletteType palette_type;
    HRESULT hr = p_->GetType(&palette_type);
    com::raise_if_failed(hr);
    return static_cast<bitmap_palette_type>(palette_type);
  }

  std::size_t get_color_count() const {
    std::uint32_t count;
    HRESULT hr = p_->GetColorCount(&count);
    com::raise_if_failed(hr);
    return static_cast<std::size_t>(count);
  }

  std::size_t get_colors(std::size_t count, color_t* colors) const {
    std::uint32_t actual_colors;
    HRESULT hr = p_->GetColors(static_cast<std::uint32_t>(count), colors,
                               &actual_colors);
    com::raise_if_failed(hr);
    return actual_colors;
  }

  bool is_black_white() const {
    BOOL flag;
    HRESULT hr = p_->IsBlackWhite(&flag);
    com::raise_if_failed(hr);
    return static_cast<bool>(flag);
  }

  bool is_grayscale() const {
    BOOL flag;
    HRESULT hr = p_->IsGrayscale(&flag);
    com::raise_if_failed(hr);
    return static_cast<bool>(flag);
  }

  bool has_alpha() const {
    BOOL flag;
    HRESULT hr = p_->HasAlpha(&flag);
    com::raise_if_failed(hr);
    return flag != 0;
  }
};

}  // namespace internal

using palette = internal::palette_t<IWICPalette>;

}  // namespace w32::wic

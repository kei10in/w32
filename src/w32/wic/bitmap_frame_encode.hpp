#pragma once

#include "../com/ocidl.hpp"
#include "../fundamentals.hpp"
#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class bitmap_frame_encode_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  inline void initialize(com::property_bag_2 const* encoder_options) const;

  inline void set_size(std::uint32_t width, std::uint32_t height) const;

  inline void set_resolution(double dpi_x, double dpi_y) const;

  inline pixel_format_id set_pixel_format(
      pixel_format_id const& pixel_format) const;

  inline void set_color_contexts(color_context const* color_contexts,
                                 std::size_t count) const;

  inline void set_palette(palette const& p) const;

  inline void set_thumbnail(bitmap_source const& thumbnail) const;

  inline void write_pixels(std::uint32_t lines,
                           std::size_t stride,
                           std::size_t size,
                           std::byte const* pixels) const;

  inline void write_source(bitmap_source const& source,
                           rect<std::int32_t> const& rc) const;

  inline void write_source(bitmap_source const& source) const;

  inline void commit() const;

  inline metadata_query_writer get_metadata_query_writer() const;
};

template <class T>
inline void bitmap_frame_encode_t<T>::initialize(
    com::property_bag_2 const* encoder_options) const {
  HRESULT hr = p_->Initialize(
      encoder_options == nullptr ? nullptr : encoder_options->get());
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::set_size(std::uint32_t width,
                                               std::uint32_t height) const {
  HRESULT hr = p_->SetSize(width, height);
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::set_resolution(double dpi_x,
                                                     double dpi_y) const {
  HRESULT hr = p_->SetResolution(dpi_x, dpi_y);
  com::raise_if_failed(hr);
}

template <class T>
inline pixel_format_id bitmap_frame_encode_t<T>::set_pixel_format(
    pixel_format_id const& pixel_format) const {
  pixel_format_id pf = pixel_format;
  HRESULT hr = p_->SetPixelFormat(&pf);
  com::raise_if_failed(hr);
  return pf;
}

template <class T>
inline void bitmap_frame_encode_t<T>::set_color_contexts(
    color_context const* color_contexts,
    std::size_t count) const {
  HRESULT hr = p_->SetColorContexts(
      static_cast<std::uint32_t>(count),
      reinterpret_cast<IWICColorContext**>(color_contexts));
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::set_palette(palette const& p) const {
  HRESULT hr = p_->SetPalette(p.get());
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::set_thumbnail(
    bitmap_source const& thumbnail) const {
  HRESULT hr = p_->SetThumbnail(thumbnail.get());
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::write_pixels(
    std::uint32_t lines,
    std::size_t stride,
    std::size_t size,
    std::byte const* pixels) const {
  HRESULT hr = p_->WritePixels(
      lines, static_cast<std::uint32_t>(stride),
      static_cast<std::uint32_t>(size),
      reinterpret_cast<std::uint8_t*>(const_cast<std::byte*>(pixels)));
}

template <class T>
inline void bitmap_frame_encode_t<T>::write_source(
    bitmap_source const& source,
    rect<std::int32_t> const& rc) const {
  WICRect r{rc.x, rc.y, rc.width, rc.height};
  HRESULT hr = p_->WriteSource(source.get(), &r);
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::write_source(
    bitmap_source const& source) const {
  HRESULT hr = p_->WriteSource(source.get(), nullptr);
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_frame_encode_t<T>::commit() const {
  HRESULT hr = p_->Commit();
  com::raise_if_failed(hr);
}

template <class T>
inline metadata_query_writer
bitmap_frame_encode_t<T>::get_metadata_query_writer() const {
  IWICMetadataQueryWriter* writer;
  HRESULT hr = p_->GetMetadataQueryWriter(&writer);
  com::raise_if_failed(hr);
  return writer;
}

}  // namespace w32::wic::internal

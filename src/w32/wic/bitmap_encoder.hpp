#pragma once

#include "../com/ocidl.hpp"
#include "bitmap_codec_info.hpp"
#include "bitmap_frame_encode.hpp"
#include "metadata_query_writer.hpp"
#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class bitmap_encoder_info_t : public bitmap_codec_info_t<T> {
 public:
  using bitmap_codec_info_t<T>::bitmap_codec_info_t;
};

template <class T>
class bitmap_encoder_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  inline void initialize(stream const& s,
                         bitmap_encoder_cache_option cache_option) const;

  inline container_format_id get_container_format() const;

  inline bitmap_encoder_info get_encoder_info() const;

  inline void set_color_contexts(std::size_t count,
                                 color_context* color_contexts) const;

  inline void set_palette(palette const& p) const;

  inline void set_thumbnail(bitmap_source const& thumbnail) const;

  inline void set_preview(bitmap_source const& preview) const;

  inline bitmap_frame_encode create_new_frame(
      com::property_bag_2* encoder_options) const;

  inline void commit() const;

  inline metadata_query_writer get_metadata_query_writer() const;
};

template <class T>
inline void bitmap_encoder_t<T>::initialize(
    stream const& s,
    bitmap_encoder_cache_option cache_option) const {
  HRESULT hr = p_->Initialize(
      s.get(), static_cast<WICBitmapEncoderCacheOption>(cache_option));
  com::raise_if_failed(hr);
}

template <class T>
inline container_format_id bitmap_encoder_t<T>::get_container_format() const {
  container_format_id container_format;
  HRESULT hr = p_->GetContainerFormat(&container_format);
  com::raise_if_failed(hr);
  return container_format;
}

template <class T>
inline bitmap_encoder_info bitmap_encoder_t<T>::get_encoder_info() const {
  IWICBitmapEncoderInfo* encoder_info;
  HRESULT hr = p_->GetEncoderInfo(&encoder_info);
  com::raise_if_failed(hr);
  return encoder_info;
}

template <class T>
inline void bitmap_encoder_t<T>::set_color_contexts(
    std::size_t count,
    color_context* color_contexts) const {
  HRESULT hr = p_->SetColorContexts(
      static_cast<std::uint32_t>(count),
      reinterpret_cast<IWICColorContext**>(color_contexts));
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_encoder_t<T>::set_palette(palette const& p) const {
  HRESULT hr = p_->SetPalette(p.get());
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_encoder_t<T>::set_thumbnail(
    bitmap_source const& thumbnail) const {
  HRESULT hr = p_->SetThumbnail(thumbnail.get());
  com::raise_if_failed(hr);
}

template <class T>
inline void bitmap_encoder_t<T>::set_preview(
    bitmap_source const& preview) const {
  HRESULT hr = p_->SetPreview(preview.get());
  com::raise_if_failed(hr);
}

template <class T>
inline bitmap_frame_encode bitmap_encoder_t<T>::create_new_frame(
    com::property_bag_2* encoder_options) const {
  IWICBitmapFrameEncode* frame_encode;
  IPropertyBag2* pb;
  HRESULT hr = p_->CreateNewFrame(&frame_encode, &pb);
  com::raise_if_failed(hr);
  if (encoder_options != nullptr) {
    *encoder_options = pb;
  }

  return frame_encode;
}

template <class T>
inline void bitmap_encoder_t<T>::commit() const {
  HRESULT hr = p_->Commit();
  com::raise_if_failed(hr);
}

template <class T>
inline metadata_query_writer bitmap_encoder_t<T>::get_metadata_query_writer()
    const {
  IWICMetadataQueryWriter* query_writer;
  HRESULT hr = p_->GetMetadataQueryWriter(&query_writer);
  com::raise_if_failed(hr);
  return query_writer;
}

}  // namespace w32::wic::internal

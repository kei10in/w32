#pragma once

#include <memory>

#include "bitmap_source.hpp"
#include "metadata_query_reader.hpp"
#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class bitmap_frame_decode_t : public bitmap_source_t<T> {
 public:
  using bitmap_source_t<T>::bitmap_source_t;

  inline metadata_query_reader get_metadata_query_reader() const;

  template <class Allocator = std::allocator<color_context>>
  std::vector<color_context, Allocator> get_color_contexts(
      Allocator const& alloc = Allocator{}) const;

  inline bitmap_source get_thumbnail() const;
};

template <class T>
inline metadata_query_reader
bitmap_frame_decode_t<T>::get_metadata_query_reader() const {
  IWICMetadataQueryReader* query_reader;
  HRESULT hr = p_->GetMetadataQueryReader(&query_reader);
  com::raise_if_failed(hr);
  return query_reader;
}

template <class T>
template <class Allocator>
std::vector<color_context, Allocator>
bitmap_frame_decode_t<T>::get_color_contexts(Allocator const& alloc) const {
  UINT needed;
  HRESULT hr;

  hr = p_->GetColorContexts(0, nullptr, &needed);
  com::raise_if_failed(hr);

  std::vector<color_context, Allocator> buffer{needed, alloc};

  hr = p_->GetColorContexts(
      needed, reinterpret_cast<IWICColorContext**>(buffer.data()), &needed);
  com::raise_if_failed(hr);

  return buffer;
}

template <class T>
inline bitmap_source bitmap_frame_decode_t<T>::get_thumbnail() const {
  IWICBitmapSource* thumbnail;
  HRESULT hr = p_->GetThumbnail(&thumbnail);
  com::raise_if_failed(hr);
  return thumbnail;
}

}  // namespace w32::wic::internal

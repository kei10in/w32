#pragma once

#include <Wincodec.h>

#include "../guid.hpp"
#include "../utils/enum_flags.hpp"
#include "bitmap_decoder_info.hpp"
#include "bitmap_frame_decode.hpp"
#include "metadata_query_reader.hpp"
#include "palette.hpp"
#include "wic_fwd.hpp"

namespace w32::wic {

namespace internal {

template <class T>
class bitmap_decoder_t : public com::internal::unknown_t<T> {
 public:
  using com::internal::unknown_t<T>::unknown_t;

  bitmap_decoder_capabilities query_capability(com::stream const& stream) {
    DWORD capability;
    HRESULT hr = p_->QueryCapability(stream.get(), &capability);
    com::raise_if_failed(hr);
    return static_cast<bitmap_decoder_capabilities>(capability);
  }

  void initialize(com::stream const& stream, decode_options cache_options) {
    HRESULT hr = p_->Initialize(stream.get(),
                                static_cast<WICDecodeOptions>(cache_options));
    com::raise_if_failed(hr);
  }

  guid get_container_format() {
    guid container_format;
    HRESULT hr = p_->GetContainerFormat(&container_format);
    com::raise_if_failed(hr);
    return container_format;
  }

  bitmap_decoder_info get_decoder_info() {
    IWICBitmapDecoderInfo* decoder_info;
    HRESULT hr = p_->GetDecoderInfo(&decoder_info);
    com::raise_if_failed(hr);
    return decoder_info;
  }

  void copy_palette(palette& p) {
    HRESULT hr = p_->CopyPalette(p.get());
    com::raise_if_failed(hr);
  }

  metadata_query_reader get_metadata_query_reader() {
    IWICMetadataQueryReader* reader;
    HRESULT hr = p_->GetMetadataQueryReader(&reader);
    com::raise_if_failed(hr);
    return reader;
  }

  bitmap_source get_preview() {
    IWICBitmapSource* preview;
    HRESULT hr = p_->GetPreview(&preview);
    com::raise_if_failed(hr);
    return preview;
  }

  std::size_t get_color_contexts(std::size_t count, color_context* contexts) {
    static_assert(
        sizeof(IWICColorContext*) == sizeof(color_context),
        "The `color_context` must be compliant with `IWICColorContext*`.");

    std::uint32_t actual;
    HRESULT hr = p_->GetColorContexts(
        static_cast<std::uint32_t>(count),
        reinterpret_cast<IWICColorContext**>(&contexts), &actual);
    com::raise_if_failed(hr);
    return actual;
  }

  bitmap_source get_thumbnail() {
    IWICBitmapSource* thumbnail;
    HRESULT hr = p_->GetThumbnail(&thumbnail);
    com::raise_if_failed(hr);
    return thumbnail;
  }

  std::size_t get_frame_count() {
    std::uint32_t count;
    HRESULT hr = p_->GetFrameCount(&count);
    com::raise_if_failed(hr);
    return count;
  }

  bitmap_frame_decode get_frame(std::size_t index) {
    IWICBitmapFrameDecode* decoder;
    HRESULT hr = p_->GetFrame(static_cast<std::uint32_t>(index), &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }
};

}  // namespace internal
}  // namespace w32::wic

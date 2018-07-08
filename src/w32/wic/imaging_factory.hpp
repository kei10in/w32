#pragma once

#include <Wincodec.h>

#include <filesystem>

#include "../fileapi.hpp"
#include "bitmap.hpp"
#include "bitmap_clipper.hpp"
#include "bitmap_decoder.hpp"
#include "bitmap_encoder.hpp"
#include "bitmap_flip_rotator.hpp"
#include "bitmap_scaler.hpp"
#include "color_context.hpp"
#include "color_transform.hpp"
#include "component_info.hpp"
#include "fast_metadata_encoder.hpp"
#include "format_converter.hpp"
#include "metadata_query_reader.hpp"
#include "metadata_query_writer.hpp"
#include "palette.hpp"
#include "pixel_format.hpp"
#include "stream.hpp"
#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class imaging_factory_t : public w32::com::internal::unknown_t<T> {
 public:
  imaging_factory_t()
      : w32::com::internal::unknown_t<T>{
            com::make_com<T>(CLSID_WICImagingFactory,
                             w32::com::class_context::inproc_server)} {}

  bitmap_decoder create_decoder_from_filename(
      std::filesystem::path const& filename,
      guid const* vendor,
      generic_access_right desired_access,
      decode_options option) const {
    IWICBitmapDecoder* decoder;
    HRESULT hr = p_->CreateDecoderFromFilename(
        filename.native().c_str(), vendor,
        static_cast<std::uint32_t>(desired_access),
        static_cast<WICDecodeOptions>(option), &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }

  bitmap_decoder create_decoder_from_stream(com::stream const& stream,
                                            guid const* vendor,
                                            decode_options option) const {
    IWICBitmapDecoder* decoder;
    HRESULT hr = p_->CreateDecoderFromStream(
        stream.get(), vendor, static_cast<WICDecodeOptions>(option), &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }

  // bitmap_decoder create_decoder_from_file_handle(void* file_handle,
  //                                                guid const* guid
  //                                                decode_options
  //                                                    metadataOptions) const;

  component_info create_component_info(
      com::clsid const& component_clsid) const {
    IWICComponentInfo* info;
    HRESULT hr = p_->CreateComponentInfo(component_clsid, &info);
    com::raise_if_failed(hr);
    return info;
  }

  bitmap_decoder create_decoder(guid const& container_format,
                                guid const* vendor) const {
    IWICBitmapDecoder* decoder;
    HRESULT hr = p_->CreateDecoder(container_format, vendor, &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }

  bitmap_encoder create_encoder(guid const& container_format,
                                guid const* vendor) const {
    IWICBitmapEncoder* encoder;
    HRESULT hr = p_->CreateEncoder(container_format, vendor, &encoder);
    com::raise_if_failed(hr);
    return encoder;
  }

  palette create_palette() const {
    IWICPalette* palette;
    HRESULT hr = p_->CreatePalette(&palette);
    com::raise_if_failed(hr);
    return palette;
  }

  format_converter create_format_converter() const {
    IWICFormatConverter* converter;
    HRESULT hr = p_->CreateFormatConverter(&converter);
    com::raise_if_failed(hr);
    return converter;
  }

  bitmap_scaler create_bitmap_scaler() const {
    IWICBitmapScaler* scaler;
    HRESULT hr = p_->CreateBitmapScaler(&scaler);
    com::raise_if_failed(hr);
    return scaler;
  }

  bitmap_clipper create_bitmap_clipper() const {
    IWICBitmapClipper* clipper;
    HRESULT hr = p_->CreateBitmapClipper(&clipper);
    com::raise_if_failed(hr);
    return clipper;
  }

  bitmap_flip_rotator create_bitmap_flip_rotator() const {
    IWICBitmapFlipRotator* flip_rotator;
    HRESULT hr = p_->CreateBitmapFlipRotator(&flip_rotator);
    com::raise_if_failed(hr);
    return flip_rotator;
  }

  stream create_stream() const {
    IWICStream* stream;
    HRESULT hr = p_->CreateStream(&stream);
    com::raise_if_failed(hr);
    return stream;
  }

  color_context create_color_context() const {
    IWICColorContext* context;
    HRESULT hr = p_->CreateColorContext(&context);
    com::raise_if_failed(hr);
    return context;
  }

  color_transform create_color_transformer() const {
    IWICColorTransform* transform;
    HRESULT hr = p_->CreateColorTransformer(&transform);
    com::raise_if_failed(hr);
    return transform;
  }

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

  bitmap create_bitmap_from_source(bitmap_source const& source,
                                   bitmap_create_cache_option option) const {
    IWICBitmap* bmp;
    HRESULT hr = p_->CreateBitmapFromSource(
        source.get(), static_cast<WICBitmapCreateCacheOption>(option), &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  bitmap create_bitmap_from_source_rect(bitmap_source const& source,
                                        std::uint32_t x,
                                        std::uint32_t y,
                                        std::uint32_t width,
                                        std::uint32_t height) const {
    IWICBitmap* bmp;
    HRESULT hr =
        p_->CreateBitmapFromSourceRect(source.get(), x, y, width, height, &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  bitmap create_bitmap_from_memory(std::uint32_t width,
                                   std::uint32_t height,
                                   pixel_format_id pixel_format,
                                   std::size_t stride,
                                   std::size_t buffer_size,
                                   byte* buffer) const {
    IWICBitmap* bmp;
    HRESULT hr = p_->CreateBitmapFromMemory(
        width, height, pixel_format, static_cast<uint32_t>(stride),
        static_cast<std::uint32_t>(buffer_size), buffer, &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  // bitmap create_bitmap_from_hbitmap(HBITMAP hBitmap,
  //                                   HPALETTE hPalette,
  //                                   WICBitmapAlphaChannelOption options)
  //                                   const;

  // bitmap create_bitmap_from_hicon(HICON hIcon);

  // create_component_enumerator(std::uint32_t componentTypes,
  //                             std::uint32_t options,
  //                             IEnumUnknown** ppIEnumUnknown) const;

  fast_metadata_encoder create_fast_metadata_encoder_from_decoder(
      bitmap_decoder const& decoder) const {
    IWICFastMetadataEncoder* encoder;
    HRESULT hr =
        p_->CreateFastMetadataEncoderFromDecoder(decoder.get(), &encoder);
    com::raise_if_failed(hr);
    return encoder;
  }

  fast_metadata_encoder create_fast_metadata_encoder_from_frame_decode(
      bitmap_frame_decode* frame_decoder) const {
    IWICFastMetadataEncoder* encoder;
    HRESULT hr = p_->CreateFastMetadataEncoderFromFrameDecode(
        frame_decoder.get(), &encoder);
    com::raise_if_failed(hr);
    return encoder;
  }

  metadata_query_writer create_query_writer(guid const& metadata_format,
                                            guid const* vendor) const {
    IWICMetadataQueryWriter* writer;
    HRESULT hr = p_->CreateQueryWriter(metadata_format, vendor, &writer);
    com::raise_if_failed(hr);
    return writer;
  }

  metadata_query_writer create_query_writer_from_reader(
      metadata_query_reader* query_reader,
      guid const* vendor) const {
    IWICMetadataQueryWriter* writer;
    HRESULT hr =
        p_->CreateQueryWriterFromReader(query_reader.get(), vendor, &writer);
    com::raise_if_failed(hr);
    return writer;
  }
};

}  // namespace w32::wic::internal

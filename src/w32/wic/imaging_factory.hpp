#pragma once

#include <Wincodec.h>

#include <filesystem>

#include "../fileapi.hpp"
#include "bitmap_clipper.hpp"
#include "bitmap_decoder.hpp"
#include "bitmap_encoder.hpp"
#include "bitmap_flip_rotator.hpp"
#include "bitmap_scaler.hpp"
#include "bitmap.hpp"
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

namespace w32::wic {

namespace internal {

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
      decode_options option) {
    IWICBitmapDecoder* decoder;
    HRESULT hr = p_->CreateDecoderFromFilename(
        filename.native(), vender, static_cast<std::uint32_t>(desired_access),
        static_cast<WICDecodeOptions>(option), &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }

  bitmap_decoder create_decoder_from_stream(com::stream const& stream,
                                            guid const* vendor,
                                            decode_options option) {
    IWICBitmapDecoder* decoder;
    HRESULT hr = p_->CreateDecoderFromStream(
        stream.get(), vendor, static_cast<WICDecodeOptions>(option), &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }

  // bitmap_decoder create_decoder_from_file_handle(void* file_handle,
  //                                                guid const* guid
  //                                                decode_options
  //                                                    metadataOptions);

  component_info create_component_info(com::clsid const& component_clsid) {
    IWICComponentInfo* info;
    HRESULT hr = p_->CreateComponentInfo(component_clsid, &info);
    com::raise_if_failed(hr);
    return info;
  }

  bitmap_decoder create_decoder(guid const& container_format,
                                guid const* vendor) {
    IWICBitmapDecoder* decoder;
    HRESULT hr =
        p_->CreateDecoder(guid const& container_format, vendor, &decoder);
    com::raise_if_failed(hr);
    return decoder;
  }

  bitmap_encoder create_encoder(guid const& container_format,
                                guid const* vendor) {
    IWICBitmapEncoder* encoder;
    HRESULT hr =
        p_->CreateDecoder(guid const& container_format, vendor, &encoder);
    com::raise_if_failed(hr);
    return encoder;
  }

  palette create_palette() {
    IWICPalette* palette;
    HRESULT hr = p_->CreatePalette(&palette);
    com::raise_if_failed(hr);
    return palette;
  }

  format_converter create_format_converter() {
    IWICFormatConverter* format_converter;
    HRESULT hr = p_->CreateFormatConverter(&format_converter);
    com::raise_if_failed(hr);
    return format_converter;
  }

  bitmap_scaler create_bitmap_scaler() {
    IWICBitmapScaler* scaler;
    HRESULT hr = p_->CreateBitmapScaler(&scaler);
    com::raise_if_failed(hr);
    return scaler;
  }

  bitmap_clipper create_bitmap_clipper() {
    IWICBitmapClipper* clipper;
    HRESULT hr = p_->CreateBitmapClipper(&clipper);
    com::raise_if_failed(hr);
    return clipper;
  }

  bitmap_flip_rotator create_bitmap_flip_rotator() {
    IWICBitmapFlipRotator* flip_rotator;
    HRESULT hr = p_->CraeteBitmapFlipRotator(&flip_rotator);
    com::raise_if_failed(hr);
    return flip_rotator;
  }

  stream create_stream() {
    IWICStream* stream;
    HRESULT hr = p_->CreateStream(&stream);
    com::raise_if_failed(hr);
    return stream;
  }

  color_context create_color_context() {
    IWICColorContext* context;
    HRESULT hr = p_->CreateColorContext(&context);
    com::raise_if_failed(hr);
    return context;
  }

  color_transform create_color_transformer() {
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
                                   bitmap_create_cache_option option) {
    IWICBitmap* bmp;
    HRESULT hr = p_->CreateBitmap(
        source.get(), static_cast<WICBitmapCreateCacheOption>(option), &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  bitmap create_bitmap_from_source_rect(bitmap_source const& source,
                                        std::uint32_t x,
                                        std::uint32_t y,
                                        std::uint32_t width,
                                        std::uint32_t height) {
    IWICBitmap* bmp;
    HRESULT hr = p_->CreateBitmap(source.get(), x, y, width, height, &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  bitmap create_bitmap_from_memory(std::uint32_t width,
                                   std::uint32_t height,
                                   pixel_format_id pixel_format,
                                   std::size_t stride,
                                   std::size_t buffer_size,
                                   byte* buffer) {
    IWICBitmap* bmp;
    HRESULT hr = p_->CreateBitmapFromMemory(
        width, height, pixel_format, static_cast<uint32_t>(stride),
        static_cast<std::uint32_t>(buffer_size), buffer, &bmp);
    com::raise_if_failed(hr);
    return bmp;
  }

  // bitmap create_bitmap_from_hbitmap(HBITMAP hBitmap,
  //                                   HPALETTE hPalette,
  //                                   WICBitmapAlphaChannelOption options);

  // bitmap create_bitmap_from_hicon(HICON hIcon);

  // create_component_enumerator(std::uint32_t componentTypes,
  //                             std::uint32_t options,
  //                             IEnumUnknown** ppIEnumUnknown);

  fast_metadata_encoder create_fast_metadata_encoder_from_decoder(
      bitmap_decoder const& decoder) {
    IWICFastMetadataEncoder* encoder;
    HRESULT hr =
        p_->CreateFastMetadataEncoderFromDecoder(decoder.get(), &encoder);
    com::raise_if_failed(hr);
    return encoder;
  }

  fast_metadata_encoder create_fast_metadata_encoder_from_frame_decode(
      bitmap_frame_decode* frame_decoder) {
    IWICFastMetadataEncoder* encoder;
    HRESULT hr = p_->CreateFastMetadataEncoderFromFrameDecode(
        frame_decoder.get(), &encoder);
    com::raise_if_failed(hr);
    return encoder;
  }

  metadata_query_writer create_query_writer(guid const& metadata_format,
                                            guid const* vendor) {
    IWICMetadataQueryWriter* writer;
    HRESULT hr = p_->CreateQueryWriter(metadata_format, vendor, &writer);
    com::raise_if_failed(hr);
    return writer;
  }

  metadata_query_writer create_query_writer_from_reader(
      metadata_query_reader* query_reader,
      guid const* vendor) {
    IWICMetadataQueryWriter* writer;
    HRESULT hr =
        p_->CreateQueryWriterFromReader(query_reader.get(), vendor, &writer);
    com::raise_if_failed(hr);
    return writer;
  }
};

}  // namespace internal

using imaging_factory = internal::imaging_factory_t<IWICImagingFactory>;

}  // namespace w32::wic

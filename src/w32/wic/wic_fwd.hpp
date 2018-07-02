#pragma once

#include "../com.hpp"

namespace w32::wic {

namespace internal {

template <class T>
class palette_t;

template <class T>
class bitmap_source_t;

template <class T>
class format_converter_t;

template <class T>
class planar_format_converter_t;

template <class T>
class bitmap_scaler_t;

template <class T>
class bitmap_clipper_t;

template <class T>
class bitmap_flip_rotator_t;

template <class T>
class bitmap_lock_t;

template <class T>
class bitmap_t;

template <class T>
class color_context_t;

template <class T>
class color_transform_t;

template <class T>
class fast_metadata_encoder_t;

template <class T>
class stream_t;

template <class T>
class enum_metadata_item_t;

template <class T>
class metadata_query_reader_t;

template <class T>
class metadata_query_writer_t;

template <class T>
class bitmap_encoder_t;

template <class T>
class bitmap_frame_encode_t;

template <class T>
class planar_bitmap_frame_encode_t;

template <class T>
class image_encoder_t;

template <class T>
class bitmap_decoder_t;

template <class T>
class bitmap_source_transform_t;

template <class T>
class planar_bitmap_source_transform_t;

template <class T>
class bitmap_frame_decode_t;

template <class T>
class progressive_level_control_t;

template <class T>
class progress_callback_t;

template <class T>
class bitmap_codec_progress_notification_t;

template <class T>
class component_info_t;

template <class T>
class format_converter_info_t;

template <class T>
class bitmap_codec_info_t;

template <class T>
class bitmap_encoder_info_t;

template <class T>
class bitmap_decoder_info_t;

template <class T>
class pixel_format_info_t;

template <class T>
class pixel_format_info2_t;

template <class T>
class imaging_factory_t;

template <class T>
class imaging_factory2_t;

template <class T>
class develop_raw_notification_callback_t;

template <class T>
class develop_raw_t;

template <class T>
class dds_decoder_t;

template <class T>
class dds_encoder_t;

template <class T>
class dds_frame_decode_t;

template <class T>
class jpeg_frame_decode_t;

template <class T>
class jpeg_frame_encode_t;

}  // namespace internal

using palette = internal::palette_t<IWICPalette>;
using bitmap_source = internal::bitmap_source_t<IWICBitmapSource>;
using format_converter = internal::format_converter_t<IWICFormatConverter>;
using planar_format_converter =
    internal::planar_format_converter_t<IWICPlanarFormatConverter>;
using bitmap_scaler = internal::bitmap_scaler_t<IWICBitmapScaler>;
using bitmap_clipper = internal::bitmap_clipper_t<IWICBitmapClipper>;
using bitmap_flip_rotator =
    internal::bitmap_flip_rotator_t<IWICBitmapFlipRotator>;
using bitmap_lock = internal::bitmap_lock_t<IWICBitmapLock>;
using bitmap = internal::bitmap_t<IWICBitmap>;
using color_context = internal::color_context_t<IWICColorContext>;
using color_transform = internal::color_transform_t<IWICColorTransform>;
using fast_metadata_encoder =
    internal::fast_metadata_encoder_t<IWICFastMetadataEncoder>;
using stream = internal::stream_t<IWICStream>;
using enum_metadata_item = internal::enum_metadata_item_t<IWICEnumMetadataItem>;
using metadata_query_reader =
    internal::metadata_query_reader_t<IWICMetadataQueryReader>;
using metadata_query_writer =
    internal::metadata_query_writer_t<IWICMetadataQueryWriter>;
using bitmap_encoder = internal::bitmap_encoder_t<IWICBitmapEncoder>;
using bitmap_frame_encode =
    internal::bitmap_frame_encode_t<IWICBitmapFrameEncode>;
using planar_bitmap_frame_encode =
    internal::planar_bitmap_frame_encode_t<IWICPlanarBitmapFrameEncode>;
using image_encoder = internal::image_encoder_t<IWICImageEncoder>;
using bitmap_decoder = internal::bitmap_decoder_t<IWICBitmapDecoder>;
using bitmap_source_transform =
    internal::bitmap_source_transform_t<IWICBitmapSourceTransform>;
using planar_bitmap_source_transform =
    internal::planar_bitmap_source_transform_t<IWICPlanarBitmapSourceTransform>;
using bitmap_frame_decode =
    internal::bitmap_frame_decode_t<IWICBitmapFrameDecode>;
using progressive_level_control =
    internal::progressive_level_control_t<IWICProgressiveLevelControl>;
using progress_callback = internal::progress_callback_t<IWICProgressCallback>;
using bitmap_codec_progress_notification =
    internal::bitmap_codec_progress_notification_t<
        IWICBitmapCodecProgressNotification>;
using component_info = internal::component_info_t<IWICComponentInfo>;
using format_converter_info =
    internal::format_converter_info_t<IWICFormatConverterInfo>;
using bitmap_codec_info = internal::bitmap_codec_info_t<IWICBitmapCodecInfo>;
using bitmap_encoder_info =
    internal::bitmap_encoder_info_t<IWICBitmapEncoderInfo>;
using bitmap_decoder_info =
    internal::bitmap_decoder_info_t<IWICBitmapDecoderInfo>;
using pixel_format_info = internal::pixel_format_info_t<IWICPixelFormatInfo>;
using pixel_format_info2 = internal::pixel_format_info2_t<IWICPixelFormatInfo2>;
using imaging_factory = internal::imaging_factory_t<IWICImagingFactory>;
using imaging_factory2 = internal::imaging_factory2_t<IWICImagingFactory2>;
using develop_raw_notification_callback =
    internal::develop_raw_notification_callback_t<
        IWICDevelopRawNotificationCallback>;
using develop_raw = internal::develop_raw_t<IWICDevelopRaw>;
using dds_decoder = internal::dds_decoder_t<IWICDdsDecoder>;
using dds_encoder = internal::dds_encoder_t<IWICDdsEncoder>;
using dds_frame_decode = internal::dds_frame_decode_t<IWICDdsFrameDecode>;
using jpeg_frame_decode = internal::jpeg_frame_decode_t<IWICJpegFrameDecode>;
using jpeg_frame_encode = internal::jpeg_frame_encode_t<IWICJpegFrameEncode>;

}  // namespace w32::wic

#pragma once

#include <cstdint>

#include <WinCodec.h>

#include "../utils/enum_flags.hpp"

namespace w32::wic {

enum class color_context_type : std::uint32_t {
  uninitialized = WICColorContextUninitialized,
  profile = WICColorContextProfile,
  exif_color_space = WICColorContextExifColorSpace,
};

enum class bitmap_create_cache_option : std::uint32_t {
  no_cache = WICBitmapNoCache,
  cache_on_demand = WICBitmapCacheOnDemand,
  cache_on_load = WICBitmapCacheOnLoad,
};

enum class decode_options : std::uint32_t {
  cache_on_demand = WICDecodeMetadataCacheOnDemand,
  cache_on_load = WICDecodeMetadataCacheOnLoad,
};

enum class bitmap_encoder_cache_option : std::uint32_t {
  cache_in_memory = WICBitmapEncoderCacheInMemory,
  cache_temp_file = WICBitmapEncoderCacheTempFile,
  no_cache = WICBitmapEncoderNoCache,
};

enum class component_type : std::uint32_t {
  decoder = WICDecoder,
  encoder = WICEncoder,
  pixel_format_converter = WICPixelFormatConverter,
  metadata_reader = WICMetadataReader,
  metadata_writer = WICMetadataWriter,
  pixel_format = WICPixelFormat,
  all_components = WICAllComponents,
};

W32_DEFINE_ENUM_FLAG_OPERATORS(component_type)

enum class component_enumerate_options : std::uint32_t {
  enabled = WICComponentEnumerateDefault,
  refresh = WICComponentEnumerateRefresh,
  disabled = static_cast<std::uint32_t>(WICComponentEnumerateDisabled),
  no_signature = WICComponentEnumerateUnsigned,
  built_in_only = WICComponentEnumerateBuiltInOnly,
};

W32_DEFINE_ENUM_FLAG_OPERATORS(component_enumerate_options)

enum class bitmap_interpolation_mode : std::uint32_t {
  nearest_neighbor = WICBitmapInterpolationModeNearestNeighbor,
  linear = WICBitmapInterpolationModeLinear,
  cubic = WICBitmapInterpolationModeCubic,
  fant = WICBitmapInterpolationModeFant,
  high_quality_cubic = WICBitmapInterpolationModeHighQualityCubic,
};

enum class bitmap_palette_type : std::uint32_t {
  custom = WICBitmapPaletteTypeCustom,
  median_cut = WICBitmapPaletteTypeMedianCut,
  fixed_black_white = WICBitmapPaletteTypeFixedBW,
  fixed_halftone_8 = WICBitmapPaletteTypeFixedHalftone8,
  fixed_halftone_27 = WICBitmapPaletteTypeFixedHalftone27,
  fixed_halftone_64 = WICBitmapPaletteTypeFixedHalftone64,
  fixed_halftone_125 = WICBitmapPaletteTypeFixedHalftone125,
  fixed_halftone_216 = WICBitmapPaletteTypeFixedHalftone216,
  fixed_web_palette = WICBitmapPaletteTypeFixedWebPalette,
  fixed_halftone_252 = WICBitmapPaletteTypeFixedHalftone252,
  fixed_halftone_256 = WICBitmapPaletteTypeFixedHalftone256,
  fixed_gray_4 = WICBitmapPaletteTypeFixedGray4,
  fixed_gray_16 = WICBitmapPaletteTypeFixedGray16,
  fixed_gray_256 = WICBitmapPaletteTypeFixedGray256,
};

enum class bitmap_dither_type : std::uint32_t {
  none = WICBitmapDitherTypeNone,
  solid = WICBitmapDitherTypeSolid,
  ordered_4x4 = WICBitmapDitherTypeOrdered4x4,
  ordered_8x8 = WICBitmapDitherTypeOrdered8x8,
  ordered_16x16 = WICBitmapDitherTypeOrdered16x16,
  spiral_4x4 = WICBitmapDitherTypeSpiral4x4,
  spiral_8x8 = WICBitmapDitherTypeSpiral8x8,
  dual_spiral_4x4 = WICBitmapDitherTypeDualSpiral4x4,
  dual_spiral_8x8 = WICBitmapDitherTypeDualSpiral8x8,
  error_diffusion = WICBitmapDitherTypeErrorDiffusion,
};

enum class bitmap_alpha_channel_option : std::uint32_t {
  use_alpha = WICBitmapUseAlpha,
  use_premultiplied_alpha = WICBitmapUsePremultipliedAlpha,
  ignore_alpha = WICBitmapIgnoreAlpha,
};

enum class bitmap_transform_options : std::uint32_t {
  rotate_0 = WICBitmapTransformRotate0,
  rotate_90 = WICBitmapTransformRotate90,
  rotate_180 = WICBitmapTransformRotate180,
  rotate_270 = WICBitmapTransformRotate270,
  flip_horizontal = WICBitmapTransformFlipHorizontal,
  flip_vertical = WICBitmapTransformFlipVertical,
};

W32_DEFINE_ENUM_FLAG_OPERATORS(bitmap_transform_options)

enum class bitmap_lock_flags : std::uint32_t {
  read = WICBitmapLockRead,
  write = WICBitmapLockWrite,
  read_write = read | write,
};

enum class bitmap_decoder_capabilities : std::uint32_t {
  same_encoder = WICBitmapDecoderCapabilitySameEncoder,
  can_decode_all_images = WICBitmapDecoderCapabilityCanDecodeAllImages,
  can_decode_some_images = WICBitmapDecoderCapabilityCanDecodeSomeImages,
  can_enumerate_metadata = WICBitmapDecoderCapabilityCanEnumerateMetadata,
  can_decode_thumbnail = WICBitmapDecoderCapabilityCanDecodeThumbnail,
};

W32_DEFINE_ENUM_FLAG_OPERATORS(bitmap_decoder_capabilities)

enum class progress_operation : std::uint32_t {
  copy_pixels = WICProgressOperationCopyPixels,
  write_pixels = WICProgressOperationWritePixels,
  all = static_cast<std::uint32_t>(WICProgressOperationAll),
};

W32_DEFINE_ENUM_FLAG_OPERATORS(progress_operation)

enum class progress_notification : std::uint32_t {
  begin = WICProgressNotificationBegin,
  end = WICProgressNotificationEnd,
  frequent = WICProgressNotificationFrequent,
  all = static_cast<std::uint32_t>(WICProgressNotificationAll),
};

W32_DEFINE_ENUM_FLAG_OPERATORS(progress_notification)

enum class component_signing : std::uint32_t {
  with_signature = WICComponentSigned,
  without_signature = WICComponentUnsigned,
  safe = WICComponentSafe,
  disabled = static_cast<std::uint32_t>(WICComponentDisabled),
};

W32_DEFINE_ENUM_FLAG_OPERATORS(component_signing)

enum class gif_logical_screen_descriptor_properties : std::uint32_t {
  signature = WICGifLogicalScreenSignature,
  width = WICGifLogicalScreenDescriptorWidth,
  height = WICGifLogicalScreenDescriptorHeight,
  global_color_table_flag = WICGifLogicalScreenDescriptorGlobalColorTableFlag,
  color_resolution = WICGifLogicalScreenDescriptorColorResolution,
  sort_flag = WICGifLogicalScreenDescriptorSortFlag,
  global_color_table_size = WICGifLogicalScreenDescriptorGlobalColorTableSize,
  background_color_index = WICGifLogicalScreenDescriptorBackgroundColorIndex,
  pixel_aspect_ratio = WICGifLogicalScreenDescriptorPixelAspectRatio,
};

enum class gif_image_descriptor_properties : std::uint32_t {
  left = WICGifImageDescriptorLeft,
  top = WICGifImageDescriptorTop,
  width = WICGifImageDescriptorWidth,
  height = WICGifImageDescriptorHeight,
  local_color_table_flag = WICGifImageDescriptorLocalColorTableFlag,
  interlace_flag = WICGifImageDescriptorInterlaceFlag,
  sort_flag = WICGifImageDescriptorSortFlag,
  local_color_table_size = WICGifImageDescriptorLocalColorTableSize,
};

enum class gif_graphic_control_extension_properties : std::uint32_t {
  disposal = WICGifGraphicControlExtensionDisposal,
  user_input_flag = WICGifGraphicControlExtensionUserInputFlag,
  transparency_flag = WICGifGraphicControlExtensionTransparencyFlag,
  delay = WICGifGraphicControlExtensionDelay,
  transparent_color_index = WICGifGraphicControlExtensionTransparentColorIndex,
};

enum class gif_application_extension_properties : std::uint32_t {
  application = WICGifApplicationExtensionApplication,
  data = WICGifApplicationExtensionData,
};

enum class gif_comment_extension_properties : std::uint32_t {
  text = WICGifCommentExtensionText,
};

enum class jpeg_comment_properties : std::uint32_t {
  text = WICJpegCommentText,
};

enum class jpeg_luminance_properties : std::uint32_t {
  table = WICJpegLuminanceTable,
};

enum class jpeg_chrominance_properties : std::uint32_t {
  table = WICJpegChrominanceTable,
};

enum class _8_bim_iptc_properties : std::uint32_t {
  p_string = WIC8BIMIptcPString,
  embedded_iptc = WIC8BIMIptcEmbeddedIPTC,
};

enum class _8_bim_resolution_info_properties : std::uint32_t {
  p_string = WIC8BIMResolutionInfoPString,
  h_resolution = WIC8BIMResolutionInfoHResolution,
  h_resolution_unit = WIC8BIMResolutionInfoHResolutionUnit,
  width_unit = WIC8BIMResolutionInfoWidthUnit,
  v_resolution = WIC8BIMResolutionInfoVResolution,
  v_resolution_unit = WIC8BIMResolutionInfoVResolutionUnit,
  height_unit = WIC8BIMResolutionInfoHeightUnit,
};

enum class _8_bim_iptc_digest_properties : std::uint32_t {
  p_string = WIC8BIMIptcDigestPString,
  iptc_digest = WIC8BIMIptcDigestIptcDigest,
};

enum class png_gama_properties : std::uint32_t {
  gamma = WICPngGamaGamma,
};

enum class png_bkgd_properties : std::uint32_t {
  background_color = WICPngBkgdBackgroundColor,
};

enum class png_itxt_properties : std::uint32_t {
  keyword = WICPngItxtKeyword,
  compression_flag = WICPngItxtCompressionFlag,
  language_tag = WICPngItxtLanguageTag,
  translated_keyword = WICPngItxtTranslatedKeyword,
  text = WICPngItxtText,
};

enum class png_chrm_properties : std::uint32_t {
  white_point_x = WICPngChrmWhitePointX,
  white_point_y = WICPngChrmWhitePointY,
  red_x = WICPngChrmRedX,
  red_y = WICPngChrmRedY,
  green_x = WICPngChrmGreenX,
  green_y = WICPngChrmGreenY,
  blue_x = WICPngChrmBlueX,
  blue_y = WICPngChrmBlueY,
};

enum class png_hist_properties : std::uint32_t {
  frequencies = WICPngHistFrequencies,
};

enum class png_iccp_properties : std::uint32_t {
  name = WICPngIccpProfileName,
  data = WICPngIccpProfileData,
};

enum class png_srgb_properties : std::uint32_t {
  rendering_intent = WICPngSrgbRenderingIntent,
};

enum class png_time_properties : std::uint32_t {
  year = WICPngTimeYear,
  month = WICPngTimeMonth,
  day = WICPngTimeDay,
  hour = WICPngTimeHour,
  minute = WICPngTimeMinute,
  second = WICPngTimeSecond,
};

enum class section_access_level : std::uint32_t {
  read = WICSectionAccessLevelRead,
  read_write = WICSectionAccessLevelReadWrite,
};

W32_DEFINE_ENUM_FLAG_OPERATORS(section_access_level)

enum class pixel_format_numeric_representation : std::uint32_t {
  unspecified = WICPixelFormatNumericRepresentationUnspecified,
  indexed = WICPixelFormatNumericRepresentationIndexed,
  unsigned_integer = WICPixelFormatNumericRepresentationUnsignedInteger,
  signed_integer = WICPixelFormatNumericRepresentationSignedInteger,
  fixed = WICPixelFormatNumericRepresentationFixed,
  floating_point = WICPixelFormatNumericRepresentationFloat,
};

enum class planar_options : std::uint32_t {
  standard = WICPlanarOptionsDefault,
  preserve_subsampling = WICPlanarOptionsPreserveSubsampling,
};

enum class jpeg_indexing_options : std::uint32_t {
  generate_on_demand = WICJpegIndexingOptionsGenerateOnDemand,
  generate_on_load = WICJpegIndexingOptionsGenerateOnLoad,
};

enum class jpeg_transfer_matrix : std::uint32_t {
  identity = WICJpegTransferMatrixIdentity,
  bt601 = WICJpegTransferMatrixBT601,
};

enum class jpeg_scan_type : std::uint32_t {
  interleaved = WICJpegScanTypeInterleaved,
  planar_components = WICJpegScanTypePlanarComponents,
  progressive = WICJpegScanTypeProgressive,
};

}  // namespace w32::wic

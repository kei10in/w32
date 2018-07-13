#pragma once

#include <WinCodec.h>
#include <WinCodecSdk.h>

#include "../guid.hpp"

namespace w32::wic {

struct metadata_format_id_tag {};
using metadata_format_id = tagged_guid<metadata_format_id_tag>;

// Metadata formats
const metadata_format_id metadata_format_unknown{GUID_MetadataFormatUnknown};
const metadata_format_id metadata_format_ifd{GUID_MetadataFormatIfd};
const metadata_format_id metadata_format_sub_ifd{GUID_MetadataFormatSubIfd};
const metadata_format_id metadata_format_exif{GUID_MetadataFormatExif};
const metadata_format_id metadata_format_gps{GUID_MetadataFormatGps};
const metadata_format_id metadata_format_interop{GUID_MetadataFormatInterop};
const metadata_format_id metadata_format_app_0{GUID_MetadataFormatApp0};
const metadata_format_id metadata_format_app_1{GUID_MetadataFormatApp1};
const metadata_format_id metadata_format_app_13{GUID_MetadataFormatApp13};
const metadata_format_id metadata_format_iptc{GUID_MetadataFormatIPTC};
const metadata_format_id metadata_format_irb{GUID_MetadataFormatIRB};
const metadata_format_id metadata_format_8_bimiptc{GUID_MetadataFormat8BIMIPTC};
const metadata_format_id metadata_format_8_bim_resolution_info{
    GUID_MetadataFormat8BIMResolutionInfo};
const metadata_format_id metadata_format_8_bimiptc_digest{
    GUID_MetadataFormat8BIMIPTCDigest};
const metadata_format_id metadata_format_xmp{GUID_MetadataFormatXMP};
const metadata_format_id metadata_format_thumbnail{
    GUID_MetadataFormatThumbnail};
const metadata_format_id metadata_format_chunk_text{
    GUID_MetadataFormatChunktEXt};
const metadata_format_id metadata_format_xmp_struct{
    GUID_MetadataFormatXMPStruct};
const metadata_format_id metadata_format_xmp_bag{GUID_MetadataFormatXMPBag};
const metadata_format_id metadata_format_xmp_seq{GUID_MetadataFormatXMPSeq};
const metadata_format_id metadata_format_xmp_alt{GUID_MetadataFormatXMPAlt};
const metadata_format_id metadata_format_lsd{GUID_MetadataFormatLSD};
const metadata_format_id metadata_format_imd{GUID_MetadataFormatIMD};
const metadata_format_id metadata_format_gce{GUID_MetadataFormatGCE};
const metadata_format_id metadata_format_ape{GUID_MetadataFormatAPE};
const metadata_format_id metadata_format_jpeg_chrominance{
    GUID_MetadataFormatJpegChrominance};
const metadata_format_id metadata_format_jpeg_luminance{
    GUID_MetadataFormatJpegLuminance};
const metadata_format_id metadata_format_jpeg_comment{
    GUID_MetadataFormatJpegComment};
const metadata_format_id metadata_format_gif_comment{
    GUID_MetadataFormatGifComment};
const metadata_format_id metadata_format_chunk_gama{
    GUID_MetadataFormatChunkgAMA};
const metadata_format_id metadata_format_chunk_bkgd{
    GUID_MetadataFormatChunkbKGD};
const metadata_format_id metadata_format_chunk_itxt{
    GUID_MetadataFormatChunkiTXt};
const metadata_format_id metadata_format_chunk_chrm{
    GUID_MetadataFormatChunkcHRM};
const metadata_format_id metadata_format_chunk_hist{
    GUID_MetadataFormatChunkhIST};
const metadata_format_id metadata_format_chunk_iccp{
    GUID_MetadataFormatChunkiCCP};
const metadata_format_id metadata_format_chunk_srgb{
    GUID_MetadataFormatChunksRGB};
const metadata_format_id metadata_format_chunk_time{
    GUID_MetadataFormatChunktIME};
const metadata_format_id metadata_format_dds{GUID_MetadataFormatDds};

}  // namespace w32::wic

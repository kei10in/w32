#pragma once

#include <filesystem>

#include "wic_fwd.hpp"

namespace w32::wic::internal {

template <class T>
class stream_t : public com::internal::stream_t<T> {
 public:
  using com::internal::stream_t<T>::stream_t;

  void initialize_from_stream(com::stream const& s) {
    HRESULT hr = p_->InitializeFromIStream(s.get());
    com::raise_if_failed(hr);
  }

  void initialize_from_filename(std::filesystem::path const& path,
                                generic_access_right desired_access) {
    HRESULT hr = p_->InitializeFromFilename(
        path.native().c_str(), static_cast<std::uint32_t>(desired_access));
    com::raise_if_failed(hr);
  }

  // void initialize_from_memory(WICInProcPointer pbBuffer,
  //                             DWORD cbBufferSize);
  //
  // void initialize_from_i_stream_region(com::stream* s,
  //                                      ULARGE_INTEGER ulOffset,
  //                                      ULARGE_INTEGER ulMaxSize) = 0;
};

}  // namespace w32::wic::internal

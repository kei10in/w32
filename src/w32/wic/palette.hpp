#pragma once

#include "../com/unknown.hpp"

namespace w32::wic {

namespace internal {

template <class T>
class palette_t : public com::internal::unknown_t<T> {};

}  // namespace internal

using palette = internal::palette_t<IWICPalette>;

}  // namespace w32::wic

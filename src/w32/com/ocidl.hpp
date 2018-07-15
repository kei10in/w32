#pragma once

#include <ocidl.h>

#include "unknown.hpp"

namespace w32::com {
namespace internal {

template <class T>
class property_bag_2_t : public unknown_t<T> {
 public:
  using unknown_t<T>::unknown_t;
};

}  // namespace internal

using property_bag_2 = internal::property_bag_2_t<IPropertyBag2>;

}  // namespace w32::com

/*!
  \file xyz_color-inl.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef REFLECT_XYZ_COLOR_INL_HPP
#define REFLECT_XYZ_COLOR_INL_HPP

#include "xyz_color.hpp"
// Zisc
#include "zisc/arithmetic_array.hpp"
// Nanairo
#include "rgb_color.hpp"
#include "yxy_color.hpp"
#include "NanairoCore/nanairo_core_config.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
inline
XyzColor::XyzColor() noexcept
{
}

/*!
  \details
  No detailed.
  */
inline
XyzColor::XyzColor(const Float x, const Float y, const Float z) noexcept :
    Color(x, y, z)
{
}

/*!
  \details
  No detailed.
  */
inline
XyzColor::XyzColor(const zisc::ArithmeticArray<Float, 3>& color) noexcept :
    Color(color)
{
}

/*!
  \details
  No detailed.
  */
inline
Float& XyzColor::x() noexcept
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
const Float& XyzColor::x() const noexcept
{
  return color_[0];
}

/*!
  \details
  No detailed.
  */
inline
Float& XyzColor::y() noexcept
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
const Float& XyzColor::y() const noexcept
{
  return color_[1];
}

/*!
  \details
  No detailed.
  */
inline
Float& XyzColor::z() noexcept
{
  return color_[2];
}

/*!
  \details
  No detailed.
  */
inline
const Float& XyzColor::z() const noexcept
{
  return color_[2];
}

} // namespace nanairo

#endif // REFLECT_XYZ_COLOR_INL_HPP

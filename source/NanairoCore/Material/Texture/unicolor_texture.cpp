/*!
  \file unicolor_texture.cpp
  \author Sho Ikeda

  Copyright (c) 2015 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "unicolor_texture.hpp"
// Standard C++ library
#include <cstddef>
// Qt
#include <QString>
// Zisc
#include "zisc/utility.hpp"
// Nanairo
#include "texture.hpp"
#include "NanairoCommon/keyword.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Data/wavelength_samples.hpp"
#include "NanairoCore/Sampling/sampled_spectra.hpp"
#include "NanairoCore/Utility/scene_settings.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
UnicolorTexture::UnicolorTexture(const System& system,
                                 const SceneSettings& settings,
                                 const QString& prefix) noexcept
{
  initialize(system, settings, prefix);
}

/*!
  \details
  No detailed.
  */
Float UnicolorTexture::floatValue(const Point2& /* coordinate */) const noexcept
{
  return float_value_;
}

/*!
  \details
  No detailed.
  */
std::size_t UnicolorTexture::textureSize() const noexcept
{
  return sizeof(spectra_value_) + sizeof(float_value_);
}

/*!
  \details
  No detailed.
  */
TextureType UnicolorTexture::type() const noexcept
{
  return TextureType::Unicolor;
}

/*!
  \details
  No detailed.
  */
Float UnicolorTexture::wavelengthValue(const Point2& /* coordinate */, 
                                       const uint16 wavelength) const noexcept
{
  return spectra_value_.getByWavelength(wavelength);
}

/*!
  \details
  No detailed.
  */
void UnicolorTexture::initialize(const System& system,
                                 const SceneSettings& settings,
                                 const QString& prefix) noexcept
{
  auto p = prefix + "/" + keyword::unicolorTexture;
  const auto key = p + "/" + keyword::textureColor;
  spectra_value_ = makeReflectiveDistribution(system, settings, key);
  float_value_ = spectra_value_.toReflectiveXyz(system).y(), 
  float_value_ = zisc::clamp(float_value_, 0.0, 1.0);
}

} // namespace nanairo
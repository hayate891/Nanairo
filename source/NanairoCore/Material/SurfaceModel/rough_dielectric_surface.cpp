/*!
  \file rough_dielectric_surface.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "rough_dielectric_surface.hpp"
// Standard C++ library
#include <cstddef>
#include <utility>
#include <vector>
// Qt
#include <QJsonObject>
#include <QString>
// Zisc
#include "zisc/error.hpp"
// Nanairo
#include "fresnel.hpp"
#include "surface_model.hpp"
#include "NanairoCommon/keyword.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Utility/scene_value.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
RoughDielectricSurface::RoughDielectricSurface(
    const QJsonObject& settings,
    const std::vector<const TextureModel*>& texture_list) noexcept
{
  initialize(settings, texture_list);
}

/*!
  \details
  No detailed.
  */
SurfaceType RoughDielectricSurface::type() const noexcept
{
  return SurfaceType::RoughDielectric;
}

/*!
  \details
  No detailed.
  */
void RoughDielectricSurface::initialize(
    const QJsonObject& settings,
    const std::vector<const TextureModel*>& texture_list) noexcept
{
  const auto texture_index = SceneValue::toInt<uint>(settings,
                                                     keyword::roughnessIndex);
  roughness_ = texture_list[texture_index];

  const auto outer_refractive_index_settings =
      SceneValue::toString(settings, keyword::outerRefractiveIndex);
  const auto n1 = SpectralDistribution::makeSpectra(outer_refractive_index_settings);
  ZISC_ASSERT(!n1.hasValue(0.0), "The n1 contains zero value.");
  ZISC_ASSERT(!n1.hasNegative(), "The n1 contains negative value.");

  const auto inner_refractive_index_settings =
      SceneValue::toString(settings, keyword::innerRefractiveIndex);
  const auto n2 = SpectralDistribution::makeSpectra(inner_refractive_index_settings);
  ZISC_ASSERT(!n2.hasNegative(), "The n2 contains negative value.");

  eta_ = n2 / n1;
}

} // namespace nanairo

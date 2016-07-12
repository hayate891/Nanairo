/*!
  \file surface_scattering_model.cpp
  \author Sho Ikeda

  Copyright (c) 2015 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "surface_model.hpp"
// Standard C++ library
#include <cstddef>
#include <vector>
// Qt
#include <QString>
// Zisc
#include "zisc/algorithm.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Nanairo
#include "rough_dielectric_surface.hpp"
#include "rough_conductor_surface.hpp"
#include "smooth_conductor_surface.hpp"
#include "smooth_dielectric_surface.hpp"
#include "smooth_diffuse_surface.hpp"
#include "NanairoCommon/keyword.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Utility/scene_settings.hpp"
#include "NanairoCore/Utility/unique_pointer.hpp"

namespace nanairo {

// Forward declaration
class Texture;

/*!
  */
SurfaceModel::~SurfaceModel() noexcept
{
}

/*!
  \details
  No detailed.
  */
UniquePointer<SurfaceModel> makeSurface(
    const SceneSettings& settings,
    const QString& prefix,
    const std::vector<const Texture*>& texture_list) noexcept
{
  using zisc::toHash32;

  SurfaceModel* surface_scattering = nullptr;

  const auto type = settings.stringValue(prefix + "/" + keyword::type);
  switch (keyword::toHash32(type)) {
   case toHash32(keyword::smoothDiffuseSurface):
    surface_scattering = new SmoothDiffuseSurface{settings, prefix, texture_list};
    break;
   case toHash32(keyword::smoothDielectricSurface):
    surface_scattering = new SmoothDielectricSurface{settings, prefix};
    break;
   case toHash32(keyword::smoothConductorSurface):
    surface_scattering = new SmoothConductorSurface{settings, prefix};
    break;
   case toHash32(keyword::roughDielectricSurface):
    surface_scattering = new RoughDielectricSurface{settings, prefix, texture_list};
    break;
   case toHash32(keyword::roughConductorSurface):
    surface_scattering = new RoughConductorSurface{settings, prefix, texture_list};
    break;
   default:
    zisc::raiseError("SurfaceError: Unsupported type is specified.");
    break;
  }

  return UniquePointer<SurfaceModel>{surface_scattering};
}

} // namespace nanairo
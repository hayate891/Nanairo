/*!
  \file rough_dielectric_surface-inl.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_ROUGH_DIELECTRIC_SURFACE_INL_HPP
#define NANAIRO_ROUGH_DIELECTRIC_SURFACE_INL_HPP

#include "rough_dielectric_surface.hpp"
// Standard C++ library
#include <tuple>
// Zisc
#include "zisc/aligned_memory_pool.hpp"
#include "zisc/error.hpp"
#include "zisc/utility.hpp"
// Nanairo
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Data/intersection_info.hpp"
#include "NanairoCore/Data/wavelength_samples.hpp"
#include "NanairoCore/Geometry/vector.hpp"
#include "NanairoCore/Material/shader_model.hpp"
#include "NanairoCore/Material/Bxdf/ggx_dielectric_bsdf.hpp"
#include "NanairoCore/Material/TextureModel/texture_model.hpp"
#include "NanairoCore/Sampling/sampled_spectra.hpp"
#include "NanairoCore/Utility/unique_pointer.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
template <uint kSampleSize>
auto RoughDielectricSurface::makeGgxDielectricBsdf(
    const Point2& texture_coordinate,
    const bool is_reverse_face,
    const WavelengthSamples<kSampleSize>& wavelengths,
    MemoryPool& memory_pool) const noexcept -> ShaderPointer<kSampleSize>
{
  // Get the roughness
  constexpr Float min_roughness = 0.001;
  Float roughness = roughness_->floatValue(texture_coordinate);
  roughness = (min_roughness < roughness)
      ? roughness * roughness
      : min_roughness * min_roughness;
  ZISC_ASSERT(zisc::isInClosedBounds(roughness, 0.0, 1.0),
              "The roughness is out of the range [0, 1].");

  // Evaluate the refractive index
  const auto wavelength = wavelengths[wavelengths.primaryWavelengthIndex()];
  const Float n = (is_reverse_face)
      ? 1.0 / eta_.getByWavelength(wavelength)
      : eta_.getByWavelength(wavelength);

  // Make GGX BSDF
  using Bsdf = GgxDielectricBsdf<kSampleSize>;
  auto bsdf = memory_pool.allocate<Bsdf>(roughness, n);
  return ShaderPointer<kSampleSize>(bsdf);
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SurfaceModel::makeGgxDielectricBsdf(
    const Point2& texture_coordinate,
    const bool is_reverse_face,
    const WavelengthSamples<kSampleSize>& wavelengths,
    MemoryPool& memory_pool) const noexcept -> ShaderPointer<kSampleSize>
{
  auto s = zisc::cast<const RoughDielectricSurface*>(this);
  return s->makeGgxDielectricBsdf(texture_coordinate,
                                  is_reverse_face,
                                  wavelengths,
                                  memory_pool);
}

} // namespace nanairo

#endif // NANAIRO_ROUGH_DIELECTRIC_SURFACE_INL_HPP

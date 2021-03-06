/*!
  \file smooth_dielectric_surface.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_SMOOTH_DIELECTRIC_SURFACE_HPP
#define NANAIRO_SMOOTH_DIELECTRIC_SURFACE_HPP

// Standard C++ library
#include <cstddef>
#include <vector>
// Nanairo
#include "surface_model.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Utility/unique_pointer.hpp"

// Forward declaration
class QJsonObject;

namespace nanairo {

// Forward declaration
template <uint> class WavelengthSamples;

//! \addtogroup Core
//! \{

/*!
  \details
  No detailed.
  */
class SmoothDielectricSurface : public SurfaceModel
{
 public:
  template <uint kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a smooth dielectric surface
  SmoothDielectricSurface(const QJsonObject& settings) noexcept;


  //! Make a Fresnel BRDF
  template <uint kSampleSize>
  ShaderPointer<kSampleSize> makeSpecularBsdf(
      const bool is_reverse_face,
      const WavelengthSamples<kSampleSize>& wavelengths,
      MemoryPool& memory_pool) const noexcept;

  //! Return the diffuse surface type
  SurfaceType type() const noexcept override;

 private:
  //! Initialize
  void initialize(const QJsonObject& settings) noexcept;


  SpectralDistribution eta_; //!< Interior exterior ratio of refractive index
};

//! \} Core

} // namespace nanairo

#include "smooth_dielectric_surface-inl.hpp"

#endif // NANAIRO_SMOOTH_DIELECTRIC_SURFACE_HPP

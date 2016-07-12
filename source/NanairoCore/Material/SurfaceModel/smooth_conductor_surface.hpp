/*!
  \file smooth_conductor_surface.hpp
  \author Sho Ikeda

  Copyright (c) 2015 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_SMOOTH_CONDUCTOR_SURFACE_HPP
#define NANAIRO_SMOOTH_CONDUCTOR_SURFACE_HPP

// Standard C++ library
#include <cstddef>
// Nanairo
#include "surface_model.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Utility/unique_pointer.hpp"

// Forward declaration
class QString;

namespace nanairo {

// Forward declaration
class SceneSettings;
template <uint> class WavelengthSamples;

//! \addtogroup Core
//! \{

/*!
  \details
  No detailed.
  */
class SmoothConductorSurface : public SurfaceModel 
{
 public:
  template <uint kSampleSize>
  using ShaderPointer = SurfaceModel::ShaderPointer<kSampleSize>;


  //! Create a smooth conductor surface
  SmoothConductorSurface(const SceneSettings& settings, 
                         const QString& prefix) noexcept;


  //! Make a Fresnel BRDF
  template <uint kSampleSize>
  ShaderPointer<kSampleSize> makeSpecularBrdf(
      const WavelengthSamples<kSampleSize>& wavelengths,
      MemoryPool& memory_pool) const noexcept;

  //! Return the surface model size
  std::size_t surfaceSize() const noexcept override;

  //! Return the smooth conductor surface type
  SurfaceType type() const noexcept override;

 private:
  //! Initialize
  void initialize(const SceneSettings& settings, const QString& prefix) noexcept;


//  SpectralDistribution eta_, //!< The ratio of refractive index
//                       eta_k_; //!< Refractive index absorption ratio
  SpectralDistribution reflectance_0deg_;
};

//! \} Core 

} // namespace nanairo

#include "smooth_conductor_surface-inl.hpp"

#endif // NANAIRO_SMOOTH_CONDUCTOR_SURFACE_HPP
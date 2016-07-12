/*!
  \file path_tracing.hpp
  \author Sho Ikeda

  Copyright (c) 2015 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_PATH_TRACING_HPP
#define NANAIRO_PATH_TRACING_HPP

// Standard C++ library
#include <functional>
// Nanairo
#include "rendering_method.hpp"
#include "NanairoCore/nanairo_core_config.hpp"

namespace nanairo {

// Forward declaration
class CameraModel;
class IntersectionInfo;
class Material;
class Ray;
class Sampler;
class SceneSettings;
class Scene;
template <uint> class ShaderModel;
class System;
template <typename> class UniquePointer;

//! \addtogroup Core 
//! \{

/*!
  \details
  No detailed.
  */
template <uint kSampleSize>
class PathTracing : public RenderingMethod<kSampleSize>
{
 public:
  using Method = RenderingMethod<kSampleSize>;
  using Spectra = typename Method::Spectra;
  using Wavelengths = typename Method::Wavelengths;
  using Shader = ShaderModel<kSampleSize>;
  using ShaderPointer = UniquePointer<Shader>;
  

  //! Initialize path tracing method
  PathTracing(const SceneSettings& settings) noexcept;


  //! Render scene using path tracing method
  void render(System& system, 
              Scene& scene, 
              const Wavelengths& sampled_wavelengths) noexcept override;

 private:
  //! Evaluate the explicit connection
  void evaluateExplicitConnection(const World& world,
                                  const Ray& ray,
                                  const ShaderPointer& bxdf,
                                  const IntersectionInfo& intersection,
                                  const Spectra& ray_weight,
                                  Sampler& sampler,
                                  MemoryPool& memory_pool,
                                  Spectra* contribution) const noexcept;

  //! Evaluate the implicit connection
  template <bool Mis>
  void evaluateImplicitConnection(const World& world,
                                  const Ray& ray,
                                  const Float inverse_direction_pdf,
                                  const IntersectionInfo& intersection,
                                  const Spectra& ray_weight,
                                  MemoryPool& memory_pool,
                                  Spectra* contribution) const noexcept;

  //! Generate a camera ray
  Ray generateRay(const CameraModel& camera,
                  const uint x,
                  const uint y,
                  Sampler& sampler,
                  MemoryPool& memory_pool,
                  Spectra* ray_weight,
                  Float* inverse_direction_pdf) const noexcept;

  //! Initialize
  void initialize(const SceneSettings& settings) noexcept;

  //! Calculate the MIS weight
  Float calcMisWeight(const Float pdf1, const Float inverse_pdf2) const noexcept;

  //! Parallelize path tracing
  void traceCameraPath(System& system, 
                       Scene& scene, 
                       const Wavelengths& sampled_wavelengths) noexcept;

  //! Trace the camera path
  void traceCameraPath(System& system,
                       Scene& scene,
                       const Wavelengths& sampled_wavelengths,
                       const int thread_id,
                       const uint x,
                       const uint y) noexcept;
};

//! \} Core

} // namespace nanairo

#include "path_tracing-inl.hpp"

#endif // NANAIRO_PATH_TRACING_HPP
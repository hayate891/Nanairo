/*!
  \file spectra_image_interface.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_SPECTRA_IMAGE_INTERFACE_HPP
#define NANAIRO_SPECTRA_IMAGE_INTERFACE_HPP

// Standard C++ library
#include <cstddef>
// Qt
#include <QtGlobal>
// Nanairo
#include "NanairoCore/nanairo_core_config.hpp"

// Forward declaration
class QString;

namespace nanairo {

// Forward declaration
class HdrImage;
template <uint> class SampledSpectra;
class System;

//! \addtogroup Core
//! \{

/*!
  \details
  No detailed.
  */
enum class SpectraImageType
{
  Spectra = 0,
  Rgb
};

/*!
  \details
  No detailed.
  */
class SpectraImageInterface
{
 public:
  //! Initialize the spectra image
  SpectraImageInterface(const uint width, const uint height) noexcept;

  //! Finalize the spectra image
  virtual ~SpectraImageInterface() noexcept;


  //! Add radiance from a sample
  template <uint kSampleSize>
  void addContribution(const uint x,
                       const uint y,
                       const SampledSpectra<kSampleSize>& contribution) noexcept;

  //! Clear the buffer value to 0
  virtual void clear() noexcept = 0;

  //! Return the height resolution
  uint heightResolution() const noexcept;

  //! Save spectra image
  virtual void save(const quint64 cycle, const QString& file_path) const noexcept = 0;

  //! Convert the spectra image to the HDR image
  virtual void toHdrImage(System& system,
                          const quint64 cycle, 
                          HdrImage* hdr_image) const noexcept = 0;

  //! Return the spectra image type
  virtual SpectraImageType type() const noexcept = 0;

  //! Return the width resolution
  uint widthResolution() const noexcept;

 private:
  uint width_,
       height_;
};

//! Add spectra contribution to image buffer
template <uint kSampleSize>
void addSpectraContribution(SpectraImageInterface* image,
                            const uint x,
                            const uint y,
                            const SampledSpectra<kSampleSize>& contribution) noexcept;

//! Add spectra contribution to image buffer
template <uint kSampleSize>
void addRgbContribution(SpectraImageInterface* image,
                        const uint x,
                        const uint y,
                        const SampledSpectra<kSampleSize>& contribution) noexcept;

//! \} Core

} // namespace nanairo

#include "spectra_image_interface-inl.hpp"

#endif // NANAIRO_SPECTRA_IMAGE_INTERFACE_HPP

/*!
  \file sampled_spectra-inl.hpp
  \author Sho Ikeda

  Copyright (c) 2015 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_SAMPLED_SPECTRA_INL_HPP
#define NANAIRO_SAMPLED_SPECTRA_INL_HPP

#include "sampled_spectra.hpp"
// Zisc
#include "zisc/arithmetic_array.hpp"
#include "zisc/math.hpp"
#include "zisc/utility.hpp"
// Nanairo
#include "sampled_wavelengths.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"
#include "NanairoCore/Data/wavelength_samples.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra() noexcept
{
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra(const Wavelengths& wavelengths) noexcept :
    wavelengths_{&wavelengths}
{
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra(const Wavelengths& wavelengths,
                                            const Float intensity) noexcept :
    wavelengths_{&wavelengths}
{
  intensities_.fill(intensity);
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize>::SampledSpectra(const Wavelengths& wavelengths,
                                            const Intensities& intensities) noexcept :
    intensities_{intensities},
    wavelengths_{&wavelengths}
{
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator+(const Float scalar) const noexcept
    -> SampledSpectra
{
  return *this + SampledSpectra{*wavelengths_, scalar};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator+(const SampledSpectra& samples) const noexcept
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_,  intensities_ + samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator-(const Float scalar) const noexcept
    -> SampledSpectra
{
  return *this - SampledSpectra{*wavelengths_, scalar};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator-(const SampledSpectra& samples) const noexcept
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ - samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator*(const Float scalar) const noexcept
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ * scalar};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator*(const SampledSpectra& samples) const noexcept
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ * samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator/(const SampledSpectra& samples) const noexcept
    -> SampledSpectra
{
  return SampledSpectra{*wavelengths_, intensities_ / samples.intensities_};
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator+=(const SampledSpectra& samples) noexcept
    -> SampledSpectra&
{
  intensities_ += samples.intensities_;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator-=(const SampledSpectra& samples) noexcept
    -> SampledSpectra&
{
  intensities_ -= samples.intensities_;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::operator*=(const SampledSpectra& samples) noexcept
    -> SampledSpectra&
{
  intensities_ *= samples.intensities_;
  return *this;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
Float SampledSpectra<kSampleSize>::average() const noexcept
{
  using zisc::cast;

  constexpr Float averager = 1.0 / cast<Float>(kSampleSize);
  return intensities_.sum() * averager;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
Float SampledSpectra<kSampleSize>::intensity(const uint index) const noexcept
{
  return intensities_[index];
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
bool SampledSpectra<kSampleSize>::isZero() const noexcept
{
  return intensities_.isZero();
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
Float SampledSpectra<kSampleSize>::max() const noexcept
{
  return intensities_.max();
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
uint16 SampledSpectra<kSampleSize>::wavelength(const uint index) const noexcept
{
  return (*wavelengths_)[index];
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto SampledSpectra<kSampleSize>::wavelengths() const noexcept -> const Wavelengths&
{
  return *wavelengths_;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
void SampledSpectra<kSampleSize>::setIntensity(const uint index, 
                                               const Float intensity) noexcept
{
  intensities_.set(index, intensity);
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize> operator*(const Float scalar, 
                                      const SampledSpectra<kSampleSize>& samples) noexcept
{
  return samples * scalar;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize> makeSampledSpectra(
    const SampledWavelengths<kSampleSize>& sampled_wavelengths) noexcept
{
  return SampledSpectra<kSampleSize>{sampled_wavelengths.wavelengths(),
                                     sampled_wavelengths.inverseProbabilities()};
}

/*!
  \details
  No detailed.
  */
//inline
//SampledSpectra sqrt(const SampledSpectra& samples)
//{
//  SampledSpectra spectra{samples.wavelengths()};
//  for (uint index = 0; index < kNumOfSpectraSamples; ++index)
//    spectra.setIntensity(index, zisc::sqrt(samples.intensity(index)));
//  return spectra;
//}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
SampledSpectra<kSampleSize> sample(const SpectralDistribution& distribution,
                                   const WavelengthSamples<kSampleSize>& wavelengths) noexcept
{
  IntensitySamples<kSampleSize> intensities;
  for (uint index = 0; index < kSampleSize; ++index)
    intensities.set(index, distribution.getByWavelength(wavelengths[index]));
  return SampledSpectra<kSampleSize>{wavelengths, intensities};
}

} // namespace nanairo

#endif // _NANAIRO_SAMPLED_SPECTRA_INL_HPP_
/*!
  \file russian_roulette.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_RUSSIAN_ROULETTE_HPP
#define NANAIRO_RUSSIAN_ROULETTE_HPP

// Zisc
#include "zisc/algorithm.hpp"
// Nanairo
#include "NanairoCore/nanairo_core_config.hpp"

// Forward declaration
class QJsonObject;

namespace nanairo {

// Forward declaration
template <uint> class SampledSpectra;
class Sampler;

//! \addtogroup Core
//! \{

/*!
  \details
  No detailed.
  */
class RouletteResult
{
 public:
  //! Create result
  RouletteResult() noexcept;

  //! Create result
  RouletteResult(const bool result, const Float probability) noexcept;


  //! Return the probability
  Float probability() const noexcept;

  //! Return the result
  bool result() const noexcept;

  //! Set probability
  void setProbability(const Float probability) noexcept;

  //! Set result
  void setResult(const bool result) noexcept;

 private:
  Float probability_;
  bool result_;
};

/*!
  */
class RussianRoulette
{
 public:
  //! Initialize
  RussianRoulette(const QJsonObject& settings) noexcept;

  //! Play russian roulette
  template <uint kSampleSize>
  RouletteResult operator()(const uint path,
                            const SampledSpectra<kSampleSize>& weight,
                            Sampler& sampler) const noexcept;


  //! Play russian roulette
  template <uint kSampleSize>
  RouletteResult play(const uint path,
                      const SampledSpectra<kSampleSize>& weight,
                      Sampler& sampler) const noexcept;

 private:
  /*!
    */
  enum class RouletteType : int
  {
    kAverage,
    kMax,
    kPath
  };


  //! Initialize
  void initialize(const QJsonObject& settings) noexcept;

  //! Play russian roulette
  template <uint kSampleSize>
  RouletteResult playWithAverage(const SampledSpectra<kSampleSize>& weight,
                                 Sampler& sampler) const noexcept;

  //! Play russian roulette
  template <uint kSampleSize>
  RouletteResult playWithMax(const SampledSpectra<kSampleSize>& weight,
                             Sampler& sampler) const noexcept;

  //! Play russian roulette
  RouletteResult playWithPath(const uint path) const noexcept;


  RouletteType type_;
  uint max_path_;
};

//! \} Core

} // namespace nanairo

#include "russian_roulette-inl.hpp"

#endif // NANAIRO_RUSSIAN_ROULETTE_HPP

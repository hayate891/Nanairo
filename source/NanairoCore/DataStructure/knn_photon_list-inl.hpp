/*!
  \file knn_photon_list-inl.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_KNN_PHOTON_LIST_INL_HPP
#define NANAIRO_KNN_PHOTON_LIST_INL_HPP

#include "knn_photon_list.hpp"
// Standard C++ library
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>
// Zisc
#include "zisc/error.hpp"
// Nanairo
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Data/photon_cache.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
KnnPhotonList<kSampleSize>::KnnPhotonList() noexcept
{
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
auto KnnPhotonList<kSampleSize>::operator[](const uint index) const noexcept
    -> const PhotonPoint&
{
  return photon_list_[index];
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
void KnnPhotonList<kSampleSize>::clear() noexcept
{
  photon_list_.clear();
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
void KnnPhotonList<kSampleSize>::insert(const Float distance2,
                                        const Cache* photon) noexcept
{
  auto compare = [](const PhotonPoint& a, const PhotonPoint& b)
  {
    return std::get<0>(a) < std::get<0>(b);
  };

  if (photon_list_.size() < k()) {
    photon_list_.emplace_back(distance2, photon);
    std::push_heap(photon_list_.begin(), photon_list_.end(), compare);
  }
  else if (distance2 < std::get<0>(photon_list_.front())) {
    std::pop_heap(photon_list_.begin(), photon_list_.end(), compare);
    photon_list_.back() = std::make_tuple(distance2, photon);
    std::push_heap(photon_list_.begin(), photon_list_.end(), compare);
  }
  ZISC_ASSERT(photon_list_.size() <= k(), "The size of knn list is greater than k.");
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
Float KnnPhotonList<kSampleSize>::inverseLongestDistance() const noexcept
{
  return zisc::invSqrt(std::get<0>(photon_list_.front()));
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
uint KnnPhotonList<kSampleSize>::k() const noexcept
{
  return k_;
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
void KnnPhotonList<kSampleSize>::setK(const uint k) noexcept
{
  ZISC_ASSERT(0 < k, "The k is zero.");
  clear();
  k_ = k;
  photon_list_.reserve(k);
}

/*!
  \details
  No detailed.
  */
template <uint kSampleSize> inline
uint KnnPhotonList<kSampleSize>::size() const noexcept
{
  return zisc::cast<uint>(photon_list_.size());
}

} // namespace nanairo

#endif // NANAIRO_KNN_PHOTON_LIST_INL_HPP

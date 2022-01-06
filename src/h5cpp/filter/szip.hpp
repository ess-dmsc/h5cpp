//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Authors:
//         Eugen Wintersberger <eugen.wintersberger@desy.de>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 20, 2020
//
#pragma once

#include <h5cpp/filter/filter.hpp>

namespace hdf5 {
namespace filter {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT SZip : public Filter
{
  public:
    //!
    //! @brief encoding method
    //!
    enum class OptionMask : unsigned int  {
      //! without coding
      None = 0u,
      //! allow K13 coding method
      AllowK13 = H5_SZIP_ALLOW_K13_OPTION_MASK,
      //! chip coding method
      Chip = H5_SZIP_CHIP_OPTION_MASK,
      //! entropy coding method
      EntropyCoding = H5_SZIP_EC_OPTION_MASK,
      //! nearest neighbor coding method
      NearestNeighbor = H5_SZIP_NN_OPTION_MASK,
    };
    //! option mask base type
    using OptionMaskBase = std::underlying_type<OptionMask>::type;

    //!
    //! \brief default constructor
    //!
    SZip();
    //!
    //! \brief constructor option mask and pixels per block
    //!
    SZip(OptionMask option_mask, unsigned int pixels_per_block);
    //!
    //! \brief constructor option mask and pixels per block
    //!
    SZip(OptionMaskBase option_mask, unsigned int pixels_per_block);
    ~SZip() override;

    //!
    //! \brief get the option mask
    //!
    OptionMaskBase option_mask() const noexcept;

    //!
    //! \brief set the option mask
    //!
    void option_mask(OptionMaskBase option_mask);

    //!
    //! \brief set the option mask
    //!
    void option_mask(OptionMask option_mask);

    //!
    //! \brief get pixels per block
    //!
    unsigned int pixels_per_block() const noexcept;

    //!
    //! \brief set pixels per block
    //!
    void pixels_per_block(unsigned int pixels_per_block);

    virtual void operator()(const property::DatasetCreationList &dcpl,
                            Availability flag=Availability::Mandatory) const override;
  private:
    SZip::OptionMaskBase option_mask_;
    unsigned int pixels_per_block_;
};

  DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const SZip::OptionMask &flags);

  DLL_EXPORT SZip::OptionMaskBase operator|(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT SZip::OptionMaskBase operator|(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT SZip::OptionMaskBase operator|(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs);

  DLL_EXPORT SZip::OptionMaskBase operator&(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT SZip::OptionMaskBase operator&(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT SZip::OptionMaskBase operator&(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs);

  DLL_EXPORT bool operator==(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT bool operator==(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT bool operator==(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs);

  DLL_EXPORT bool operator!=(const SZip::OptionMask &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT bool operator!=(const SZip::OptionMaskBase &lhs,const SZip::OptionMask &rhs);
  DLL_EXPORT bool operator!=(const SZip::OptionMask &lhs,const SZip::OptionMaskBase &rhs);

#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace filter
} // namespace hdf5

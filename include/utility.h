#ifndef GREGJM_Z80_UTILITY_H
#define GREGJM_Z80_UTILITY_H

#include "types.hpp"

namespace z80 {

auto zero_extend(UnsignedHalfWordT narrow) noexcept -> UnsignedWordT;

auto sign_extend(UnsignedHalfWordT narrow) noexcept -> UnsignedWordT;

} // namespace z80

#endif

#include "utility.h"

#include <byte_cast.hpp>

using namespace z80::literals;

auto z80::zero_extend(UnsignedHalfWordT narrow) noexcept -> UnsignedWordT {
	return sign_extend(narrow) & 0xff_uword;
}

auto z80::sign_extend(UnsignedHalfWordT narrow) noexcept -> UnsignedWordT {
	const auto signed_punned = byte_cast<HalfWordT>(narrow);
	const auto extended = static_cast<WordT>(signed_punned);
	const auto unsigned_punned = byte_cast<UnsignedWordT>(extended);

	return unsigned_punned;
}

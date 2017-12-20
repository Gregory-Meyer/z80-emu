#include "register_pair.h"

#include <iostream>

auto main() -> int {
	const auto reg = z80::RegisterPair{ z80::SignedRegister_t{ 4080 } };

	const auto as_unsigned = static_cast<z80::UnsignedRegister_t>(reg);
	const auto as_signed = static_cast<z80::SignedRegister_t>(reg);

	const auto upper_as_unsigned =
		static_cast<z80::UnsignedHalfRegister_t>(reg.upper());
	const auto upper_as_signed =
		static_cast<z80::SignedHalfRegister_t>(reg.upper());

	const auto lower_as_unsigned =
		static_cast<z80::UnsignedHalfRegister_t>(reg.lower());
	const auto lower_as_signed =
		static_cast<z80::SignedHalfRegister_t>(reg.lower());

	std::cout << as_unsigned << std::endl;
	std::cout << as_signed << std::endl;
	std::cout << int{ upper_as_unsigned } << std::endl;
	std::cout << int{ upper_as_signed } << std::endl;
	std::cout << int{ lower_as_unsigned } << std::endl;
	std::cout << int{ lower_as_signed } << std::endl;
}

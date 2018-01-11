#include "register_pair.h"

#include <iostream>

auto immutable_test() -> void {
	const auto reg = z80::RegisterPair{ z80::WordT{ 4080 } };

	const auto as_unsigned = static_cast<z80::UnsignedWordT>(reg);
	const auto as_signed = static_cast<z80::WordT>(reg);

	const auto upper_as_unsigned =
		static_cast<z80::UnsignedHalfWordT>(reg.upper());
	const auto upper_as_signed =
		static_cast<z80::HalfWordT>(reg.upper());

	const auto lower_as_unsigned =
		static_cast<z80::UnsignedHalfWordT>(reg.lower());
	const auto lower_as_signed =
		static_cast<z80::HalfWordT>(reg.lower());

	std::cout << as_unsigned << std::endl;
	std::cout << as_signed << std::endl;
	std::cout << int{ upper_as_unsigned } << std::endl;
	std::cout << int{ upper_as_signed } << std::endl;
	std::cout << int{ lower_as_unsigned } << std::endl;
	std::cout << int{ lower_as_signed } << std::endl;
}

auto mutable_test() -> void {
	auto reg = z80::RegisterPair{ z80::WordT{ 4080 } };

	reg.upper() = z80::HalfWordT{ -1 };

	const auto as_unsigned = static_cast<z80::UnsignedWordT>(reg);
	const auto as_signed = static_cast<z80::WordT>(reg);

	const auto upper_as_unsigned =
		static_cast<z80::UnsignedHalfWordT>(reg.upper());
	const auto upper_as_signed =
		static_cast<z80::HalfWordT>(reg.upper());

	const auto lower_as_unsigned =
		static_cast<z80::UnsignedHalfWordT>(reg.lower());
	const auto lower_as_signed =
		static_cast<z80::HalfWordT>(reg.lower());

	std::cout << as_unsigned << std::endl;
	std::cout << as_signed << std::endl;
	std::cout << int{ upper_as_unsigned } << std::endl;
	std::cout << int{ upper_as_signed } << std::endl;
	std::cout << int{ lower_as_unsigned } << std::endl;
	std::cout << int{ lower_as_signed } << std::endl;
}

auto main() -> int {
	immutable_test();
	mutable_test();
}

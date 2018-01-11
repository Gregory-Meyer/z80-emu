#include "types.hpp"

#include <iostream>

auto main() -> int {
	using namespace z80::literals;

	std::cout << -9223372036854775808_i64 << '\n';
	std::cout << 15_u8 << '\n';
}

#include "catch.hpp"

#include "memory_unit.h"

using namespace z80::literals;

SCENARIO("Basic MemoryUnit functionality", "[MemoryUnit]") {
	GIVEN("a default constructed MemoryUnit") {
		const auto mem = z80::MemoryUnit{ };

		THEN("its size is the default size and its elements are 0_uhalf") {
			CHECK(mem.size() == z80::MemoryUnit::DEFAULT_SIZE);

			for (z80::MemoryUnit::SizeT i = 0; i < mem.size(); ++i) {
				CHECK(mem.load(i) == 0_uhalf);
			}
		}
	}

	GIVEN("a MemoryUnit with size 16") {
		const auto mem = z80::MemoryUnit{ 16_uhalf };

		THEN("its size is 16") {
			CHECK(mem.size() == 16_uhalf);

			for (z80::MemoryUnit::SizeT i = 0; i < mem.size(); ++i) {
				CHECK(mem.load(i) == 0_uhalf);
			}
		}
	}
}

SCENARIO("MemoryUnit mutation", "[MemoryUnit]") {
	GIVEN("a default constructed MemoryUnit with some elements initialized") {
		auto mem = z80::MemoryUnit{ };

		for (z80::MemoryUnit::SizeT i = 0; i < 30; ++i) {
			mem.store(i, 1_uhalf);
		}

		THEN("only those elements are initialized") {
			CHECK(mem.size() == z80::MemoryUnit::DEFAULT_SIZE);

			for (z80::MemoryUnit::SizeT i = 0; i < mem.size(); ++i) {
				if (i < 30) {
					CHECK(mem.load(i) == 1_uhalf);
				} else {
					CHECK(mem.load(i) == 0_uhalf);
				}
			}
		}
	}

	GIVEN("a MemoryUnit of size 16 with some elements initialized") {
		auto mem = z80::MemoryUnit{ 16 };

		for (z80::MemoryUnit::SizeT i = 0; i < 8; ++i) {
			mem.store(i, 1_uhalf);
		}

		THEN("only those elements are initialized") {
			CHECK(mem.size() == 16);

			for (z80::MemoryUnit::SizeT i = 0; i < mem.size(); ++i) {
				if (i < 8) {
					CHECK(mem.load(i) == 1_uhalf);
				} else {
					CHECK(mem.load(i) == 0_uhalf);
				}
			}
		}
	}
}

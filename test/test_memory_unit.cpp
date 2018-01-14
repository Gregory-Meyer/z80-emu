#include "catch.hpp"

#include "memory_unit.h"

#include <numeric>

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

SCENARIO("MutableAddress semantics", "[MutableAddress]") {
	GIVEN("a MemoryUnit and some MutableAddresses") {
		auto mem = z80::MemoryUnit{ 32 };
		mem.store(3, 1_uhalf);
		mem.store(7, 1_uhalf);

		auto addr1 = mem.make_address(0);
		auto addr2 = mem.make_address(3);
		auto addr3 = mem.make_address(7);

		THEN("they evaluate true") {
			CHECK(static_cast<bool>(addr1));
			CHECK(static_cast<bool>(addr2));
			CHECK(static_cast<bool>(addr3));
		}

		THEN("they compare as expected") {
			CHECK_FALSE(addr1 == addr2);
			CHECK(addr1 != addr2);
			CHECK(addr1 < addr2);
			CHECK(addr1 <= addr2);
			CHECK_FALSE(addr1 > addr2);
			CHECK_FALSE(addr1 >= addr2);

			CHECK_FALSE(addr1 == addr3);
			CHECK(addr1 != addr3);
			CHECK(addr1 < addr3);
			CHECK(addr1 <= addr3);
			CHECK_FALSE(addr1 > addr3);
			CHECK_FALSE(addr1 >= addr3);

			CHECK_FALSE(addr2 == addr3);
			CHECK(addr2 != addr3);
			CHECK(addr2 < addr3);
			CHECK(addr2 <= addr3);
			CHECK_FALSE(addr2 > addr3);
			CHECK_FALSE(addr2 >= addr3);
		}

		THEN("their values correspond") {
			CHECK(*addr1 == 0_uhalf);
			CHECK(*addr2 == 1_uhalf);
			CHECK(*addr3 == 1_uhalf);

			CHECK(mem.load(0) == 0_uhalf);
			CHECK(mem.load(3) == 1_uhalf);
			CHECK(mem.load(7) == 1_uhalf);
		}

		AND_WHEN("one is modified, the memory is changed as well") {
			*addr1 = 2_uhalf;

			CHECK(*addr1 == 2_uhalf);
			CHECK(*addr2 == 1_uhalf);
			CHECK(*addr3 == 1_uhalf);

			CHECK(mem.load(0) == 2_uhalf);
			CHECK(mem.load(3) == 1_uhalf);
			CHECK(mem.load(7) == 1_uhalf);
		}
	}
}

SCENARIO("MutableSlice semantics", "[MutableSlice]") {
	GIVEN("a MemoryUnit and some MutableSlices") {
		auto mem = z80::MemoryUnit{ 32 };

		auto arr = mem.make_slice(3, 8);

		CHECK(arr.size() == 5);
		CHECK_FALSE(arr.empty());

		THEN("when modified, the underling memory is modified") {
			std::iota(arr.begin(), arr.end(), 1);

			auto i = 1_u8;

			for (const auto val : arr) {
				CHECK(val == i);
				++i;
			}

			CHECK(arr.front() == mem.load(3));
			CHECK(arr.back() == mem.load(7));

			for (z80::UnsignedWordT i = 0; i < arr.size(); ++i) {
				CHECK(arr[i]
				      == mem.load(static_cast<z80::MemoryUnit::SizeT>(i + 3)));
			}
		}

		THEN("when indexed out of range, an exception is thrown") {
			CHECK_THROWS(arr.at(-1));
			CHECK_NOTHROW(arr.at(0));
			CHECK_NOTHROW(arr.at(4));
			CHECK_THROWS(arr.at(5));
		}
	}
}

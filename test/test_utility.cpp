#include "catch.hpp"

#include "types.hpp"
#include "utility.h"

using namespace z80::literals;

SCENARIO("sign extending integral numbers", "[sign_extend]") {
	GIVEN("a few non-negative integral numbers") {
		const auto x = 0b00000000_uhalf;
		const auto y = 0b00000001_uhalf;
		const auto z = 0b00000010_uhalf;

		const auto a = 0b00000011_uhalf;
		const auto b = 0b00000111_uhalf;
		const auto c = 0b00001111_uhalf;

		const auto f = 0b01111101_uhalf;
		const auto g = 0b01111110_uhalf;
		const auto h = 0b01111111_uhalf;


		THEN("the integral numbers retain their value upon sign extension") {
			CHECK(x == z80::sign_extend(x));
			CHECK(y == z80::sign_extend(y));
			CHECK(z == z80::sign_extend(z));

			CHECK(a == z80::sign_extend(a));
			CHECK(b == z80::sign_extend(b));
			CHECK(c == z80::sign_extend(c));

			CHECK(f == z80::sign_extend(f));
			CHECK(g == z80::sign_extend(g));
			CHECK(h == z80::sign_extend(h));
		}
	}

	GIVEN("a few negative integral numbers") {
		const auto x = 0b11111111_uhalf;
		const auto y = 0b11111110_uhalf;
		const auto z = 0b11111101_uhalf;

		const auto a = 0b11111001_uhalf;
		const auto b = 0b11110001_uhalf;
		const auto c = 0b11100001_uhalf;

		const auto f = 0b10000010_uhalf;
		const auto g = 0b10000001_uhalf;
		const auto h = 0b10000000_uhalf;

		THEN("the integral numbers have their leading ones extended") {
			CHECK(x != z80::sign_extend(x));
			CHECK(z80::sign_extend(x) == 0b1111111111111111_uword);
			CHECK(y != z80::sign_extend(y));
			CHECK(z80::sign_extend(y) == 0b1111111111111110_uword);
			CHECK(z != z80::sign_extend(z));
			CHECK(z80::sign_extend(z) == 0b1111111111111101_uword);

			CHECK(a != z80::sign_extend(a));
			CHECK(z80::sign_extend(a) == 0b1111111111111001_uword);
			CHECK(b != z80::sign_extend(b));
			CHECK(z80::sign_extend(b) == 0b1111111111110001_uword);
			CHECK(c != z80::sign_extend(c));
			CHECK(z80::sign_extend(c) == 0b1111111111100001_uword);

			CHECK(f != z80::sign_extend(f));
			CHECK(z80::sign_extend(f) == 0b1111111110000010_uword);
			CHECK(g != z80::sign_extend(g));
			CHECK(z80::sign_extend(g) == 0b1111111110000001_uword);
			CHECK(h != z80::sign_extend(h));
			CHECK(z80::sign_extend(h) == 0b1111111110000000_uword);
		}
	}
}

SCENARIO("zero extending integral numbers", "[zero_extend]") {
	GIVEN("a few non-negative integral numbers") {
		const auto x = 0b00000000_uhalf;
		const auto y = 0b00000001_uhalf;
		const auto z = 0b00000010_uhalf;

		const auto a = 0b00000011_uhalf;
		const auto b = 0b00000111_uhalf;
		const auto c = 0b00001111_uhalf;

		const auto f = 0b01111101_uhalf;
		const auto g = 0b01111110_uhalf;
		const auto h = 0b01111111_uhalf;


		THEN("the integral numbers retain their value upon zero extension") {
			CHECK(x == z80::zero_extend(x));
			CHECK(y == z80::zero_extend(y));
			CHECK(z == z80::zero_extend(z));

			CHECK(a == z80::zero_extend(a));
			CHECK(b == z80::zero_extend(b));
			CHECK(c == z80::zero_extend(c));

			CHECK(f == z80::zero_extend(f));
			CHECK(g == z80::zero_extend(g));
			CHECK(h == z80::zero_extend(h));
		}
	}

	GIVEN("a few negative integral numbers") {
		const auto x = 0b11111111_uhalf;
		const auto y = 0b11111110_uhalf;
		const auto z = 0b11111101_uhalf;

		const auto a = 0b11111001_uhalf;
		const auto b = 0b11110001_uhalf;
		const auto c = 0b11100001_uhalf;

		const auto f = 0b10000010_uhalf;
		const auto g = 0b10000001_uhalf;
		const auto h = 0b10000000_uhalf;

		THEN("the integral numbers are not modified") {
			CHECK(x == z80::zero_extend(x));
			CHECK(z80::zero_extend(x) == 0b0000000011111111_uword);
			CHECK(y == z80::zero_extend(y));
			CHECK(z80::zero_extend(y) == 0b0000000011111110_uword);
			CHECK(z == z80::zero_extend(z));
			CHECK(z80::zero_extend(z) == 0b0000000011111101_uword);

			CHECK(a == z80::zero_extend(a));
			CHECK(z80::zero_extend(a) == 0b0000000011111001_uword);
			CHECK(b == z80::zero_extend(b));
			CHECK(z80::zero_extend(b) == 0b0000000011110001_uword);
			CHECK(c == z80::zero_extend(c));
			CHECK(z80::zero_extend(c) == 0b0000000011100001_uword);

			CHECK(f == z80::zero_extend(f));
			CHECK(z80::zero_extend(f) == 0b0000000010000010_uword);
			CHECK(g == z80::zero_extend(g));
			CHECK(z80::zero_extend(g) == 0b0000000010000001_uword);
			CHECK(h == z80::zero_extend(h));
			CHECK(z80::zero_extend(h) == 0b0000000010000000_uword);
		}
	}
}

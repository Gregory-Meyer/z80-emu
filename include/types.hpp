#ifndef GREGJM_Z80_TYPES_HPP
#define GREGJM_Z80_TYPES_HPP

#include <cstdint>
#include <cstddef>

namespace z80 {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using usize = std::size_t;
using isize = std::ptrdiff_t;

using WordT = i16;
using HalfWordT = i8;
using UnsignedWordT = u16;
using UnsignedHalfWordT = u8;

using MathWordT = u32;

namespace literals {

constexpr auto operator""_u8(const unsigned long long value) noexcept -> u8 {
	return static_cast<u8>(value);
}

constexpr auto operator""_u16(const unsigned long long value) noexcept -> u16 {
	return static_cast<u16>(value);
}

constexpr auto operator""_u32(const unsigned long long value) noexcept -> u32 {
	return static_cast<u32>(value);
}

constexpr auto operator""_u64(const unsigned long long value) noexcept -> u64 {
	return static_cast<u64>(value);
}

constexpr auto operator""_i8(const unsigned long long value) noexcept -> i8
{
	return static_cast<i8>(value);
}

constexpr auto operator""_i16(const unsigned long long value) noexcept -> i16 {
	return static_cast<i16>(value);
}

constexpr auto operator""_i32(const unsigned long long value) noexcept -> i32  {
	return static_cast<i32>(value);
}

constexpr auto operator""_i64(const unsigned long long value) noexcept -> i64 {
	return static_cast<i64>(value);
}

constexpr auto operator""_usize(const unsigned long long value) noexcept -> usize {
	return static_cast<usize>(value);
}

constexpr auto operator""_isize(const unsigned long long value) noexcept -> isize {
	return static_cast<isize>(value);
}

constexpr auto operator""_iword(
	const unsigned long long value
) noexcept -> WordT {
	return static_cast<WordT>(value);
}

constexpr auto operator""_ihalf(
	const unsigned long long value
) noexcept -> HalfWordT {
	return static_cast<HalfWordT>(value);
}

constexpr auto operator""_uword(
	const unsigned long long value
) noexcept -> UnsignedWordT {
	return static_cast<UnsignedWordT>(value);
}

constexpr auto operator""_uhalf(
	const unsigned long long value
) noexcept -> UnsignedHalfWordT {
	return static_cast<UnsignedHalfWordT>(value);
}

//constexpr auto operator""_b(const unsigned long long value) noexcept
//	-> std::byte
//{
//	return static_cast<std::byte>(value);
//}

} // namespace literals
} // namespace z80

#endif

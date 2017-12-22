// some fun literals

#ifndef GREGJM_Z80_LITERALS_HPP
#define GREGJM_Z80_LITERALS_HPP

#include <cstdint>

namespace z80 {
namespace literals {

constexpr auto operator""_u8(const unsigned long long value) noexcept
	-> std::uint8_t
{
	return static_cast<std::uint8_t>(value);
}

constexpr auto operator""_i8(const unsigned long long value) noexcept
	-> std::int8_t
{
	return static_cast<std::int8_t>(value);
}

constexpr auto operator""_u16(const unsigned long long value) noexcept
	-> std::uint16_t
{
	return static_cast<std::uint16_t>(value);
}

constexpr auto operator""_i16(const unsigned long long value) noexcept
	-> std::int16_t
{
	return static_cast<std::int16_t>(value);
}

constexpr auto operator""_u32(const unsigned long long value) noexcept
	-> std::uint32_t
{
	return static_cast<std::uint32_t>(value);
}

constexpr auto operator""_i32(const unsigned long long value) noexcept
	-> std::int32_t
{
	return static_cast<std::int32_t>(value);
}

constexpr auto operator""_u64(const unsigned long long value) noexcept
	-> std::uint64_t
{
	return static_cast<std::uint64_t>(value);
}

constexpr auto operator""_i64(const unsigned long long value) noexcept
	-> std::int64_t
{
	return static_cast<std::int64_t>(value);
}

} // namespace literals
} // namespace z80

#endif

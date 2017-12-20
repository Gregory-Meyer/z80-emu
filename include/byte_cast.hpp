#ifndef GREGJM_Z80_BYTE_CAST_HPP
#define GREGJM_Z80_BYTE_CAST_HPP

#include <type_traits>

namespace z80 {

template <typename T, typename U>
constexpr auto same_size_align() noexcept -> bool {
	return sizeof(T) == sizeof(U) and alignof(T) == alignof(U);
}

template <typename T, typename U,
		  typename = std::enable_if_t<same_size_align<T, U>()>>
constexpr auto byte_cast(U &value) noexcept -> T& {
	return *reinterpret_cast<T*>(&value);
}

template <typename T, typename U,
		  typename = std::enable_if_t<same_size_align<T, U>()>>
constexpr auto byte_cast(const U &value) noexcept -> const T& {
	return *reinterpret_cast<const T*>(&value);
}

} // namespace z80

#endif

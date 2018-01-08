#ifndef GREGJM_Z80_MEMORY_UNIT_H
#define GREGJM_Z80_MEMORY_UNIT_H

#include "register_pair.h"

#include <cstddef>
#include <vector>

namespace z80 {

// abstract class handling memory operations on the z80
// the z80 has 16 bits of byte-addressable address space
class MemoryUnit {
public:
	using Value_t = std::byte;
	using Size_t = UnsignedRegister_t;
	using Difference_t = SignedRegister_t;

	// pointer-like type
	// does not have pointer arithmetic
	class Address {
	public:
		Address(MemoryUnit &memory, const Size_t address) noexcept;

		auto operator=(const std::nullptr_t) -> Address&;

		auto operator*() const -> Value_t&;

		friend auto operator==(const Address lhs,
		                       const Address rhs) noexcept -> bool;

		friend auto operator!=(const Address lhs,
		                       const Address rhs) noexcept -> bool;

		friend auto operator<(const Address lhs,
		                      const Address rhs) noexcept -> bool;

		friend auto operator<=(const Address lhs,
		                       const Address rhs) noexcept -> bool;

		friend auto operator>(const Address lhs,
		                      const Address rhs) noexcept -> bool;

		friend auto operator>=(const Address lhs,
		                       const Address rhs) noexcept -> bool;

	private:
		MemoryUnit *memory_ = nullptr;
		Size_t address_ = 0;
	};

	// slice of memory; an address and a size, in essence
	// does not own its memory
	class Slice {
	public:
		Slice(MemoryUnit &memory, const Size_t start,
		      const Size_t size) noexcept;

		auto operator[](const Size_t index) const noexcept -> Value_t&;

		auto at(const Size_t index) const -> Value_t&;

		auto front() const noexcept -> Value_t&;

		auto back() const noexcept -> Value_t&;

		auto empty() const noexcept -> bool;

		auto size() const noexcept -> Size_t;

		auto max_size() const noexcept -> Size_t;

		auto fill() const noexcept -> void;

		auto swap(Slice &other) noexcept -> void;

	private:
		MemoryUnit *memory_ = nullptr;
		Size_t address_ = 0;
		Size_t size_ = 0;
	};

	auto address_of(Value_t &data);

private:
};

auto operator==(const Address lhs, const Address rhs) noexcept -> bool;

auto operator!=(const Address lhs, const Address rhs) noexcept -> bool;

auto operator<(const Address lhs, const Address rhs) noexcept -> bool;

auto operator<=(const Address lhs, const Address rhs) noexcept -> bool;

auto operator>(const Address lhs, const Address rhs) noexcept -> bool;

auto operator>=(const Address lhs, const Address rhs) noexcept -> bool;

} // namespace z80

#endif

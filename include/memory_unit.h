#ifndef GREGJM_Z80_MEMORY_UNIT_H
#define GREGJM_Z80_MEMORY_UNIT_H

#include "exceptions.h"
#include "register_pair.h"
#include "types.hpp"

#include <cstddef>
#include <vector>

namespace z80 {

// abstract class handling memory operations on the z80
// the z80 has 16 bits of byte-addressable address space
class MemoryUnit {
public:
	using ValueT = u8;
	using SizeT = UnsignedWordT;
	using DifferenceT = WordT;

	// immutable reference into a MemoryUnit
	class Address;

	// mutable reference into a MemoryUnit
	class MutableAddress;

	// immutable reference to a contiguous slice of memory in a MemoryUnit
	class Slice;

	// mutable reference to a contiguous slice of memory in a MemoryUnit
	class MutableSlice;

	constexpr auto DEFAULT_SIZE = static_cast<usize>(1 << 16);

	MemoryUnit() = default;

	explicit MemoryUnit(SizeT size);

//	// returns a MutableAddress object corresponding to the passed value
//	// will throw NonmemberException if the value is not
//	// owned by this MemoryUnit
//	auto address_of(ValueT &value) -> MutableAddress;
//
//	// returns an Address object corresponding to the passed value
//	// will throw NonmemberException if the value is not
//	// owned by this MemoryUnit
//	auto address_of(const ValueT &value) const -> Address;

	// returns a MutableAddress referring to the specified address
	// in this MemoryUnit
	// throws OutOfBoundsException if address >= size()
	auto make_address(SizeT address) -> MutableAddress;

	// returns an Address referring to the specified address
	// in this MemoryUnit
	// throws OutOfBoundsException if address >= size()
	auto make_address(SizeT address) const -> Address;

	// returns a MutableSlice referring to the slice of memory with
	// specified bounds [lower, upper)
	// throws OutOfBoundsException if lower > upper or upper > size()
	auto make_slice(SizeT lower, SizeT upper) -> MutableSlice;

	// returns a Slice referring to the slice of memory with
	// specified bounds [lower, upper)
	// throws OutOfBoundsException if lower > upper or upper > size()
	auto make_slice(SizeT lower, SizeT upper) const -> Slice;

	// returns the byte at the given address by value
	// throws OutOfBoundsException if address >= size()
	auto load(SizeT address) const -> ValueT;

	// writes to the given address
	// throws OutOfBoundsException if address >= size()
	auto store(SizeT address, ValueT data) -> void;

	// returns the number of bytes in this MemoryUnit
	auto size() const noexcept -> SizeT;

private:
	auto data() noexcept -> ValueT*;

	auto data() const noexcept -> const ValueT*;

//	auto is_member(const ValueT &value) const noexcept -> bool;

	std::vector<ValueT> data_ = std::vector<ValueT>(DEFAULT_SIZE, 0);
};

class MemoryUnit::Address {
public:
	friend MemoryUnit;

private:
	explicit Address(const MemoryUnit &parent) noexcept;

	Address(const MemoryUnit &parent, SizeT address) noexcept;

	const MemoryUnit *parent_ = nullptr;
	SizeT address_ = 0;
};

class MemoryUnit::MutableAddress {
public:
	friend MemoryUnit;

private:
	explicit MutableAddress(MemoryUnit &parent) noexcept;

	MutableAddress(MemoryUnit &parent, SizeT address) noexcept;

	MemoryUnit *parent_ = nullptr;
	SizeT address_ = 0;
};

class MemoryUnit::Slice {
public:
	friend MemoryUnit;

private:
	explicit Slice(const MemoryUnit &parent) noexcept;

	Slice(const MemoryUnit &parent, SizeT lower, SizeT upper) noexcept;

	const MemoryUnit *parent_ = nullptr;
	SizeT begin_ = 0;
	SizeT end_ = 0;
};

class MemoryUnit::MutableSlice {
public:
	friend MemoryUnit;

private:
	explicit MutableSlice(MemoryUnit &parent) noexcept;

	MutableSlice(MemoryUnit &parent, SizeT lower, SizeT upper) noexcept;

	MemoryUnit *parent_ = nullptr;
	SizeT begin_ = 0;
	SizeT end_ = 0;
};

} // namespace z80

#endif

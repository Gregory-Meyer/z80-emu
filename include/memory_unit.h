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

	static constexpr auto DEFAULT_SIZE = static_cast<usize>(1 << 16);

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
	auto operator[](SizeT address) noexcept -> ValueT&;

	auto operator[](SizeT address) const noexcept -> const ValueT&;

	auto at(SizeT address) -> ValueT&;

	auto at(SizeT address) const -> const ValueT&;

	auto data() noexcept -> ValueT*;

	auto data() const noexcept -> const ValueT*;

//	auto is_member(const ValueT &value) const noexcept -> bool;

	std::vector<ValueT> data_ = std::vector<ValueT>(DEFAULT_SIZE, 0);
};

class MemoryUnit::Address {
public:
	friend MemoryUnit;

	Address(MemoryUnit::MutableAddress mut_addr) noexcept;

	auto swap(Address &other) noexcept -> void;

	auto operator*() const noexcept -> const ValueT&;

	auto operator->() const noexcept -> const ValueT*;

	explicit operator bool() const noexcept;

	friend auto operator==(MemoryUnit::Address lhs,
	                       MemoryUnit::Address rhs) noexcept -> bool;

	friend auto operator!=(MemoryUnit::Address lhs,
	                       MemoryUnit::Address rhs) noexcept -> bool;

	friend auto operator<(MemoryUnit::Address lhs,
	                      MemoryUnit::Address rhs) noexcept -> bool;

	friend auto operator<=(MemoryUnit::Address lhs,
	                       MemoryUnit::Address rhs) noexcept -> bool;

	friend auto operator>(MemoryUnit::Address lhs,
	                      MemoryUnit::Address rhs) noexcept -> bool;

	friend auto operator>=(MemoryUnit::Address lhs,
	                       MemoryUnit::Address rhs) noexcept -> bool;

private:
	Address(const MemoryUnit &parent, SizeT address) noexcept;

	const MemoryUnit *parent_ = nullptr;
	SizeT address_;
};

class MemoryUnit::MutableAddress {
public:
	friend Address;
	friend MemoryUnit;

	auto swap(MutableAddress &other) noexcept -> void;

	auto operator*() const noexcept -> ValueT&;

	auto operator->() const noexcept -> ValueT*;

	explicit operator bool() const noexcept;

	friend auto operator==(MemoryUnit::MutableAddress lhs,
	                       MemoryUnit::MutableAddress rhs) noexcept -> bool;

	friend auto operator!=(MemoryUnit::MutableAddress lhs,
	                       MemoryUnit::MutableAddress rhs) noexcept -> bool;

	friend auto operator<(MemoryUnit::MutableAddress lhs,
	                      MemoryUnit::MutableAddress rhs) noexcept -> bool;

	friend auto operator<=(MemoryUnit::MutableAddress lhs,
	                       MemoryUnit::MutableAddress rhs) noexcept -> bool;

	friend auto operator>(MemoryUnit::MutableAddress lhs,
	                      MemoryUnit::MutableAddress rhs) noexcept -> bool;

	friend auto operator>=(MemoryUnit::MutableAddress lhs,
	                       MemoryUnit::MutableAddress rhs) noexcept -> bool;

private:
	MutableAddress(MemoryUnit &parent, SizeT address) noexcept;

	MemoryUnit *parent_ = nullptr;
	SizeT address_;
};

class MemoryUnit::Slice {
public:
	friend MemoryUnit;

private:
	Slice(const MemoryUnit &parent, SizeT lower, SizeT upper) noexcept;

	const MemoryUnit *parent_ = nullptr;
	SizeT begin_;
	SizeT end_;
};

class MemoryUnit::MutableSlice {
public:
	friend MemoryUnit;

private:
	MutableSlice(MemoryUnit &parent, SizeT lower, SizeT upper) noexcept;

	MemoryUnit *parent_ = nullptr;
	SizeT begin_;
	SizeT end_;
};

auto swap(MemoryUnit::Address &lhs, MemoryUnit::Address &rhs) noexcept -> void;

auto swap(MemoryUnit::MutableAddress &lhs,
          MemoryUnit::MutableAddress &rhs) noexcept -> void;

auto operator==(MemoryUnit::Address lhs,
                MemoryUnit::Address rhs) noexcept -> bool;

auto operator!=(MemoryUnit::Address lhs,
                MemoryUnit::Address rhs) noexcept -> bool;

auto operator<(MemoryUnit::Address lhs,
               MemoryUnit::Address rhs) noexcept -> bool;

auto operator<=(MemoryUnit::Address lhs,
                MemoryUnit::Address rhs) noexcept -> bool;

auto operator>(MemoryUnit::Address lhs,
               MemoryUnit::Address rhs) noexcept -> bool;

auto operator>=(MemoryUnit::Address lhs,
                MemoryUnit::Address rhs) noexcept -> bool;

auto operator==(MemoryUnit::MutableAddress lhs,
                MemoryUnit::MutableAddress rhs) noexcept -> bool;

auto operator!=(MemoryUnit::MutableAddress lhs,
                MemoryUnit::MutableAddress rhs) noexcept -> bool;

auto operator<(MemoryUnit::MutableAddress lhs,
               MemoryUnit::MutableAddress rhs) noexcept -> bool;

auto operator<=(MemoryUnit::MutableAddress lhs,
                MemoryUnit::MutableAddress rhs) noexcept -> bool;

auto operator>(MemoryUnit::MutableAddress lhs,
               MemoryUnit::MutableAddress rhs) noexcept -> bool;

auto operator>=(MemoryUnit::MutableAddress lhs,
                MemoryUnit::MutableAddress rhs) noexcept -> bool;


} // namespace z80

#endif

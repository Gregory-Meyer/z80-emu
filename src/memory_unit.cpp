#include "memory_unit.h"

using namespace z80::literals;

z80::MemoryUnit::MemoryUnit(SizeT size) : data_(size, 0) { }

//auto z80::MemoryUnit::address_of(const ValueT &value) const -> Address {
//	if (not is_member(value)) {
//		throw NonmemberException{ "MemoryUnit::address_of(const ValueT&) const" };
//	}
//
//	return { *this, static_cast<SizeT>(data() - &value) };
//}
//
//auto z80::MemoryUnit::address_of(ValueT &value) -> MutableAddress {
//	if (not is_member(value)) {
//		throw NonmemberException{ "MemoryUnit::address_of(ValueT&)" };
//	}
//
//	return { *this, static_cast<SizeT>(data() - &value) };
//}

auto z80::MemoryUnit::make_address(const SizeT address) -> MutableAddress {
	if (address > size()) {
		throw OutOfBoundsException{ "MemoryUnit::make_address" };
	}

	return { *this, address };
}

auto z80::MemoryUnit::make_address(const SizeT address) const -> Address {
	if (address > size()) {
		throw OutOfBoundsException{ "MemoryUnit::make_address const" };
	}

	return { *this, address };
}

auto z80::MemoryUnit::make_slice(const SizeT lower,
                                 const SizeT upper) -> MutableSlice {
	if (lower > upper or upper > size()) {
		throw OutOfBoundsException{ "MemoryUnit::make_slice" };
	}

	return { *this, lower, upper };
}

auto z80::MemoryUnit::make_slice(const SizeT lower,
                                 const SizeT upper) const -> Slice {
	if (lower > upper or upper > size()) {
		throw OutOfBoundsException{ "MemoryUnit::make_slice const" };
	}

	return { *this, lower, upper };
}

auto z80::MemoryUnit::load(SizeT address) const -> ValueT {
	if (address >= size()) {
		throw OutOfBoundsException{ "MemoryUnit::load" };
	}

	return data_[address];
}

auto z80::MemoryUnit::store(SizeT address, ValueT data) -> void {
	if (address >= size()) {
		throw OutOfBoundsException{ "MemoryUnit::store" };
	}

	data_[address] = data;
}

auto z80::MemoryUnit::size() const noexcept -> SizeT {
	return static_cast<SizeT>(data_.size());
}

auto z80::MemoryUnit::data() noexcept -> ValueT* {
	return data_.data();
}

auto z80::MemoryUnit::data() const noexcept -> const ValueT* {
	return data_.data();
}

//auto z80::MemoryUnit::is_member(
//	const MemoryUnit::ValueT &value
//) const noexcept -> bool {
//	const auto address = &value;
//
//	return address >= data() and address <= data() + size();
//}

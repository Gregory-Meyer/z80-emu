#include "memory_unit.h"

#include <algorithm>
#include <memory>

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

auto z80::MemoryUnit::operator[](const SizeT address) noexcept -> ValueT& {
	return data_[address];
}

auto z80::MemoryUnit::operator[](
	const SizeT address
) const noexcept -> const ValueT& {
	return data_[address];
}

auto z80::MemoryUnit::at(const SizeT address) -> ValueT& {
	if (address >= size()) {
		throw OutOfBoundsException{ "MemoryUnit::at" };
	}

	return (*this)[address];
}

auto z80::MemoryUnit::at(const SizeT address) const -> const ValueT& {
	if (address >= size()) {
		throw OutOfBoundsException{ "MemoryUnit::at" };
	}

	return (*this)[address];
}

//auto z80::MemoryUnit::is_member(
//	const MemoryUnit::ValueT &value
//) const noexcept -> bool {
//	const auto address = &value;
//
//	return address >= data() and address <= data() + size();
//}

z80::MemoryUnit::Address::Address(
	const MemoryUnit::MutableAddress mut_addr
) noexcept : parent_{ mut_addr.parent_ }, address_{ mut_addr.address_ } { }

auto z80::MemoryUnit::Address::swap(Address &other) noexcept -> void {
	using std::swap;

	swap(parent_, other.parent_);
	swap(address_, other.address_);
}

auto z80::MemoryUnit::Address::operator*() const noexcept -> const ValueT& {
	return (*parent_)[address_];
}

auto z80::MemoryUnit::Address::operator->() const noexcept -> const ValueT* {
	return std::addressof((*parent_)[address_]);
}

z80::MemoryUnit::Address::operator bool() const noexcept {
	return static_cast<bool>(parent_);
}

z80::MemoryUnit::Address::Address(const MemoryUnit &parent,
                                  SizeT address) noexcept
	: parent_{ &parent },
	  address_{ address }
{ }

auto z80::MemoryUnit::MutableAddress::swap(
	z80::MemoryUnit::MutableAddress &other
) noexcept -> void {
	using std::swap;

	swap(parent_, other.parent_);
	swap(address_, other.address_);
}

auto z80::MemoryUnit::MutableAddress::operator*() const noexcept -> ValueT& {
	return (*parent_)[address_];
}

auto z80::MemoryUnit::MutableAddress::operator->() const noexcept -> ValueT* {
	return std::addressof((*parent_)[address_]);
}

z80::MemoryUnit::MutableAddress::operator bool() const noexcept {
	return static_cast<bool>(parent_);
}

z80::MemoryUnit::MutableAddress::MutableAddress(MemoryUnit &parent,
                                                SizeT address) noexcept
	: parent_{ &parent }, address_{ address }
{ }

auto z80::swap(MemoryUnit::Address &lhs,
               MemoryUnit::Address &rhs) noexcept -> void {
	lhs.swap(rhs);
}

auto z80::operator==(const MemoryUnit::Address lhs,
                     const MemoryUnit::Address rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ == rhs.address_);
}

auto z80::operator!=(const MemoryUnit::Address lhs,
                     const MemoryUnit::Address rhs) noexcept -> bool {
	return (lhs.parent_ != rhs.parent_) or (lhs.address_ != rhs.address_);
}

auto z80::operator<(const MemoryUnit::Address lhs,
                    const MemoryUnit::Address rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ < rhs.address_);
}

auto z80::operator<=(const MemoryUnit::Address lhs,
                     const MemoryUnit::Address rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ <= rhs.address_);
}

auto z80::operator>(const MemoryUnit::Address lhs,
                    const MemoryUnit::Address rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ > rhs.address_);
}

auto z80::operator>=(const MemoryUnit::Address lhs,
                     const MemoryUnit::Address rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ >= rhs.address_);
}

auto z80::operator==(z80::MemoryUnit::MutableAddress lhs,
                     z80::MemoryUnit::MutableAddress rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ == rhs.address_);
}

auto z80::operator!=(z80::MemoryUnit::MutableAddress lhs,
                     z80::MemoryUnit::MutableAddress rhs) noexcept -> bool {
	return (lhs.parent_ != rhs.parent_) or (lhs.address_ != rhs.address_);
}

auto z80::operator<(z80::MemoryUnit::MutableAddress lhs,
                    z80::MemoryUnit::MutableAddress rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ < rhs.address_);
}

auto z80::operator<=(z80::MemoryUnit::MutableAddress lhs,
                     z80::MemoryUnit::MutableAddress rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ <= rhs.address_);
}

auto z80::operator>(z80::MemoryUnit::MutableAddress lhs,
                    z80::MemoryUnit::MutableAddress rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ > rhs.address_);
}

auto z80::operator>=(z80::MemoryUnit::MutableAddress lhs,
                     z80::MemoryUnit::MutableAddress rhs) noexcept -> bool {
	return (lhs.parent_ == rhs.parent_) and (lhs.address_ >= rhs.address_);
}

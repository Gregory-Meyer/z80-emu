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

auto z80::MemoryUnit::max_size() const noexcept -> SizeT {
	return std::numeric_limits<SizeT>::max();
}

auto z80::MemoryUnit::data() noexcept -> ValueT* {
	return data_.data();
}

auto z80::MemoryUnit::data() const noexcept -> const ValueT* {
	return data_.data();
}

auto z80::MemoryUnit::operator[](const SizeT address) -> ValueT& {
	return data_[address];
}

auto z80::MemoryUnit::operator[](
	const SizeT address
) const -> const ValueT& {
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

z80::MemoryUnit::Slice::Slice(const MutableSlice mut_slice) noexcept
	: parent_ { mut_slice.parent_ }, begin_{ mut_slice.begin_ },
	  end_{ mut_slice.end_ }
{ }

auto z80::MemoryUnit::Slice::at(const SizeT pos) const -> const ValueT& {
	if (pos >= size()) {
		throw OutOfBoundsException{ "Slice::at" };
	}

	return (*this)[pos];
}

auto z80::MemoryUnit::Slice::operator[](
	const SizeT pos
) const -> const ValueT& {
	return (*parent_)[static_cast<SizeT>(begin_ + pos)];
}

auto z80::MemoryUnit::Slice::front() const -> const ValueT& {
	return (*parent_)[begin_];
}

auto z80::MemoryUnit::Slice::back() const -> const ValueT& {
	return (*parent_)[static_cast<SizeT>(end_ - 1)];
}

auto z80::MemoryUnit::Slice::data() const noexcept -> const ValueT* {
	return std::addressof((*parent_)[begin_]);
}

auto z80::MemoryUnit::Slice::begin() const noexcept -> iterator {
	return cbegin();
}

auto z80::MemoryUnit::Slice::cbegin() const noexcept -> const_iterator {
	return std::addressof((*parent_)[begin_]);
}

auto z80::MemoryUnit::Slice::end() const noexcept -> iterator {
	return cend();
}

auto z80::MemoryUnit::Slice::cend() const noexcept -> const_iterator {
	return std::addressof((*parent_)[end_]);
}

auto z80::MemoryUnit::Slice::rbegin() const noexcept -> reverse_iterator {
	return crbegin();
}

auto z80::MemoryUnit::Slice::crbegin() const noexcept -> const_reverse_iterator {
	return const_reverse_iterator{ cend() };
}

auto z80::MemoryUnit::Slice::rend() const noexcept -> reverse_iterator {
	return crend();
}

auto z80::MemoryUnit::Slice::crend() const noexcept -> const_reverse_iterator {
	return const_reverse_iterator{ cbegin() };
}

auto z80::MemoryUnit::Slice::empty() const noexcept -> bool {
	return begin_ == end_;
}

auto z80::MemoryUnit::Slice::size() const noexcept -> SizeT {
	return static_cast<SizeT>(end_ - begin_);
}

auto z80::MemoryUnit::Slice::max_size() const noexcept -> SizeT {
	return std::numeric_limits<SizeT>::max();
}

auto z80::MemoryUnit::Slice::swap(Slice &other) noexcept -> void {
	using std::swap;

	swap(parent_, other.parent_);
	swap(begin_, other.begin_);
	swap(end_, other.end_);
}

z80::MemoryUnit::Slice::Slice(const z80::MemoryUnit &parent,
                              z80::MemoryUnit::SizeT lower,
                              z80::MemoryUnit::SizeT upper) noexcept
	: parent_{ &parent }, begin_{ lower }, end_{ upper }
{ }

auto z80::MemoryUnit::MutableSlice::at(const SizeT pos) const -> ValueT& {
	if (pos >= size()) {
		throw OutOfBoundsException{ "Slice::at" };
	}

	return (*this)[pos];
}

auto z80::MemoryUnit::MutableSlice::operator[](const SizeT pos) const -> ValueT& {
	return (*parent_)[pos];
}

auto z80::MemoryUnit::MutableSlice::front() const -> ValueT& {
	return (*parent_)[begin_];
}

auto z80::MemoryUnit::MutableSlice::back() const -> ValueT& {
	return (*parent_)[static_cast<SizeT>(end_ - 1)];
}

auto z80::MemoryUnit::MutableSlice::data() const noexcept -> ValueT* {
	return std::addressof((*parent_)[begin_]);
}

auto z80::MemoryUnit::MutableSlice::begin() const noexcept -> iterator {
	return data();
}

auto z80::MemoryUnit::MutableSlice::cbegin() const noexcept -> const_iterator {
	return data();
}

auto z80::MemoryUnit::MutableSlice::end() const noexcept -> iterator {
	return std::addressof((*parent_)[end_]);
}

auto z80::MemoryUnit::MutableSlice::cend() const noexcept -> const_iterator {
	return std::addressof((*parent_)[end_]);
}

auto z80::MemoryUnit::MutableSlice::rbegin() const noexcept -> reverse_iterator {
	return reverse_iterator{ end() };
}

auto z80::MemoryUnit::MutableSlice::crbegin() const noexcept -> const_reverse_iterator {
	return const_reverse_iterator{ cend() };
}

auto z80::MemoryUnit::MutableSlice::rend() const noexcept -> reverse_iterator {
	return reverse_iterator{ begin() };
}

auto z80::MemoryUnit::MutableSlice::crend() const noexcept -> const_reverse_iterator {
	return const_reverse_iterator{ cbegin() };
}

auto z80::MemoryUnit::MutableSlice::empty() const noexcept -> bool {
	return begin_ == end_;
}

auto z80::MemoryUnit::MutableSlice::size() const noexcept -> SizeT {
	return static_cast<SizeT>(end_ - begin_);
}

auto z80::MemoryUnit::MutableSlice::max_size() const noexcept -> SizeT {
	return std::numeric_limits<SizeT>::max();
}

auto z80::MemoryUnit::MutableSlice::swap(MutableSlice &other) noexcept -> void {
	using std::swap;

	swap(parent_, other.parent_);
	swap(begin_, other.begin_);
	swap(end_, other.end_);
}

z80::MemoryUnit::MutableSlice::MutableSlice(MemoryUnit &parent,
                                            const SizeT lower,
                                            const SizeT upper) noexcept
	: parent_{ &parent }, begin_{ lower }, end_{ upper }
{ }

auto z80::swap(MemoryUnit::Address &lhs,
                MemoryUnit::Address &rhs) noexcept -> void {
	lhs.swap(rhs);
}

auto z80::swap(MemoryUnit::MutableAddress &lhs,
               MemoryUnit::MutableAddress &rhs) noexcept -> void {
	lhs.swap(rhs);
}

auto z80::swap(MemoryUnit::Slice &lhs,
               MemoryUnit::Slice &rhs) noexcept -> void {
	lhs.swap(rhs);
}

auto z80::swap(MemoryUnit::MutableSlice &lhs,
               MemoryUnit::MutableSlice &rhs) noexcept -> void {
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

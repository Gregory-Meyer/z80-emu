#include "register_pair.h"

#include "byte_cast.hpp"

z80::RegisterPair::RegisterPair() noexcept : data_ { 0 } { }

z80::RegisterPair::RegisterPair(const RegisterPair &other) noexcept
	: data_{ other.data_.load() }
{ }

z80::RegisterPair::RegisterPair(const UnsignedRegister_t value) noexcept
	: data_{ value }
{ }

z80::RegisterPair::RegisterPair(const SignedRegister_t value) noexcept
	: data_{ byte_cast<UnsignedRegister_t>(value) }
{ }

z80::RegisterPair::RegisterPair(
	const UnsignedHalfRegister_t upper_value,
	const UnsignedHalfRegister_t lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

z80::RegisterPair::RegisterPair(
	const UnsignedHalfRegister_t upper_value,
	const SignedHalfRegister_t lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

z80::RegisterPair::RegisterPair(
	const SignedHalfRegister_t upper_value,
	const UnsignedHalfRegister_t lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

z80::RegisterPair::RegisterPair(
	const SignedHalfRegister_t upper_value,
	const SignedHalfRegister_t lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

auto z80::RegisterPair::operator=(const RegisterPair &other) noexcept -> RegisterPair& {
	data_ = other.data_.load();

	return *this;
}

auto z80::RegisterPair::operator=(const UnsignedRegister_t value) noexcept
	-> RegisterPair&
{
	set(value);

	return *this;
}

auto z80::RegisterPair::operator=(const SignedRegister_t value) noexcept
	-> RegisterPair&
{
	set(value);

	return *this;
}

z80::RegisterPair::operator UnsignedRegister_t() const noexcept {
	return get_unsigned();
}

z80::RegisterPair::operator SignedRegister_t() const noexcept {
	return get_signed();
}

auto z80::RegisterPair::set(const UnsignedRegister_t value) noexcept -> void {
	data_ = value;
}

auto z80::RegisterPair::set(const SignedRegister_t value) noexcept -> void {
	data_ = byte_cast<UnsignedRegister_t>(value);
}

auto z80::RegisterPair::get_unsigned() const noexcept -> UnsignedRegister_t {
	return data_.load();
}

auto z80::RegisterPair::get_signed() const noexcept -> SignedRegister_t {
	return byte_cast<SignedRegister_t>(get_unsigned());
}

auto z80::RegisterPair::upper() noexcept -> UpperReference {
	return UpperReference{ *this };
}

auto z80::RegisterPair::upper() const noexcept -> ConstUpperReference {
	return ConstUpperReference{ *this };
}

auto z80::RegisterPair::lower() noexcept -> LowerReference {
	return LowerReference{ *this };
}

auto z80::RegisterPair::lower() const noexcept -> ConstLowerReference {
	return ConstLowerReference{ *this };
}

auto z80::RegisterPair::set_upper(
	const UnsignedHalfRegister_t value
) noexcept -> void {
	const auto as_word = static_cast<UnsignedRegister_t>(value << 8);

	data_ &= 0b0000000011111111;
	data_ |= as_word;
}

auto z80::RegisterPair::set_upper(
	const SignedHalfRegister_t value
) noexcept -> void {
	set_upper(byte_cast<UnsignedHalfRegister_t>(value));
}

auto z80::RegisterPair::set_lower(
	const UnsignedHalfRegister_t value
) noexcept -> void {
	data_ &= 0b1111111100000000;
	data_ |= value;
}

auto z80::RegisterPair::set_lower(
	const SignedHalfRegister_t value
) noexcept -> void {
	set_lower(byte_cast<UnsignedHalfRegister_t>(value));
}

auto z80::RegisterPair::get_upper_unsigned() const noexcept
	-> UnsignedHalfRegister_t
{
	const auto as_int = data_.load() >> 8;

	return static_cast<UnsignedHalfRegister_t>(as_int);
}

auto z80::RegisterPair::get_upper_signed() const noexcept
	-> SignedHalfRegister_t
{
	return byte_cast<SignedHalfRegister_t>(get_upper_unsigned());
}

auto z80::RegisterPair::get_lower_unsigned() const noexcept
	-> UnsignedHalfRegister_t
{
	const auto as_int = data_.load() & 0b0000000011111111;

	return static_cast<UnsignedHalfRegister_t>(as_int);
}

auto z80::RegisterPair::get_lower_signed() const noexcept
	-> SignedHalfRegister_t
{
	return byte_cast<SignedHalfRegister_t>(get_lower_unsigned());
}

auto z80::RegisterPair::UpperReference::operator=(
	const UnsignedHalfRegister_t value
) noexcept -> UpperReference& {
	set(value);
	return *this;
}

auto z80::RegisterPair::UpperReference::operator=(
	const SignedHalfRegister_t value
) noexcept -> UpperReference& {
	set(value);
	return *this;
}

z80::RegisterPair::UpperReference::operator UnsignedHalfRegister_t()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::UpperReference::operator SignedHalfRegister_t()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::UpperReference::set(
	const UnsignedHalfRegister_t value
) noexcept -> void {
	parent_.set_upper(value);
}

auto z80::RegisterPair::UpperReference::set(
	const SignedHalfRegister_t value
) noexcept -> void {
	parent_.set_upper(value);
}

auto z80::RegisterPair::UpperReference::get_unsigned() const noexcept
	-> UnsignedHalfRegister_t
{
	return parent_.get_upper_unsigned();
}

auto z80::RegisterPair::UpperReference::get_signed() const noexcept
	-> SignedHalfRegister_t
{
	return parent_.get_upper_signed();
}

z80::RegisterPair::UpperReference::UpperReference(
	RegisterPair &parent
) noexcept : parent_{ parent } { }

z80::RegisterPair::ConstUpperReference::operator UnsignedHalfRegister_t()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::ConstUpperReference::operator SignedHalfRegister_t()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::ConstUpperReference::get_unsigned() const noexcept
	-> UnsignedHalfRegister_t
{
	return parent_.get_upper_unsigned();
}

auto z80::RegisterPair::ConstUpperReference::get_signed() const noexcept
	-> SignedHalfRegister_t
{
	return parent_.get_upper_signed();
}

z80::RegisterPair::ConstUpperReference::ConstUpperReference(
	const RegisterPair &parent
) noexcept : parent_{ parent } { }

auto z80::RegisterPair::LowerReference::operator=(
	const UnsignedHalfRegister_t value
) noexcept -> LowerReference& {
	set(value);
	return *this;
}

auto z80::RegisterPair::LowerReference::operator=(
	const SignedHalfRegister_t value
) noexcept -> LowerReference& {
	set(value);
	return *this;
}

z80::RegisterPair::LowerReference::operator UnsignedHalfRegister_t()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::LowerReference::operator SignedHalfRegister_t()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::LowerReference::set(
	const UnsignedHalfRegister_t value
) noexcept -> void {
	parent_.set_lower(value);
}

auto z80::RegisterPair::LowerReference::set(
	const SignedHalfRegister_t value
) noexcept -> void {
	parent_.set_lower(value);
}

auto z80::RegisterPair::LowerReference::get_unsigned() const noexcept
	-> UnsignedHalfRegister_t
{
	return parent_.get_lower_unsigned();
}

auto z80::RegisterPair::LowerReference::get_signed() const noexcept
	-> SignedHalfRegister_t
{
	return parent_.get_lower_signed();
}

z80::RegisterPair::LowerReference::LowerReference(
	RegisterPair &parent
) noexcept : parent_{ parent } { }

z80::RegisterPair::ConstLowerReference::operator UnsignedHalfRegister_t()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::ConstLowerReference::operator SignedHalfRegister_t()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::ConstLowerReference::get_unsigned() const noexcept
	-> UnsignedHalfRegister_t
{
	return parent_.get_lower_unsigned();
}

auto z80::RegisterPair::ConstLowerReference::get_signed() const noexcept
	-> SignedHalfRegister_t
{
	return parent_.get_lower_signed();
}

z80::RegisterPair::ConstLowerReference::ConstLowerReference(
	const RegisterPair &parent
) noexcept : parent_{ parent } { }

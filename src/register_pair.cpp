#include "register_pair.h"

#include "byte_cast.hpp"

z80::RegisterPair::RegisterPair() noexcept : data_ { 0 } { }

z80::RegisterPair::RegisterPair(const RegisterPair &other) noexcept
	: data_{ other.data_.load() }
{ }

z80::RegisterPair::RegisterPair(RegisterPair &&other) noexcept
	: data_{ other.data_.load() }
{ }

z80::RegisterPair::RegisterPair(const UnsignedWordT value) noexcept
	: data_{ value }
{ }

z80::RegisterPair::RegisterPair(const WordT value) noexcept
	: data_{ byte_cast<UnsignedWordT>(value) }
{ }

z80::RegisterPair::RegisterPair(
	const UnsignedHalfWordT upper_value,
	const UnsignedHalfWordT lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

z80::RegisterPair::RegisterPair(
	const UnsignedHalfWordT upper_value,
	const HalfWordT lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

z80::RegisterPair::RegisterPair(
	const HalfWordT upper_value,
	const UnsignedHalfWordT lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

z80::RegisterPair::RegisterPair(
	const HalfWordT upper_value,
	const HalfWordT lower_value
) noexcept : data_ { 0 } {
	set_upper(upper_value);
	set_lower(lower_value);
}

auto z80::RegisterPair::operator=(const RegisterPair &other) noexcept -> RegisterPair& {
	data_ = other.data_.load();

	return *this;
}

auto z80::RegisterPair::operator=(RegisterPair &&other) noexcept -> RegisterPair& {
	data_ = other.data_.load();

	return *this;
}

auto z80::RegisterPair::operator=(const UnsignedWordT value) noexcept
	-> RegisterPair&
{
	set(value);

	return *this;
}

auto z80::RegisterPair::operator=(const WordT value) noexcept
	-> RegisterPair&
{
	set(value);

	return *this;
}

z80::RegisterPair::operator UnsignedWordT() const noexcept {
	return get_unsigned();
}

z80::RegisterPair::operator WordT() const noexcept {
	return get_signed();
}

auto z80::RegisterPair::set(const UnsignedWordT value) noexcept -> void {
	data_ = value;
}

auto z80::RegisterPair::set(const WordT value) noexcept -> void {
	data_ = byte_cast<UnsignedWordT>(value);
}

auto z80::RegisterPair::get_unsigned() const noexcept -> UnsignedWordT {
	return data_.load();
}

auto z80::RegisterPair::get_signed() const noexcept -> WordT {
	return byte_cast<WordT>(get_unsigned());
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
	const UnsignedHalfWordT value
) noexcept -> void {
	const auto as_word = static_cast<UnsignedWordT>(value << 8);

	data_ &= 0b0000000011111111;
	data_ |= as_word;
}

auto z80::RegisterPair::set_upper(
	const HalfWordT value
) noexcept -> void {
	set_upper(byte_cast<UnsignedHalfWordT>(value));
}

auto z80::RegisterPair::set_lower(
	const UnsignedHalfWordT value
) noexcept -> void {
	data_ &= 0b1111111100000000;
	data_ |= value;
}

auto z80::RegisterPair::set_lower(
	const HalfWordT value
) noexcept -> void {
	set_lower(byte_cast<UnsignedHalfWordT>(value));
}

auto z80::RegisterPair::get_upper_unsigned() const noexcept
	-> UnsignedHalfWordT
{
	const auto as_int = data_.load() >> 8;

	return static_cast<UnsignedHalfWordT>(as_int);
}

auto z80::RegisterPair::get_upper_signed() const noexcept
	-> HalfWordT
{
	return byte_cast<HalfWordT>(get_upper_unsigned());
}

auto z80::RegisterPair::get_lower_unsigned() const noexcept
	-> UnsignedHalfWordT
{
	const auto as_int = data_.load() & 0b0000000011111111;

	return static_cast<UnsignedHalfWordT>(as_int);
}

auto z80::RegisterPair::get_lower_signed() const noexcept
	-> HalfWordT
{
	return byte_cast<HalfWordT>(get_lower_unsigned());
}

auto z80::RegisterPair::UpperReference::operator=(
	const UnsignedHalfWordT value
) noexcept -> UpperReference& {
	set(value);

	return *this;
}

auto z80::RegisterPair::UpperReference::operator=(
	const HalfWordT value
) noexcept -> UpperReference& {
	set(value);

	return *this;
}

z80::RegisterPair::UpperReference::operator UnsignedHalfWordT()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::UpperReference::operator HalfWordT()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::UpperReference::set(
	const UnsignedHalfWordT value
) noexcept -> void {
	parent_.set_upper(value);
}

auto z80::RegisterPair::UpperReference::set(
	const HalfWordT value
) noexcept -> void {
	parent_.set_upper(value);
}

auto z80::RegisterPair::UpperReference::get_unsigned() const noexcept
	-> UnsignedHalfWordT
{
	return parent_.get_upper_unsigned();
}

auto z80::RegisterPair::UpperReference::get_signed() const noexcept
	-> HalfWordT
{
	return parent_.get_upper_signed();
}

z80::RegisterPair::UpperReference::UpperReference(
	RegisterPair &parent
) noexcept : parent_{ parent } { }

z80::RegisterPair::ConstUpperReference::operator UnsignedHalfWordT()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::ConstUpperReference::operator HalfWordT()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::ConstUpperReference::get_unsigned() const noexcept
	-> UnsignedHalfWordT
{
	return parent_.get_upper_unsigned();
}

auto z80::RegisterPair::ConstUpperReference::get_signed() const noexcept
	-> HalfWordT
{
	return parent_.get_upper_signed();
}

z80::RegisterPair::ConstUpperReference::ConstUpperReference(
	const RegisterPair &parent
) noexcept : parent_{ parent } { }

auto z80::RegisterPair::LowerReference::operator=(
	const UnsignedHalfWordT value
) noexcept -> LowerReference& {
	set(value);

	return *this;
}

auto z80::RegisterPair::LowerReference::operator=(
	const HalfWordT value
) noexcept -> LowerReference& {
	set(value);

	return *this;
}

z80::RegisterPair::LowerReference::operator UnsignedHalfWordT()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::LowerReference::operator HalfWordT()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::LowerReference::set(
	const UnsignedHalfWordT value
) noexcept -> void {
	parent_.set_lower(value);
}

auto z80::RegisterPair::LowerReference::set(
	const HalfWordT value
) noexcept -> void {
	parent_.set_lower(value);
}

auto z80::RegisterPair::LowerReference::get_unsigned() const noexcept
	-> UnsignedHalfWordT
{
	return parent_.get_lower_unsigned();
}

auto z80::RegisterPair::LowerReference::get_signed() const noexcept
	-> HalfWordT
{
	return parent_.get_lower_signed();
}

z80::RegisterPair::LowerReference::LowerReference(
	RegisterPair &parent
) noexcept : parent_{ parent } { }

z80::RegisterPair::ConstLowerReference::operator UnsignedHalfWordT()
	const noexcept
{
	return get_unsigned();
}

z80::RegisterPair::ConstLowerReference::operator HalfWordT()
	const noexcept
{
	return get_signed();
}

auto z80::RegisterPair::ConstLowerReference::get_unsigned() const noexcept
	-> UnsignedHalfWordT
{
	return parent_.get_lower_unsigned();
}

auto z80::RegisterPair::ConstLowerReference::get_signed() const noexcept
	-> HalfWordT
{
	return parent_.get_lower_signed();
}

z80::RegisterPair::ConstLowerReference::ConstLowerReference(
	const RegisterPair &parent
) noexcept : parent_{ parent } { }

// 16 bit register
// can be accessed as one 16-bit register or two 8-bit registers
// uses atomic underlying representation to avoid data races

#ifndef GREGJM_Z80_REGISTER_PAIR_H
#define GREGJM_Z80_REGISTER_PAIR_H

#include "types.hpp"

#include <cstdint>
#include <atomic>

namespace z80 {

class RegisterPair {
public:
	class UpperReference {
	public:
		friend RegisterPair;

		UpperReference() = delete;

		UpperReference(const UpperReference &other) = default;

		UpperReference(UpperReference &&other) = default;

		auto operator=(const UpperReference &other) -> UpperReference& = delete;

		auto operator=(UpperReference &&other) -> UpperReference& = delete;

		auto operator=(UnsignedHalfWordT value) noexcept
			-> UpperReference&;

		auto operator=(HalfWordT value) noexcept
			-> UpperReference&;

		explicit operator UnsignedHalfWordT() const noexcept;

		explicit operator HalfWordT() const noexcept;

		auto set(UnsignedHalfWordT value) noexcept -> void;

		auto set(HalfWordT value) noexcept -> void;

		auto get_unsigned() const noexcept -> UnsignedHalfWordT;

		auto get_signed() const noexcept -> HalfWordT;

	private:
		explicit UpperReference(RegisterPair &parent) noexcept;

		RegisterPair &parent_;
	};

	class ConstUpperReference {
	public:
		friend RegisterPair;

		ConstUpperReference() = delete;

		ConstUpperReference(const ConstUpperReference &other) = default;

		ConstUpperReference(ConstUpperReference &&other) = default;

		auto operator=(const ConstUpperReference &other)
			-> ConstUpperReference& = delete;

		auto operator=(ConstUpperReference &&other)
			-> ConstUpperReference& = delete;

		explicit operator UnsignedHalfWordT() const noexcept;

		explicit operator HalfWordT() const noexcept;

		auto get_unsigned() const noexcept -> UnsignedHalfWordT;

		auto get_signed() const noexcept -> HalfWordT;

	private:
		explicit ConstUpperReference(const RegisterPair &parent) noexcept;

		const RegisterPair &parent_;
	};

	class LowerReference {
	public:
		friend RegisterPair;

		LowerReference() = delete;

		LowerReference(const LowerReference &other) = default;

		LowerReference(LowerReference &&other) = default;

		auto operator=(const LowerReference &other) -> LowerReference& = delete;

		auto operator=(LowerReference &&other) -> LowerReference& = delete;

		auto operator=(UnsignedHalfWordT value) noexcept
			-> LowerReference&;

		auto operator=(HalfWordT value) noexcept
			-> LowerReference&;

		explicit operator UnsignedHalfWordT() const noexcept;

		explicit operator HalfWordT() const noexcept;

		auto set(UnsignedHalfWordT value) noexcept -> void;

		auto set(HalfWordT value) noexcept -> void;

		auto get_unsigned() const noexcept -> UnsignedHalfWordT;

		auto get_signed() const noexcept -> HalfWordT;

	private:
		explicit LowerReference(RegisterPair &parent) noexcept;

		RegisterPair &parent_;
	};

	class ConstLowerReference {
	public:
		friend RegisterPair;

		ConstLowerReference() = delete;

		ConstLowerReference(const ConstLowerReference &other) = default;

		ConstLowerReference(ConstLowerReference &&other) = default;

		explicit operator UnsignedHalfWordT() const noexcept;

		explicit operator HalfWordT() const noexcept;

		auto get_unsigned() const noexcept -> UnsignedHalfWordT;

		auto get_signed() const noexcept -> HalfWordT;

	private:
		explicit ConstLowerReference(const RegisterPair &parent) noexcept;

		const RegisterPair &parent_;
	};

	RegisterPair() noexcept;

	RegisterPair(const RegisterPair &other) noexcept;

	RegisterPair(RegisterPair &&other) noexcept;

	explicit RegisterPair(UnsignedWordT value) noexcept;

	explicit RegisterPair(WordT value) noexcept;

	RegisterPair(UnsignedHalfWordT upper_value,
	             UnsignedHalfWordT lower_value) noexcept;

	RegisterPair(UnsignedHalfWordT upper_value, HalfWordT lower_value) noexcept;

	RegisterPair(HalfWordT upper_value, UnsignedHalfWordT lower_value) noexcept;

	RegisterPair(HalfWordT upper_value, HalfWordT lower_value) noexcept;

	auto operator=(const RegisterPair &other) noexcept -> RegisterPair&;

	auto operator=(RegisterPair &&other) noexcept -> RegisterPair&;

	auto operator=(UnsignedWordT value) noexcept -> RegisterPair&;

	auto operator=(WordT value) noexcept -> RegisterPair&;

	explicit operator UnsignedWordT() const noexcept;

	explicit operator WordT() const noexcept;

	auto set(UnsignedWordT value) noexcept -> void;

	auto set(WordT value) noexcept -> void;

	auto get_unsigned() const noexcept -> UnsignedWordT;

	auto get_signed() const noexcept -> WordT;

	auto upper() noexcept -> UpperReference;

	auto upper() const noexcept -> ConstUpperReference;

	auto lower() noexcept -> LowerReference;

	auto lower() const noexcept -> ConstLowerReference;

private:
	auto set_upper(UnsignedHalfWordT value) noexcept -> void;

	auto set_upper(HalfWordT value) noexcept -> void;

	auto set_lower(UnsignedHalfWordT value) noexcept -> void;

	auto set_lower(HalfWordT value) noexcept -> void;

	auto get_upper_unsigned() const noexcept -> UnsignedHalfWordT;

	auto get_upper_signed() const noexcept -> HalfWordT;

	auto get_lower_unsigned() const noexcept -> UnsignedHalfWordT;

	auto get_lower_signed() const noexcept -> HalfWordT;

	std::atomic<UnsignedWordT> data_;
};

} // namespace z80

#endif

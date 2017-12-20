// 16 bit register
// can be accessed as one 16-bit register or two 8-bit registers
// uses atomic underlying representation to avoid issues and stuff

#ifndef GREGJM_Z80_REGISTER_PAIR_H
#define GREGJM_Z80_REGISTER_PAIR_H

#include <cstdint>
#include <atomic>

namespace z80 {

using SignedRegister_t = std::int16_t;
using SignedHalfRegister_t = std::int8_t;
using UnsignedRegister_t = std::uint16_t;
using UnsignedHalfRegister_t = std::uint8_t;

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

		auto operator=(const UnsignedHalfRegister_t value) noexcept
			-> UpperReference&;

		auto operator=(const SignedHalfRegister_t value) noexcept
			-> UpperReference&;

		explicit operator UnsignedHalfRegister_t() const noexcept;

		explicit operator SignedHalfRegister_t() const noexcept;

		auto set(const UnsignedHalfRegister_t value) noexcept -> void;

		auto set(const SignedHalfRegister_t value) noexcept -> void;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t;

		auto get_signed() const noexcept -> SignedHalfRegister_t;

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

		explicit operator UnsignedHalfRegister_t() const noexcept;

		explicit operator SignedHalfRegister_t() const noexcept;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t;

		auto get_signed() const noexcept -> SignedHalfRegister_t;

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

		auto operator=(const UnsignedHalfRegister_t value) noexcept
			-> LowerReference&;

		auto operator=(const SignedHalfRegister_t value) noexcept
			-> LowerReference&;

		explicit operator UnsignedHalfRegister_t() const noexcept;

		explicit operator SignedHalfRegister_t() const noexcept;

		auto set(const UnsignedHalfRegister_t value) noexcept -> void;

		auto set(const SignedHalfRegister_t value) noexcept -> void;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t;

		auto get_signed() const noexcept -> SignedHalfRegister_t;

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

		auto operator=(const ConstLowerReference &other)
			-> ConstLowerReference& = delete;

		auto operator=(ConstLowerReference &&other)
			-> ConstLowerReference& = delete;

		explicit operator UnsignedHalfRegister_t() const noexcept;

		explicit operator SignedHalfRegister_t() const noexcept;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t;

		auto get_signed() const noexcept -> SignedHalfRegister_t;

	private:
		explicit ConstLowerReference(const RegisterPair &parent) noexcept;

		const RegisterPair &parent_;
	};

	RegisterPair() noexcept;

	RegisterPair(const RegisterPair &other) noexcept;

	RegisterPair(RegisterPair &&other) noexcept = default;

	explicit RegisterPair(const UnsignedRegister_t value) noexcept;

	explicit RegisterPair(const SignedRegister_t value) noexcept;

	RegisterPair(const UnsignedHalfRegister_t upper_value,
				 const UnsignedHalfRegister_t lower_value) noexcept;

	RegisterPair(const UnsignedHalfRegister_t upper_value,
				 const SignedHalfRegister_t lower_value) noexcept;

	RegisterPair(const SignedHalfRegister_t upper_value,
				 const UnsignedHalfRegister_t lower_value) noexcept;

	RegisterPair(const SignedHalfRegister_t upper_value,
				 const SignedHalfRegister_t lower_value) noexcept;

	auto operator=(const RegisterPair &other) noexcept -> RegisterPair&;

	auto operator=(RegisterPair &&other) noexcept -> RegisterPair& = default;

	auto operator=(const UnsignedRegister_t value) noexcept -> RegisterPair&;

	auto operator=(const SignedRegister_t value) noexcept -> RegisterPair&;

	explicit operator UnsignedRegister_t() const noexcept;

	explicit operator SignedRegister_t() const noexcept;

	auto set(const UnsignedRegister_t value) noexcept -> void;

	auto set(const SignedRegister_t value) noexcept -> void;

	auto get_unsigned() const noexcept -> UnsignedRegister_t;

	auto get_signed() const noexcept -> SignedRegister_t;

	auto upper() noexcept -> UpperReference;

	auto upper() const noexcept -> ConstUpperReference;

	auto lower() noexcept -> LowerReference;

	auto lower() const noexcept -> ConstLowerReference;

private:
	auto set_upper(const UnsignedHalfRegister_t value) noexcept -> void;

	auto set_upper(const SignedHalfRegister_t value) noexcept -> void;

	auto set_lower(const UnsignedHalfRegister_t value) noexcept -> void;

	auto set_lower(const SignedHalfRegister_t value) noexcept -> void;

	auto get_upper_unsigned() const noexcept -> UnsignedHalfRegister_t;

	auto get_upper_signed() const noexcept -> SignedHalfRegister_t;

	auto get_lower_unsigned() const noexcept -> UnsignedHalfRegister_t;

	auto get_lower_signed() const noexcept -> SignedHalfRegister_t;

	std::atomic<UnsignedRegister_t> data_;
};

} // namespace z80

#endif

// 16 bit register
// can be accessed as one 16-bit register or two 8-bit registers
// uses atomic underlying representation to avoid data races

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
	class Reference {
	public:
		friend RegisterPair;

		Reference() = delete;

		Reference(const Reference &other) = default;

		Reference(Reference &&other) = default;

		auto operator=(const Reference &other) -> Reference& = delete;

		auto operator=(Reference &&other) -> Reference& = delete;

		auto operator=(const UnsignedHalfRegister_t value) noexcept
			-> Reference&;

		auto operator=(const SignedHalfRegister_t value) noexcept -> Reference&;

		virtual ~Reference();

		explicit operator UnsignedHalfRegister_t() const noexcept;

		explicit operator SignedHalfRegister_t() const noexcept;

		virtual auto set(const UnsignedHalfRegister_t value) noexcept
			-> void = 0;

		virtual auto set(const SignedHalfRegister_t value) noexcept
			-> void = 0;

		virtual auto get_unsigned() const noexcept
			-> UnsignedHalfRegister_t = 0;

		virtual auto get_signed() const noexcept -> SignedHalfRegister_t = 0;

	private:
		explicit Reference(RegisterPair &parent) noexcept;

		RegisterPair &parent_;
	};

	class ConstReference {
	public:
		friend RegisterPair;

		ConstReference() = delete;

		ConstReference(const ConstReference &other) = default;

		ConstReference(ConstReference &&other) = default;

		auto operator=(const ConstReference &other) -> ConstReference& = delete;

		auto operator=(ConstReference &&other) -> ConstReference& = delete;

		virtual ~ConstReference();

		explicit operator UnsignedHalfRegister_t() const noexcept;

		explicit operator SignedHalfRegister_t() const noexcept;

		virtual auto get_unsigned() const noexcept
			-> UnsignedHalfRegister_t = 0;

		virtual auto get_signed() const noexcept -> SignedHalfRegister_t = 0;

	private:
		explicit ConstReference(const RegisterPair &parent) noexcept;

		const RegisterPair &parent_;
	};

	class UpperReference final : public Reference {
	public:
		friend RegisterPair;

		UpperReference() = delete;

		UpperReference(const UpperReference &other) = default;

		UpperReference(UpperReference &&other) = default;

		auto operator=(const UpperReference &other) -> UpperReference& = delete;

		auto operator=(UpperReference &&other) -> UpperReference& = delete;

		auto set(const UnsignedHalfRegister_t value) noexcept -> void override;

		auto set(const SignedHalfRegister_t value) noexcept -> void override;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t override;

		auto get_signed() const noexcept -> SignedHalfRegister_t override;

	private:
		explicit UpperReference(RegisterPair &parent) noexcept;
	};

	class ConstUpperReference final : public ConstReference {
	public:
		friend RegisterPair;

		ConstUpperReference() = delete;

		ConstUpperReference(const ConstUpperReference &other) = default;

		ConstUpperReference(ConstUpperReference &&other) = default;

		auto operator=(const ConstUpperReference &other)
			-> ConstUpperReference& = delete;

		auto operator=(ConstUpperReference &&other)
			-> ConstUpperReference& = delete;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t override;

		auto get_signed() const noexcept -> SignedHalfRegister_t override;

	private:
		explicit ConstUpperReference(const RegisterPair &parent) noexcept;
	};

	class LowerReference final : public Reference {
	public:
		friend RegisterPair;

		LowerReference() = delete;

		LowerReference(const LowerReference &other) = default;

		LowerReference(LowerReference &&other) = default;

		auto operator=(const LowerReference &other) -> LowerReference& = delete;

		auto operator=(LowerReference &&other) -> LowerReference& = delete;

		auto set(const UnsignedHalfRegister_t value) noexcept -> void override;

		auto set(const SignedHalfRegister_t value) noexcept -> void override;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t override;

		auto get_signed() const noexcept -> SignedHalfRegister_t override;

	private:
		explicit LowerReference(RegisterPair &parent) noexcept;
	};

	class ConstLowerReference final : public ConstReference {
	public:
		friend RegisterPair;

		ConstLowerReference() = delete;

		ConstLowerReference(const ConstLowerReference &other) = default;

		ConstLowerReference(ConstLowerReference &&other) = default;

		auto get_unsigned() const noexcept -> UnsignedHalfRegister_t override;

		auto get_signed() const noexcept -> SignedHalfRegister_t override;

	private:
		explicit ConstLowerReference(const RegisterPair &parent) noexcept;
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

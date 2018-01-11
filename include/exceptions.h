#ifndef GREGJM_Z80_EXCEPTIONS_H
#define GREGJM_Z80_EXCEPTIONS_H

#include <stdexcept>
#include <string>
#include <string_view>

namespace z80 {

//class NonmemberException : public std::logic_error {
//public:
//	explicit NonmemberException(const std::string &reason);
//
//	explicit NonmemberException(const char *reason);
//
//	virtual ~NonmemberException() = default;
//};

//class NullPointerException : public std::logic_error {
//public:
//	explicit NullPointerException(const std::string &reason);
//
//	explicit NullPointerException(const char *reason);
//
//	virtual ~NullPointerException() = default;
//};

class OutOfBoundsException : public std::out_of_range {
public:
	explicit OutOfBoundsException(const std::string &reason);

	explicit OutOfBoundsException(const char *reason);

	virtual ~OutOfBoundsException() = default;
};

} // namespace z80

#endif

#include "exceptions.h"

#include <utility>

//z80::NonmemberException::NonmemberException(const std::string &reason)
//	: std::logic_error{ reason }
//{ }
//
//z80::NonmemberException::NonmemberException(const char *const reason)
//	: std::logic_error{ reason }
//{ }

//z80::NullPointerException::NullPointerException(const std::string &reason)
//	: std::logic_error{ reason }
//{ }
//
//z80::NullPointerException::NullPointerException(const char *const reason)
//	: std::logic_error{ reason }
//{ }

z80::OutOfBoundsException::OutOfBoundsException(const std::string &reason)
	: std::out_of_range{ reason }
{ }

z80::OutOfBoundsException::OutOfBoundsException(const char *const reason)
	: std::out_of_range{ reason }
{ }

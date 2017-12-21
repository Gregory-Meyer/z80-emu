#ifndef GREGJM_Z80_ZILOG_H
#define GREGJM_Z80_ZILOG_H

#include "register_pair.h"

namespace z80 {

class Zilog {
public:

private:
	struct Registers {
		RegisterPair af;
		RegisterPair bc;
		RegisterPair de;
		RegisterPair hl;
	};

	Registers main_;
	Registers alternate_;
	RegisterPair index_y_;
	RegisterPair index_x_;
	UnsignedRegister_t stack_pointer_;
	UnsignedHalfRegister_t interrupt_;
	UnsignedHalfRegister_t refresh_;
	UnsignedRegister_t program_counter_;
	UnsignedHalfRegister_t flags_;
};

} // namespace z80

#endif

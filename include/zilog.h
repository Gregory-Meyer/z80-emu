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
	UnsignedWordT stack_pointer_;
	UnsignedHalfWordT interrupt_;
	UnsignedHalfWordT refresh_;
	UnsignedWordT program_counter_;
	UnsignedHalfWordT flags_;
};

} // namespace z80

#endif

#ifndef GREGJM_Z80_FLAG_REGISTER_H
#define GREGJM_Z80_FLAG_REGISTER_H

#include "types.hpp"

#include <bitset>

namespace z80 {

class FlagRegister {
public:

private:
	std::bitset<8> flags_;
};

} // namespace z80

#endif

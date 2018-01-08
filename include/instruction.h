#ifndef GREGJM_Z80_INSTRUCTION_H
#define GREGJM_Z80_INSTRUCTION_H

#include <bitset>
#include <string_view>

namespace z80 {

class Instruction {
public:
	void execute() const;

private:
	virtual void execute_impl() const;

	std::bitset<16> data_;
};

} // namespace z80


#endif

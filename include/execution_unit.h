#ifndef GREGJM_Z80_EXECUTION_UNIT_H
#define GREGJM_Z80_EXECUTION_UNIT_H

#include "types.hpp"

namespace z80 {

enum class OperationMode {
	Add, AddCarry, Subtract, SubtractCarry, And, Or, Xor, Compare, Increment,
	Decrement, RotateLeft, RotateLeftCarry, RotateRight, RotateRightCarry,
	ShiftLeft, ShiftRight, TestBit, SetBit, ResetBit
};

class ExecutionUnit {
public:
	auto execute(MathWordT lhs, MathWordT rhs,
	             OperationMode mode) noexcept -> MathWordT;

private:
};

} // namespace z80

#endif

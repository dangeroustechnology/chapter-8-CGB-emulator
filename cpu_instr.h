#include "memory.h"

#pragma once

class cpu_instr
{
public: 
	memory memo;
	cpu_instr();
	// 8-bit load instructions
	void load_rr(unsigned char register1, unsigned char register2);
	void load_rn(unsigned char register1, unsigned char data);
	void load_ra(unsigned char register1, unsigned short address);  // pass in addr from a 16-bit register
	void load_ro(unsigned char register1, unsigned char offset);  // offset can come from data or C register
	void load_rad(unsigned char register1);
	void load_rai(unsigned char register1);
	void load_or(unsigned char offset, unsigned char register1);
	void load_ar(unsigned short address, unsigned char register1);
	void load_an(unsigned short address, unsigned char data);
	void load_adr(unsigned char register1);
	void load_air(unsigned char register1);
	// 16-bit load instructions
	void load_rrnn(unsigned short register1, unsigned short data);
	void load_nnsp(unsigned short address);
	void load_sphl();
	void push_rr(unsigned char register1);
	void push_nn(unsigned short data); // not part of the instr set, just for convenience
	unsigned short pop_rr();
	// 8-bit arithmetic/logic instructions
	void add_reg(unsigned char register1, unsigned char data);
	void add_reg_c(unsigned char register1, unsigned char data);
	void sub_reg(unsigned char register1, unsigned char data);
	void sub_reg_c(unsigned char register1, unsigned char data);
	void compare(unsigned char register1, unsigned char data);
	void increment(unsigned char register1);
	void increment(unsigned short address);
	void decrement(unsigned char register1);
	void decrement(unsigned short address);
	void and_reg(unsigned char register1, unsigned char data);
	void or_reg(unsigned char register1, unsigned char data);
	void xor_reg(unsigned char register1, unsigned char data);
	void complement_c();
	void set_cflag(bool flag);
	void complement_a();
	void daa();												// TODO
	// 16-bit arithmetic instructions
	void add_16(unsigned short register1);
	void increment_16(unsigned char register1);
	void decrement_16(unsigned char register1);
	void add_sp(signed char data);
	void load_HLSP(signed char data);
	// Control flow & misc instructions
	void jump(unsigned short address);
	void jump_cnd(bool condition, unsigned short address);
	void jump_rel(signed char offset);
	void call(unsigned short address);
	void call_cnd(bool condition, unsigned short address);
	void ret();
	void ret_cnd(bool condition);
	void reti();											// TODO
	void halt();											// TODO
	void stop();											// TODO
	void set_interrupts(bool flag);							// TODO
	void nop();
	// Rotate & shift instructions
	void rot_left(unsigned char register1);
	void rot_left_c(unsigned char register1);
	void rot_right(unsigned char register1);
	void rot_right_c(unsigned char register1);
	void swap_reg(unsigned char register1);
	void swap_addr(unsigned short address);
	// Bit instructions
	void bit_reg(unsigned char bit, unsigned char register1);
	void bit_addr(unsigned char bit, unsigned short address);
	void set_bit_reg(unsigned char bit, unsigned char register1);
	void set_bit_addr(unsigned char bit, unsigned short address);
	void reset_bit_reg(unsigned char bit, unsigned char register1);
	void reset_bit_addr(unsigned char bit, unsigned short address);
};


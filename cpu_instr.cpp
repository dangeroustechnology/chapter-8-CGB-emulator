#include "cpu_instr.h"

using namespace std;

cpu_instr::cpu_instr() {
	
}

// 8-bit load instructions
void cpu_instr::load_rr(unsigned char r1, unsigned char r2) {		// load to register from register
	memo.reg[r1] = memo.reg[r2];
}

void cpu_instr::load_rn(unsigned char r, unsigned char n) {			// load to register from data
	memo.reg[r] = n;
}

void cpu_instr::load_ra(unsigned char r, unsigned short a) {		// load to register from address
	memo.reg[r] = memo.mem[a];
}

void cpu_instr::load_ro(unsigned char r, unsigned char o) {			// load to register from offset
	memo.reg[r] = memo.mem[0xFF00 + o];
}

void cpu_instr::load_rad(unsigned char r) {							// load to register from addr (decrement)
	memo.reg[r] = memo.mem[memo.get_HL()];
	memo.set_HL(memo.get_HL() - 1);
}

void cpu_instr::load_rai(unsigned char r) {							// load to register from addr (increment)
	memo.reg[r] = memo.mem[memo.get_HL()];
	memo.set_HL(memo.get_HL() + 1);
}

void cpu_instr::load_or(unsigned char o, unsigned char r) {			// load to offset from register
	memo.mem[0xFF00 + o] = memo.reg[r];
}

void cpu_instr::load_ar(unsigned short a, unsigned char r) {		// load to address from register
	memo.mem[a] = memo.reg[r];
}

void cpu_instr::load_an(unsigned short a, unsigned char n) {		// load to address from data
	memo.mem[a] = n;
}

void cpu_instr::load_adr(unsigned char r) {							// load to addr from register (decrement)
	memo.mem[memo.get_HL()] = memo.reg[r];
	memo.set_HL(memo.get_HL() - 1);
}

void cpu_instr::load_air(unsigned char r) {							// load to addr from register (increment)
	memo.mem[memo.get_HL()] = memo.reg[r];
	memo.set_HL(memo.get_HL() + 1);
}

// 16-bit load instructions
void cpu_instr::load_rrnn(unsigned short r, unsigned short n) {		// load to register from data
	switch (r) {
	case 2:
		memo.set_BC(n);
		break;
	case 4:
		memo.set_DE(n);
		break;
	case 6:
		memo.set_HL(n);
		break;
	case 8:
		memo.sp = n;
	}
}

void cpu_instr::load_nnsp(unsigned short a) {						// load to address from stack pointer
	unsigned char low = memo.sp & 0xFF;
	unsigned char high = (memo.sp & 0xFF00) >> 8;
	memo.mem[a] = low;
	memo.mem[a + 1] = high;
}

void cpu_instr::load_sphl() {										// load to stack pointer from register (HL)
	memo.sp = memo.get_HL();
}

void cpu_instr::push_rr(unsigned char r) {							// push register to stack
	unsigned char low = memo.reg[r + 1];
	unsigned char high = memo.reg[r];
	memo.stack[memo.sp] = low;
	memo.sp++;
	memo.stack[memo.sp] = high;
	memo.sp++;
}

void cpu_instr::push_nn(unsigned short d) {							// push immediate data to stack
	unsigned char low = d & 0xFF;
	unsigned char high = (d >> 8) & 0xFF;
	memo.stack[memo.sp] = low;
	memo.sp++;
	memo.stack[memo.sp] = high;
	memo.sp++;
}

unsigned short cpu_instr::pop_rr() {								// pop from stack
	memo.sp--;
	unsigned short data = memo.stack[memo.sp];
	data = data << 8;
	memo.sp--;
	unsigned char low = memo.stack[memo.sp];
	data |= low;
	return data;
}

// 8-bit arithmetic instructions
// i have not implemented Hf regularly due to the fact that it is only used by DAA, which is also unimplemented
void cpu_instr::add_reg(unsigned char r, unsigned char n) {		// add data to register
	memo.setflag_C(0xFF - n < memo.reg[r]);
	unsigned char result = memo.reg[r] + n;
	memo.setflag_Z(result == 0);
	memo.reg[r] = result;
}

void cpu_instr::add_reg_c(unsigned char r, unsigned char n) {	// add data to register with carry
	int carry = memo.getflag_C();
	memo.setflag_N(false);
	memo.setflag_C(0xFF - n - carry < memo.reg[r]);
	unsigned char result = memo.reg[r] + n + carry;
	memo.setflag_Z(result == 0);
	memo.reg[r] = result;
}

void cpu_instr::sub_reg(unsigned char r, unsigned char n) {		// subtract data from register
	memo.setflag_Z(n == memo.reg[r]);
	memo.setflag_N(true);
	memo.setflag_C(n > memo.reg[r]);
	memo.reg[r] -= n;
}

void cpu_instr::sub_reg_c(unsigned char r, unsigned char n) {	// subtract data from register with carry
	int carry = memo.getflag_C();
	memo.setflag_Z(n == memo.reg[r] + carry);
	memo.setflag_N(true);
	memo.setflag_C(n > memo.reg[r] + carry);
	memo.reg[r] -= n + carry;
}

void cpu_instr::compare(unsigned char r, unsigned char n) {		// compare register to data
	memo.setflag_Z(n == memo.reg[r]);							// basically just sub() w/o the subtraction
	memo.setflag_N(true);
	memo.setflag_C(n > memo.reg[r]);
}

void cpu_instr::increment(unsigned char r) {					// increment register
	memo.reg[r]++;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
}
void cpu_instr::increment(unsigned short a) {					// increment at address
	memo.mem[a]++;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(false);
}

void cpu_instr::decrement(unsigned char r) {					// decrement register
	memo.reg[r]--;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(true);
}
void cpu_instr::decrement(unsigned short a) {					// decrement at address
	memo.mem[a]--;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(true);
}

// Logic instructions
void cpu_instr::and_reg(unsigned char r, unsigned char n) {	// logical and the register
	memo.reg[r] &= n;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
	memo.setflag_H(true);
	memo.setflag_C(false);
}

void cpu_instr::or_reg(unsigned char r, unsigned char n) {	// logical or the register
	memo.reg[r] |= n;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
	memo.setflag_H(false);
	memo.setflag_C(false);
}

void cpu_instr::xor_reg(unsigned char r, unsigned char n) {	// xor the register
	memo.reg[r] ^= n;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
	memo.setflag_H(false);
	memo.setflag_C(false);
}

void cpu_instr::complement_c() {							// toggle carry flag
	memo.setflag_C(!memo.getflag_C());
	memo.setflag_N(false);
	memo.setflag_H(false);
}

void cpu_instr::set_cflag(bool flag) {						// set carry flag
	memo.setflag_C(flag);
	memo.setflag_N(false);
	memo.setflag_H(false);
}

void cpu_instr::complement_a() {							// complement A register
	memo.reg[0] = ~memo.reg[0];
	memo.setflag_N(true);
	memo.setflag_H(true);
}

void cpu_instr::daa() {												// TODO: has to do w/ BCD
	nop();
}

// 16-bit arithmetic instructions
void cpu_instr::add_16(unsigned short r) {		// add 16-bit register (BC, DE, HL, SP) to HL
	memo.setflag_C(0xFFFF - r < memo.get_HL());
	unsigned short result = memo.get_HL() + r;
	memo.setflag_Z(result == 0);
	memo.setflag_N(false);
	memo.set_HL(result);
}

void cpu_instr::increment_16(unsigned char r) {	// increment 16-bit register
	switch (r) {
	case 2:
		memo.set_BC(memo.get_BC() + 1);
		break;
	case 4:
		memo.set_DE(memo.get_DE() + 1);
		break;
	case 6:
		memo.set_HL(memo.get_HL() + 1);
		break;
	case 8:
		memo.sp++;
		break;
	}
	memo.setflag_N(false);
}
void cpu_instr::decrement_16(unsigned char r) {	// decrement 16-bit register
	switch (r) {
	case 2:
		memo.set_BC(memo.get_BC() - 1);
		memo.setflag_Z(memo.get_BC() == 0);
		break;
	case 4:
		memo.set_DE(memo.get_DE() - 1);
		memo.setflag_Z(memo.get_DE() == 0);
		break;
	case 6:
		memo.set_HL(memo.get_HL() - 1);
		memo.setflag_Z(memo.get_HL() == 0);
		break;
	case 8:
		memo.sp--;
		memo.setflag_Z(memo.sp == 0);
		break;
	}
	memo.setflag_N(true);
}

void cpu_instr::add_sp(signed char data) {		// add signed immediate data to SP
	bool flag = (data >= 0) ? 0xFFFF - data < memo.sp : false;
	memo.setflag_C(flag);
	memo.sp += data;
}

void cpu_instr::load_HLSP(signed char data) {	// load SP + signed data to HL
	bool flag = (data >= 0) ? 0xFFFF - data < memo.sp : false;
	memo.setflag_C(flag);
	memo.set_HL(memo.sp + data);
}

// Control flow instructions
void cpu_instr::jump(unsigned short a) {				// jump to address
	memo.pc = a;
}

void cpu_instr::jump_cnd(bool c, unsigned short a) {	// conditional jump (C, Z, N && C, N && Z)
	if (c) {											
		memo.pc = a;
	}
}

void cpu_instr::jump_rel(signed char o) {				// jump relative to current position
	memo.pc += o;
}

void cpu_instr::call(unsigned short a) {				// function call
	push_nn(memo.pc);
	memo.pc = a;
}

void cpu_instr::call_cnd(bool c, unsigned short a) {	// conditonal function call
	if (c) {
		push_nn(memo.pc);
		memo.pc = a;
	}
}

void cpu_instr::ret() {									// return from function call
	memo.pc = pop_rr();
}

void cpu_instr::ret_cnd(bool c) {						// conditional return
	if (c) {
		memo.pc = pop_rr();
	}
}

void cpu_instr::reti() {											// TODO: return w/ interrupts
	nop();
}

void cpu_instr::halt() {											// TODO: stop clock until interrupt
	nop();
}

void cpu_instr::stop() {											// TODO: stop clock
	memo.read(); // by convention, STOP (0x10) is followed by 0x00
}

void cpu_instr::set_interrupts(bool f) {							// TODO: set interrupts flag
	// interrupts = f;
}

void cpu_instr::nop() {									// no operation
	// "this page intentionally left blank"
}

// Rotate and shift instructions
void  cpu_instr::rot_left(unsigned char r) {		// rotate register left
	unsigned char n = memo.reg[r];
	memo.reg[r] = n << 1;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
	memo.setflag_C(((n >> 7) & 0x01) == 1);
}

void  cpu_instr::rot_left(unsigned short a) {		// rotate mem addr left
	unsigned char n = memo.mem[a];
	memo.mem[a] = n << 1;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
	memo.setflag_C(((n >> 7) & 0x01) == 1);
}

void cpu_instr::rot_left_c(unsigned char r) {		// rotate register left thru carry
	unsigned char n = memo.reg[r];
	unsigned char msb = (n >> 7) & 0x01;
	n = n << 1;
	memo.getflag_C() ? n |= 0x01 : n &= 0xFE; // 0xFE = 0b11111110
	memo.reg[r] = n;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
	memo.setflag_C(msb);
}

void cpu_instr::rot_left_c(unsigned short a) {		// rotate mem addr left thru carry
	unsigned char n = memo.mem[a];
	unsigned char msb = (n >> 7) & 0x01;
	n = n << 1;
	memo.getflag_C() ? n |= 0x01 : n &= 0xFE; // 0xFE = 0b11111110
	memo.mem[a] = n;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
	memo.setflag_C(msb);
}

void  cpu_instr::rot_right(unsigned char r) {		// rotate register right
	unsigned char n = memo.reg[r];
	memo.setflag_C((n & 0x01) == 1);
	memo.reg[r] = n >> 1;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
}

void  cpu_instr::rot_right(unsigned short a) {		// rotate mem addr right
	unsigned char n = memo.mem[a];
	memo.setflag_C((n & 0x01) == 1);
	memo.mem[a] = n >> 1;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
}

void cpu_instr::rot_right_c(unsigned char r) {		// rotate register right thru carry
	unsigned char n = memo.reg[r];
	unsigned char lsb = n & 0x01;
	n = n >> 1;
	memo.getflag_C() ? n |= 0x80 : n &= 0x7F; // 0x80 = 0b10000000, 0x7F = 0b01111111
	memo.reg[r] = n;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
	memo.setflag_C(lsb);
}

void cpu_instr::rot_right_c(unsigned short a) {		// rotate mem addr right thru carry
	unsigned char n = memo.mem[a];
	unsigned char lsb = n & 0x01;
	n = n >> 1;
	memo.getflag_C() ? n |= 0x80 : n &= 0x7F; // 0x80 = 0b10000000, 0x7F = 0b01111111
	memo.mem[a] = n;
	memo.setflag_Z(0);
	memo.setflag_N(0);
	memo.setflag_H(0);
	memo.setflag_C(lsb);
}

void cpu_instr::swap_reg(unsigned char r) {			// swap high and low nybbles of reg
	unsigned char data = memo.reg[r];
	unsigned char high = (data >> 4) & 0x0F;
	data = (data << 4) & 0xF0;
	unsigned char result = data | high;
	memo.reg[r] = result;
	memo.setflag_Z(result == 0);
	memo.setflag_N(false);
	memo.setflag_C(false);
}

void cpu_instr::swap_addr(unsigned short a) {		// swap high and low nybbles at addr
	unsigned char data = memo.mem[a];
	unsigned char high = (data >> 4) & 0x0F;
	data = (data << 4) & 0xF0;
	unsigned char result = data | high;
	memo.mem[a] = result;
	memo.setflag_Z(result == 0);
	memo.setflag_N(false);
	memo.setflag_C(false);
}

void cpu_instr::shift_left(unsigned char r) {		// shift register left
	unsigned char msb = memo.reg[r] & 0x80;			// docs have this as arithmetic shift,
	memo.reg[r] = memo.reg[r] << 1;					// but theres no difference on left shift
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(0);
	memo.setflag_C(msb == 0x80);
}

void cpu_instr::shift_left(unsigned short a) {		// shift addr left
	unsigned char msb = memo.mem[a] & 0x80;
	memo.mem[a] = memo.mem[a] << 1;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(0);
	memo.setflag_C(msb == 0x80);
}

void cpu_instr::shift_right_a(unsigned char r) {	// shift reg right arithmetic
	unsigned char msb = memo.reg[r] & 0x80;
	unsigned char lsb = memo.reg[r] & 0x01;
	memo.reg[r] = (memo.reg[r] >> 1) | msb;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(0);
	memo.setflag_C(lsb == 0x80);
}

void cpu_instr::shift_right_a(unsigned short a) {	// shift addr right arithmetic
	unsigned char msb = memo.mem[a] & 0x80;
	unsigned char lsb = memo.mem[a] & 0x01;
	memo.mem[a] = (memo.mem[a] >> 1) | msb;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(0);
	memo.setflag_C(lsb == 0x80);
}

void cpu_instr::shift_right_l(unsigned char r) {	// shift reg right logical
	unsigned char lsb = memo.reg[r] & 0x01;
	memo.reg[r] = memo.reg[r] >> 1;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(0);
	memo.setflag_C(lsb == 0x80);
}

void cpu_instr::shift_right_l(unsigned short a) {	// shift addr right logical
	unsigned char lsb = memo.mem[a] & 0x01;
	memo.mem[a] - memo.mem[a] >> 1;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(0);
	memo.setflag_C(lsb == 0x80);
}

// Single-bit operations
void cpu_instr::bit_reg(unsigned char b, unsigned char r) {
	unsigned char bit = (memo.reg[r] >> b) & 0x01;
	memo.setflag_Z(bit);
	memo.setflag_N(0);
}

void cpu_instr::bit_addr(unsigned char b, unsigned short a) {
	unsigned char bit = (memo.mem[a] >> b) & 0x01;
	memo.setflag_Z(bit);
	memo.setflag_N(0);
}

void cpu_instr::set_bit_reg(unsigned char b, unsigned char r) {		// set bit b of register
	unsigned char mask = 0x01 << b;
	memo.reg[r] |= mask;
}

void cpu_instr::set_bit_addr(unsigned char b, unsigned short a) {	// set bit b at address
	unsigned char mask = 0x01 << b;
	memo.mem[a] |= mask;
}

void cpu_instr::reset_bit_reg(unsigned char b, unsigned char r) {	// reset bit b of register
	unsigned char mask = 0x01 << b;
	mask = ~mask;
	memo.reg[r] &= mask;
}

void cpu_instr::reset_bit_addr(unsigned char b, unsigned short a) {	// reset bit b at address
	unsigned char mask = 0x01 << b;
	mask = ~mask;
	memo.mem[a] &= mask;
}
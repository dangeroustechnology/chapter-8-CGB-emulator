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

void cpu_instr::load_air(unsigned char r) {						// load to addr from register (increment)
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

void cpu_instr::push_rr(unsigned char r) {							// push to stack
	unsigned char low = memo.reg[r + 1];
	unsigned char high = memo.reg[r];
	memo.stack[memo.sp] = low;
	memo.sp++;
	memo.stack[memo.sp] = high;
	memo.sp++;
}

void cpu_instr::push_nn(unsigned short d) {
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
// i still have to figure out exactly how to deal with Hf. some other time, perhaps
void cpu_instr::add_reg(unsigned char r, unsigned char n) {
	memo.setflag_C(0xFF - n < memo.reg[r]);
	unsigned char result = memo.reg[r] + n;
	memo.setflag_Z(result == 0);
	memo.reg[r] = result;
}

void cpu_instr::add_reg_c(unsigned char r, unsigned char n) {
	int carry = memo.getflag_C();
	memo.setflag_C(0xFF - n - carry < memo.reg[r]);
	memo.setflag_N(false);
	unsigned char result = memo.reg[r] + n + carry;
	memo.setflag_Z(result == 0);
	memo.reg[r] = result;
}

void cpu_instr::sub_reg(unsigned char r, unsigned char n) {
	if (n > memo.reg[r]) {
		memo.setflag_C(true);
	}
	else if (n == memo.reg[r]) {
		memo.setflag_Z(true);
	}
	else {
		memo.setflag_C(false);
		memo.setflag_Z(false);
	}
	memo.setflag_N(true);
	memo.reg[r] -= n;
}

void cpu_instr::sub_reg_c(unsigned char r, unsigned char n) {
	int carry = memo.getflag_C();
	if (n > memo.reg[r] + carry) {
		memo.setflag_C(true);
	}
	else if (n == memo.reg[r] + carry) {
		memo.setflag_Z(true);
	}
	else {
		memo.setflag_C(false);
		memo.setflag_Z(false);
	}
	memo.setflag_N(true);
	memo.reg[r] -= n + carry;
}

void cpu_instr::compare(unsigned char r, unsigned char n) {
	if (n > memo.reg[r]) {
		memo.setflag_C(true);
	}
	else if(n == memo.reg[r]) {
		memo.setflag_Z(true);
	}
	else {
		memo.setflag_C(false);
		memo.setflag_Z(false);
	}
	memo.setflag_N(true);
}

void cpu_instr::increment(unsigned char r) {
	memo.reg[r]++;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
}
void cpu_instr::increment(unsigned short a) {
	memo.mem[a]++;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(false);
}

void cpu_instr::decrement(unsigned char r) {
	memo.reg[r]--;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(true);
}
void cpu_instr::decrement(unsigned short a) {
	memo.mem[a]--;
	memo.setflag_Z(memo.mem[a] == 0);
	memo.setflag_N(true);
}

// Logic instructions
void cpu_instr::and_reg(unsigned char r, unsigned char n) {
	memo.reg[r] &= n;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
	memo.setflag_H(true);
	memo.setflag_C(false);
}

void cpu_instr::or_reg(unsigned char r, unsigned char n) {
	memo.reg[r] |= n;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
	memo.setflag_H(false);
	memo.setflag_C(false);
}

void cpu_instr::xor_reg(unsigned char r, unsigned char n) {
	memo.reg[r] ^= n;
	memo.setflag_Z(memo.reg[r] == 0);
	memo.setflag_N(false);
	memo.setflag_H(false);
	memo.setflag_C(false);
}

void cpu_instr::complement_c() {
	memo.setflag_C(!memo.getflag_C());
	memo.setflag_N(false);
	memo.setflag_H(false);
}

void cpu_instr::set_cflag(bool flag) {
	memo.setflag_C(flag);
	memo.setflag_N(false);
	memo.setflag_H(false);
}

void cpu_instr::complement_a() {
	memo.reg[0] = ~memo.reg[0];
	memo.setflag_N(true);
	memo.setflag_H(true);
}

void cpu_instr::daa() {									// some bcd thing, i think
	nop();
}

// 16-bit arithmetic instructions
void cpu_instr::add_16(unsigned short r) {				// r = bd, de, hl, or sp
	memo.setflag_C(0xFFFF - r < memo.get_HL());
	unsigned short result = memo.get_HL() + r;
	memo.setflag_Z(result == 0);
	memo.setflag_N(false);
	memo.set_HL(result);

}

void cpu_instr::increment_16(unsigned char r) {
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
void cpu_instr::decrement_16(unsigned char r) {
	switch (r) {
	case 0:	// bad workaround lmao
		memo.sp--;
		memo.setflag_Z(memo.sp == 0);
		break;
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
	}
	memo.setflag_N(true);
}

void cpu_instr::add_sp(signed char data) {		// TODO: the gd flag management you lazy child
	memo.sp += data;
}

void cpu_instr::load_HLSP(signed char data) {	// TODO: see above
	memo.set_HL(memo.sp + data);
}

// Control flow instructions
void cpu_instr::jump(unsigned short a) {
	memo.pc = a;
}

void cpu_instr::jump_cnd(bool c, unsigned short a) {	// the docs on this one are a bit confusing but it looks as tho
	if (c) {											// the condition can be c, n && c, z, or n && z
		memo.pc = a;
	}
}

void cpu_instr::jump_rel(signed char o) {
	memo.pc += o;
}

void cpu_instr::call(unsigned short a) {
	push_nn(memo.pc);
	memo.pc = a;
}

void cpu_instr::call_cnd(bool c, unsigned short a) {
	if (c) {
		push_nn(memo.pc);
		memo.pc = a;
	}
}

void cpu_instr::ret() {
	memo.pc = pop_rr();
}

void cpu_instr::ret_cnd(bool c) {
	if (c) {
		memo.pc = pop_rr();
	}
}

void cpu_instr::reti() {
	// ugh, dont even get me started
}

void cpu_instr::halt() {											// TODO
	nop();
}

void cpu_instr::stop() {											// TODO
	nop();
}

void cpu_instr::set_interrupts(bool f) {
	// interrupts = f;
}

void cpu_instr::nop() {
	memo.pc++;
}
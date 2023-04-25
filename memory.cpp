#include "memory.h"

using namespace std;

memory::memory() {
    for (int i = 0; i < 65536; i++) {
        mem[i] = 0;
    }
    for (int i = 0; i < 8; i++) {
        reg[i] = 0;
    }
    for (int i = 0; i < 64; i++) {
        stack[i] = 0;
    }
}

void memory::fill(string filename) {
    fr.read_in_file(filename, mem);
}

// 16-bit register getters
unsigned short memory::get_AF() {
    unsigned short high = reg[0];
    high = high << 8;
    unsigned char low = 0;
    for (int i = 0; i < 4; i++) {
        flags[i] == true ? low |= 0x1 : low |= 0x0;
        low = low << 1;
    }
    low = low << 4; // flags should be in upper nybble of low
    unsigned short af = high | low;
    return af;
}

unsigned short memory::get_BC() {
    unsigned short bc = reg[2];
    bc = bc << 8;
    bc |= reg[3];
    return bc;
}

unsigned short memory::get_DE() {
    unsigned short de = reg[4];
    de = de << 8;
    de |= reg[5];
    return de;
}

unsigned short memory::get_HL() {
    unsigned short hl = reg[6];
    hl = hl << 8;
    hl |= reg[7];
    return hl;
}

// 16-bit register setters
void memory::set_AF(unsigned short data) {
    unsigned char a = (data >> 8) & 0xFF;
    reg[0] = a;
    unsigned char f = (data >> 4) & 0x0F; // flags are in upper nybble of F
    for (int i = 0; i < 4; i++) {
        (f & 0x1) == 1 ? flags[i] = true : flags[i] = false;
        f = f >> 1;
    }
}

void memory::set_BC(unsigned short data) {
    unsigned char high = (data & 0xFF00) >> 8;
    unsigned char low = data & 0x00FF;
    reg[2] = high;
    reg[3] = low;
}
void memory::set_DE(unsigned short data) {
    unsigned char high = (data & 0xFF00) >> 8;
    unsigned char low = data & 0x00FF;
    reg[4] = high;
    reg[5] = low;
}
void memory::set_HL(unsigned short data) {
    unsigned char high = (data & 0xFF00) >> 8;
    unsigned char low = data & 0x00FF;
    reg[6] = high;
    reg[7] = low;
}

// flag getters
bool memory::getflag_Z() {
    return flags[0];
}

bool memory::getflag_N() {
    return flags[1];
}

bool memory::getflag_H() {
    return flags[2];
}

bool memory::getflag_C() {
    return flags[3];
}

// flag setters
void memory::setflag_Z(bool flag) {
    flags[0] = flag;
}

void memory::setflag_N(bool flag) {
    flags[1] = flag;
}

void memory::setflag_H(bool flag) {
    flags[2] = flag;
}

void memory::setflag_C(bool flag) {
    flags[3] = flag;
}

unsigned char memory::read() {  // read a byte and increment PC
    return mem[pc++];
}

unsigned char* memory::dump() { // return a copy of memory for dumping
    return mem;
}
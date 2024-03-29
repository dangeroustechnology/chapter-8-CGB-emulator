// Chapter 8 CGB Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <bitset>
#include "file_reader.h"
#include "cpu_instr.h"
#include "memory.h"

using namespace std;

int main(int argc, char* argv[])
{
    ofstream output("gameboy_emulator_output.txt");
    const unsigned char A = 0;
    const unsigned char B = 2;
    const unsigned char C = 3;
    const unsigned char D = 4;
    const unsigned char E = 5;
    const unsigned char H = 6;
    const unsigned char L = 7;
    const unsigned char SP = 8;
    string filename = argv[1] ? argv[1] : ".\\test";
    cpu_instr cpu;
    cpu.memo.fill(filename);
    bool clock = true;
    while (clock) {
        // var declarations for use in instructions
        unsigned char opcode = cpu.memo.read();
        unsigned int op_int = opcode;
        unsigned short addr = 0;
        unsigned char lsb = 0;
        unsigned short data = 0;
        signed short s_data = 0;
        signed char offset = 0;

        switch (opcode) {
        case 0x00:
            output << cpu.memo.pc - 1 << " " << op_int << " NOP" << endl;
            cpu.nop();
            break;
        case 0x01:
            output << cpu.memo.pc - 1 << " " << op_int << " LD BC NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(B, data);
            break;
        case 0x02:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (BC) A" << endl;
            cpu.load_ar(cpu.memo.get_BC(), cpu.memo.reg[A]);
            break;
        case 0x03:
            output << cpu.memo.pc - 1 << " " << op_int << " INC BC" << endl;
            cpu.increment_16(B);
            break;
        case 0x04:
            output << cpu.memo.pc - 1 << " " << op_int << " INC B" << endl;
            cpu.increment(B);
            break;
        case 0x05:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC B" << endl;
            cpu.decrement(B);
            break;
        case 0x06:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B N" << endl;
            cpu.load_rn(2, cpu.memo.read());
            break;
        case 0x07:
            output << cpu.memo.pc - 1 << " " << op_int << " RLCA" << endl;
            cpu.rot_left_c(A);
            break;
        case 0x08:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (NN) SP" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_nnsp(addr);
            break;
        case 0x09:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD HL BC" << endl;
            cpu.add_16(cpu.memo.get_BC());
            break;
        case 0x0A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A (BC)" << endl;
            cpu.load_ra(A, cpu.memo.mem[cpu.memo.get_BC()]);
            break;
        case 0x0B:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC BC" << endl;
            cpu.decrement_16(B);
            break;
        case 0x0C:
            output << cpu.memo.pc - 1 << " " << op_int << " INC C" << endl;
            cpu.increment(C);
            break;
        case 0x0D:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC C" << endl;
            cpu.decrement(C);
            break;
        case 0x0E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C N" << endl;
            cpu.load_rn(C, cpu.memo.read());
            break;
        case 0x0F:
            output << cpu.memo.pc - 1 << " " << op_int << " RRCA" << endl;
            cpu.rot_right_c(A);
            break;
        case 0x10:
            output << cpu.memo.pc - 1 << " " << op_int << " STOP" << endl;
            cpu.stop();
            clock = false; // tho this isnt properly implemented, i use it in test files
            break;
        case 0x11:
            output << cpu.memo.pc - 1 << " " << op_int << " LD DE NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(D, data);
            break;
        case 0x12:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (DE) A" << endl;
            cpu.load_ar(cpu.memo.get_DE(), A);
            break;
        case 0x13:
            output << cpu.memo.pc - 1 << " " << op_int << " INC DE" << endl;
            cpu.increment_16(D);
            break;
        case 0x14:
            output << cpu.memo.pc - 1 << " " << op_int << " INC D" << endl;
            cpu.increment(D);
            break;
        case 0x15:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC D" << endl;
            cpu.decrement(D);
            break;
        case 0x16:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D N" << endl;
            cpu.load_rn(D, cpu.memo.read());
            break;
        case 0x17:
            output << cpu.memo.pc - 1 << " " << op_int << " RLA" << endl;
            cpu.rot_left(A);
            break;
        case 0x18:
            output << cpu.memo.pc - 1 << " " << op_int << " JR O" << endl;
            cpu.jump_rel(cpu.memo.read());
            break;
        case 0x19:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD HL DE" << endl;
            cpu.add_16(cpu.memo.get_DE());
            break;
        case 0x1A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A (DE)" << endl;
            cpu.load_ra(A, cpu.memo.get_DE());
            break;
        case 0x1B:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC DE" << endl;
            cpu.decrement_16(D);
            break;
        case 0x1C:
            output << cpu.memo.pc - 1 << " " << op_int << " INC E" << endl;
            cpu.increment(E);
            break;
        case 0x1D:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC E" << endl;
            cpu.decrement(E);
            break;
        case 0x1E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E N" << endl;
            cpu.load_rn(E, cpu.memo.read());
            break;
        case 0x1F:
            output << cpu.memo.pc - 1 << " " << op_int << " RRA" << endl;
            cpu.rot_right(A);
            break;
        case 0x20:
            output << cpu.memo.pc - 1 << " " << op_int << " JR NZ O" << endl;
            offset = cpu.memo.read();
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd((cpu.memo.getflag_N() && cpu.memo.getflag_Z()), addr);
            break;
        case 0x21:
            output << cpu.memo.pc - 1 << " " << op_int << " LD HL NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(H, data);
            break;
        case 0x22:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL+) A" << endl;
            cpu.load_air(A);
            break;
        case 0x23:
            output << cpu.memo.pc - 1 << " " << op_int << " INC HL" << endl;
            cpu.increment_16(H);
            break;
        case 0x24:
            output << cpu.memo.pc - 1 << " " << op_int << " INC H" << endl;
            cpu.increment(H);
            break;
        case 0x25:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC H" << endl;
            cpu.decrement(H);
            break;
        case 0x26:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H N" << endl;
            cpu.load_rn(H, cpu.memo.read());
            break;
        case 0x27:
            output << cpu.memo.pc - 1 << " " << op_int << " DAA" << endl;
            cpu.daa();
            break;
        case 0x28:
            output << cpu.memo.pc - 1 << " " << op_int << " JR Z O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd(cpu.memo.getflag_Z(), addr);
            break;
        case 0x29:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD HL HL" << endl;
            cpu.add_16(cpu.memo.get_HL());
            break;
        case 0x2A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A (HL+)" << endl;
            cpu.load_rai(A);
            break;
        case 0x2B:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC HL" << endl;
            cpu.decrement_16(H);
            break;
        case 0x2C:
            output << cpu.memo.pc - 1 << " " << op_int << " INC L" << endl;
            cpu.increment(L);
            break;
        case 0x2D:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC L" << endl;
            cpu.decrement(L);
            break;
        case 0x2E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L N" << endl;
            cpu.load_rn(L, cpu.memo.read());
            break;
        case 0x2F:
            output << cpu.memo.pc - 1 << " " << op_int << " CPL" << endl;
            cpu.complement_a();
            output << bitset<8>(cpu.memo.reg[A]) << endl;
            break;
        case 0x30:
            output << cpu.memo.pc - 1 << " " << op_int << " JR NC O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd((cpu.memo.getflag_N() && cpu.memo.getflag_C()), addr);
            break;
        case 0x31:
            output << cpu.memo.pc - 1 << " " << op_int << " LD SP NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(SP, data);
            break;
        case 0x32:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL-) A" << endl;
            cpu.load_adr(A);
            break;
        case 0x33:
            output << cpu.memo.pc - 1 << " " << op_int << " INC SP" << endl;
            cpu.increment_16(SP);
            break;
        case 0x34:
            output << cpu.memo.pc - 1 << " " << op_int << " INC (HL)" << endl;
            cpu.increment(cpu.memo.get_HL());
            break;
        case 0x35:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC (HL)" << endl;
            cpu.decrement(cpu.memo.get_HL());
            break;
        case 0x36:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) N" << endl;
            cpu.load_an(cpu.memo.get_HL(), cpu.memo.read());
            break;
        case 0x37:
            output << cpu.memo.pc - 1 << " " << op_int << " SCF" << endl;
            cpu.set_cflag(true);
            break;
        case 0x38:
            output << cpu.memo.pc - 1 << " " << op_int << " JR C O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0x39:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD HL SP" << endl;
            cpu.add_16(cpu.memo.sp);
            break;
        case 0x3A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A (HL-)" << endl;
            cpu.load_rad(A);
            break;
        case 0x3B:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC SP" << endl;
            cpu.decrement_16(SP);
            break;
        case 0x3C:
            output << cpu.memo.pc - 1 << " " << op_int << " INC A" << endl;
            cpu.increment(A);
            break;
        case 0x3D:
            output << cpu.memo.pc - 1 << " " << op_int << " DEC A" << endl;
            cpu.decrement(A);
            break;
        case 0x3E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A N" << endl;
            cpu.load_rn(A, cpu.memo.read());
            break;
        case 0x3F:
            output << cpu.memo.pc - 1 << " " << op_int << " CCF" << endl;
            cpu.complement_c();
            break;
        case 0x40: 
            output << cpu.memo.pc - 1 << " " << op_int << " LD B B" << endl;
            cpu.load_rr(B, B);
            break;
        case 0x41: 
            output << cpu.memo.pc - 1 << " " << op_int << " LD B C" << endl;
            cpu.load_rr(B, C);
            break;
        case 0x42:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B D" << endl;
            cpu.load_rr(B, D);
            break;
        case 0x43:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B E" << endl;
            cpu.load_rr(B, E);
            break;
        case 0x44:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B H" << endl;
            cpu.load_rr(B, H);
            break;
        case 0x45:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B L" << endl;
            cpu.load_rr(B, L);
            break;
        case 0x46:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B (HL)" << endl;
            cpu.load_ra(B, cpu.memo.get_HL());
            break;
        case 0x47:
            output << cpu.memo.pc - 1 << " " << op_int << " LD B A" << endl;
            cpu.load_rr(B, A);
            break;
        case 0x48:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C B" << endl;
            cpu.load_rr(C, B);
            break;
        case 0x49:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C C" << endl;
            cpu.load_rr(C, C);
            break;
        case 0x4A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C D" << endl;
            cpu.load_rr(C, D);
            break;
        case 0x4B:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C E" << endl;
            cpu.load_rr(C, E);
            break;
        case 0x4C:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C H" << endl;
            cpu.load_rr(C, H);
            break;
        case 0x4D:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C L" << endl;
            cpu.load_rr(C, L);
            break;
        case 0x4E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C (HL)" << endl;
            cpu.load_ra(C, cpu.memo.get_HL());
            break;
        case 0x4F:
            output << cpu.memo.pc - 1 << " " << op_int << " LD C A" << endl;
            cpu.load_rr(C, A);
            break;
        case 0x50:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D B" << endl;
            cpu.load_rr(D, B);
            break;
        case 0x51:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D C" << endl;
            cpu.load_rr(D, C);
            break;
        case 0x52:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D D" << endl;
            cpu.load_rr(D, D);
            break;
        case 0x53:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D E" << endl;
            cpu.load_rr(D, E);
            break;
        case 0x54:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D H" << endl;
            cpu.load_rr(D, H);
            break;
        case 0x55:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D L" << endl;
            cpu.load_rr(D, L);
            break;
        case 0x56:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D (HL)" << endl;
            cpu.load_ra(D, cpu.memo.get_HL());
            break;
        case 0x57:
            output << cpu.memo.pc - 1 << " " << op_int << " LD D A" << endl;
            cpu.load_rr(D, A);
            break;
        case 0x58:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E B" << endl;
            cpu.load_rr(E, B);
            break;
        case 0x59:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E C" << endl;
            cpu.load_rr(E, C);
            break;
        case 0x5A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E D" << endl;
            cpu.load_rr(E, D);
            break;
        case 0x5B:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E E" << endl;
            cpu.load_rr(E, E);
            break;
        case 0x5C:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E H" << endl;
            cpu.load_rr(E, H);
            break;
        case 0x5D:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E L" << endl;
            cpu.load_rr(E, L);
            break;
        case 0x5E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E (HL)" << endl;
            cpu.load_ra(E, cpu.memo.get_HL());
            break;
        case 0x5F:
            output << cpu.memo.pc - 1 << " " << op_int << " LD E A" << endl;
            cpu.load_rr(E, A);
            break;
        case 0x60:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H B" << endl;
            cpu.load_rr(H, B);
            break;
        case 0x61:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H C" << endl;
            cpu.load_rr(H, C);
            break;
        case 0x62:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H D" << endl;
            cpu.load_rr(H, D);
            break;
        case 0x63:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H E" << endl;
            cpu.load_rr(H, E);
            break;
        case 0x64:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H H" << endl;
            cpu.load_rr(H, H);
            break;
        case 0x65:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H L" << endl;
            cpu.load_rr(H, L);
            break;
        case 0x66:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H (HL)" << endl;
            cpu.load_ra(H, cpu.memo.get_HL());
            break;
        case 0x67:
            output << cpu.memo.pc - 1 << " " << op_int << " LD H A" << endl;
            cpu.load_rr(H, A);
            break;
        case 0x68:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L B" << endl;
            cpu.load_rr(L, B);
            break;
        case 0x69:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L C" << endl;
            cpu.load_rr(L, C);
            break;
        case 0x6A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L D" << endl;
            cpu.load_rr(L, D);
            break;
        case 0x6B:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L E" << endl;
            cpu.load_rr(L, E);
            break;
        case 0x6C:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L H" << endl;
            cpu.load_rr(L, H);
            break;
        case 0x6D:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L L" << endl;
            cpu.load_rr(L, L);
            break;
        case 0x6E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L (HL)" << endl;
            cpu.load_ra(L, cpu.memo.get_HL());
            break;
        case 0x6F:
            output << cpu.memo.pc - 1 << " " << op_int << " LD L A" << endl;
            cpu.load_rr(L, A);
            break;
        case 0x70:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) B" << endl;
            cpu.load_ar(cpu.memo.get_HL(), B);
            break;
        case 0x71:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) C" << endl;
            cpu.load_ar(cpu.memo.get_HL(), C);
            break;
        case 0x72:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) D" << endl;
            cpu.load_ar(cpu.memo.get_HL(), D);
            break;
        case 0x73:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) E" << endl;
            cpu.load_ar(cpu.memo.get_HL(), E);
            break;
        case 0x74:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) H" << endl;
            cpu.load_ar(cpu.memo.get_HL(), H);
            break;
        case 0x75:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) L" << endl;
            cpu.load_ar(cpu.memo.get_HL(), L);
            break;
        case 0x76:
            output << cpu.memo.pc - 1 << " " << op_int << " HALT" << endl;
            cpu.halt();
            break;
        case 0x77:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (HL) A" << endl;
            cpu.load_ar(cpu.memo.get_HL(), A);
            break;
        case 0x78:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A B" << endl;
            cpu.load_rr(A, B);
            break;
        case 0x79:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A C" << endl;
            cpu.load_rr(A, C);
            break;
        case 0x7A:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A D" << endl;
            cpu.load_rr(A, D);
            break;
        case 0x7B:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A E" << endl;
            cpu.load_rr(A, E);
            break;
        case 0x7C:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A H" << endl;
            cpu.load_rr(A, H);
            break;
        case 0x7D:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A L" << endl;
            cpu.load_rr(A, L);
            break;
        case 0x7E:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A (HL)" << endl;
            cpu.load_ra(A, cpu.memo.get_HL());
            break;
        case 0x7F:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A A" << endl;
            cpu.load_rr(A, A);
            break;
        case 0x80:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A B" << endl;
            cpu.add_reg(A, cpu.memo.reg[B]);
            break;
        case 0x81:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A C" << endl;
            cpu.add_reg(A, cpu.memo.reg[C]);
            break;
        case 0x82:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A D" << endl;
            cpu.add_reg(A, cpu.memo.reg[D]);
            break;
        case 0x83:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A E" << endl;
            cpu.add_reg(A, cpu.memo.reg[E]);
            break;
        case 0x84:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A H" << endl;
            cpu.add_reg(A, cpu.memo.reg[H]);
            break;
        case 0x85:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A L" << endl;
            cpu.add_reg(A, cpu.memo.reg[L]);
            break;
        case 0x86:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A (HL)" << endl;
            cpu.add_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x87:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A A" << endl;
            cpu.add_reg(A, cpu.memo.reg[A]);
            break;
        case 0x88:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A B" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x89:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A C" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8A:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A D" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8B:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A E" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8C:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A H" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8D:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A L" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8E:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A (HL)" << endl;
            cpu.add_reg_c(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x8F:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A A" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x90:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A B" << endl;
            cpu.sub_reg(A, cpu.memo.reg[B]);
            break;
        case 0x91:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A C" << endl;
            cpu.sub_reg(A, cpu.memo.reg[C]);
            break;
        case 0x92:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A D" << endl;
            cpu.sub_reg(A, cpu.memo.reg[D]);
            break;
        case 0x93:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A E" << endl;
            cpu.sub_reg(A, cpu.memo.reg[E]);
            break;
        case 0x94:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A H" << endl;
            cpu.sub_reg(A, cpu.memo.reg[H]);
            break;
        case 0x95:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A L" << endl;
            cpu.sub_reg(A, cpu.memo.reg[L]);
            break;
        case 0x96:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A (HL)" << endl;
            cpu.sub_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x97:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB A A" << endl;
            cpu.sub_reg(A, cpu.memo.reg[A]);
            break;
        case 0x98:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A B" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x99:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A C" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9A:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A D" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9B:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A E" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9C:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A H" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9D:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A L" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9E:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A (HL)" << endl;
            cpu.sub_reg_c(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x9F:
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A A" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[A]);
            break;
        case 0xA0:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A B" << endl;
            cpu.and_reg(A, cpu.memo.reg[B]);
            break;
        case 0xA1:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A C" << endl;
            cpu.and_reg(A, cpu.memo.reg[C]);
            break;
        case 0xA2:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A D" << endl;
            cpu.and_reg(A, cpu.memo.reg[D]);
            output << bitset<8>(cpu.memo.reg[A]) << endl;
            break;
        case 0xA3:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A E" << endl;
            cpu.and_reg(A, cpu.memo.reg[E]);
            break;
        case 0xA4:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A H" << endl;
            cpu.and_reg(A, cpu.memo.reg[H]);
            break;
        case 0xA5:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A L" << endl;
            cpu.and_reg(A, cpu.memo.reg[L]);
            break;
        case 0xA6:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A (HL)" << endl;
            cpu.and_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xA7:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A A" << endl;
            cpu.and_reg(A, cpu.memo.reg[A]);
            break;
        case 0xA8:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A B" << endl;
            cpu.xor_reg(A, cpu.memo.reg[B]);
            break;
        case 0xA9:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A C" << endl;
            cpu.xor_reg(A, cpu.memo.reg[C]);
            break;
        case 0xAA:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A D" << endl;
            cpu.xor_reg(A, cpu.memo.reg[D]);
            break;
        case 0xAB:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A E" << endl;
            cpu.xor_reg(A, cpu.memo.reg[E]);
            break;
        case 0xAC:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A H" << endl;
            cpu.xor_reg(A, cpu.memo.reg[H]);
            break;
        case 0xAD:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A L" << endl;
            cpu.xor_reg(A, cpu.memo.reg[L]);
            output << bitset<8>(cpu.memo.reg[A]) << endl;
            break;
        case 0xAE:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A (HL)" << endl;
            cpu.xor_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xAF:
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A A" << endl;
            cpu.xor_reg(A, cpu.memo.reg[A]);
            break;
        case 0xB0:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A B" << endl;
            cpu.or_reg(A, cpu.memo.reg[B]);
            break;
        case 0xB1:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A C" << endl;
            cpu.or_reg(A, cpu.memo.reg[C]);
            break;
        case 0xB2:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A D" << endl;
            cpu.or_reg(A, cpu.memo.reg[D]);
            break;
        case 0xB3:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A E" << endl;
            cpu.or_reg(A, cpu.memo.reg[E]);
            break;
        case 0xB4:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A H" << endl;
            cpu.or_reg(A, cpu.memo.reg[H]);
            break;
        case 0xB5:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A L" << endl;
            cpu.or_reg(A, cpu.memo.reg[L]);
            break;
        case 0xB6:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A (HL)" << endl;
            cpu.or_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xB7:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A A" << endl;
            cpu.or_reg(A, cpu.memo.reg[A]);
            break;
        case 0xB8:
            output << cpu.memo.pc - 1 << " " << op_int << " CP B" << endl;
            cpu.compare(A, cpu.memo.reg[B]);
            break;
        case 0xB9:
            output << cpu.memo.pc - 1 << " " << op_int << " CP C" << endl;
            cpu.compare(A, cpu.memo.reg[C]);
            break;
        case 0xBA:
            output << cpu.memo.pc - 1 << " " << op_int << " CP D" << endl;
            cpu.compare(A, cpu.memo.reg[D]);
            break;
        case 0xBB:
            output << cpu.memo.pc - 1 << " " << op_int << " CP E" << endl;
            cpu.compare(A, cpu.memo.reg[E]);
            break;
        case 0xBC:
            output << cpu.memo.pc - 1 << " " << op_int << " CP H" << endl;
            cpu.compare(A, cpu.memo.reg[H]);
            break;
        case 0xBD:
            output << cpu.memo.pc - 1 << " " << op_int << " CP L" << endl;
            cpu.compare(A, cpu.memo.reg[L]);
            break;
        case 0xBE:
            output << cpu.memo.pc - 1 << " " << op_int << " CP (HL)" << endl;
            cpu.compare(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xBF:
            output << cpu.memo.pc - 1 << " " << op_int << " CP A" << endl;
            cpu.compare(A, cpu.memo.reg[A]);
            break;
        case 0xC0:
            output << cpu.memo.pc - 1 << " " << op_int << " RET NZ" << endl;
            cpu.ret_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_Z());
            break;
        case 0xC1:
            output << cpu.memo.pc - 1 << " " << op_int << " POP BC" << endl;
            cpu.memo.set_BC(cpu.pop_rr());
            break;
        case 0xC2:
            output << cpu.memo.pc - 1 << " " << op_int << " JP NZ ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_Z(), addr);
            break;
        case 0xC3:
            output << cpu.memo.pc - 1 << " " << op_int << " JP ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump(addr);
            break;
        case 0xC4:
            output << cpu.memo.pc - 1 << " " << op_int << " CALL NZ ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_Z(), addr);
            break;
        case 0xC5:
            output << cpu.memo.pc - 1 << " " << op_int << " PUSH BC" << endl;
            cpu.push_rr(B);
            break;
        case 0xC6:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD A N" << endl;
            cpu.add_reg(A, cpu.memo.read());
            break;
        case 0xC7:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 00" << endl;
            cpu.call(0x0);
            break;
        case 0xC8:
            output << cpu.memo.pc - 1 << " " << op_int << " RET Z" << endl;
            cpu.ret_cnd(cpu.memo.getflag_Z());
            break;
        case 0xC9:
            output << cpu.memo.pc - 1 << " " << op_int << " RET" << endl;
            cpu.ret();
            break;
        case 0xCA:
            output << cpu.memo.pc - 1 << " " << op_int << " JP Z ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_Z(), addr);
            break;
        case 0xCB: // hope you're ready to double the size of the switch statement!
            output << cpu.memo.pc - 1 << " " << op_int << " PREFIX" << endl;
            {
                unsigned char prefix = cpu.memo.read();
                switch (prefix) {
                case 0x00:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC B" << endl;
                    cpu.rot_left_c(B);
                    break;
                case 0x01:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC C" << endl;
                    cpu.rot_left_c(C);
                    break;
                case 0x02:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC D" << endl;
                    cpu.rot_left_c(D);
                    break;
                case 0x03:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC E" << endl;
                    cpu.rot_left_c(E);
                    break;
                case 0x04:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC H" << endl;
                    cpu.rot_left_c(H);
                    break;
                case 0x05:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC L" << endl;
                    cpu.rot_left_c(L);
                    break;
                case 0x06:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC (HL)" << endl;
                    cpu.rot_left_c(cpu.memo.get_HL());
                    break;
                case 0x07:
                    output << cpu.memo.pc - 1 << " " << op_int << " RLC A" << endl;
                    cpu.rot_left_c(A);
                    break;
                case 0x08:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC B" << endl;
                    cpu.rot_right_c(B);
                    break;
                case 0x09:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC C" << endl;
                    cpu.rot_right_c(C);
                    break;
                case 0x0A:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC D" << endl;
                    cpu.rot_right_c(D);
                    break;
                case 0x0B:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC E" << endl;
                    cpu.rot_right_c(E);
                    break;
                case 0x0C:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC H" << endl;
                    cpu.rot_right_c(H);
                    break;
                case 0x0D:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC L" << endl;
                    cpu.rot_right_c(L);
                    break;
                case 0x0E:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC (HL)" << endl;
                    cpu.rot_right_c(cpu.memo.get_HL());
                    break;
                case 0x0F:
                    output << cpu.memo.pc - 1 << " " << op_int << " RRC A" << endl;
                    cpu.rot_right_c(A);
                    break;
                case 0x10:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL B" << endl;
                    cpu.rot_left(B);
                    break;
                case 0x11:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL C" << endl;
                    cpu.rot_left(C);
                    break;
                case 0x12:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL D" << endl;
                    cpu.rot_left(D);
                    break;
                case 0x13:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL E" << endl;
                    cpu.rot_left(E);
                    break;
                case 0x14:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL H" << endl;
                    cpu.rot_left(H);
                    break;
                case 0x15:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL L" << endl;
                    cpu.rot_left(L);
                    break;
                case 0x16:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL (HL)" << endl;
                    cpu.rot_left(cpu.memo.get_HL());
                    break;
                case 0x17:
                    output << cpu.memo.pc - 1 << " " << op_int << " RL A" << endl;
                    cpu.rot_left(A);
                    break;
                case 0x18:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR B" << endl;
                    cpu.rot_right(B);
                    break;
                case 0x19:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR C" << endl;
                    cpu.rot_right(C);
                    break;
                case 0x1A:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR D" << endl;
                    cpu.rot_right(D);
                    break;
                case 0x1B:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR E" << endl;
                    cpu.rot_right(E);
                    break;
                case 0x1C:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR H" << endl;
                    cpu.rot_right(H);
                    break;
                case 0x1D:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR L" << endl;
                    cpu.rot_right(L);
                    break;
                case 0x1E:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR (HL)" << endl;
                    cpu.rot_right(cpu.memo.get_HL());
                    break;
                case 0x1F:
                    output << cpu.memo.pc - 1 << " " << op_int << " RR A" << endl;
                    cpu.rot_right(A);
                    break;
                case 0x20:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA B" << endl;
                    cpu.shift_left(B);
                    break;
                case 0x21:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA C" << endl;
                    cpu.shift_left(C);
                    break;
                case 0x22:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA D" << endl;
                    cpu.shift_left(D);
                    break;
                case 0x23:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA E" << endl;
                    cpu.shift_left(E);
                    break;
                case 0x24:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA H" << endl;
                    cpu.shift_left(H);
                    break;
                case 0x25:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA L" << endl;
                    cpu.shift_left(L);
                    break;
                case 0x26:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA (HL)" << endl;
                    cpu.shift_left(cpu.memo.get_HL());
                    break;
                case 0x27:
                    output << cpu.memo.pc - 1 << " " << op_int << " SLA A" << endl;
                    cpu.shift_left(A);
                    output << bitset<8>(cpu.memo.reg[A]) << endl;
                    break;
                case 0x28:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA B" << endl;
                    cpu.shift_right_a(B);
                    break;
                case 0x29:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA C" << endl;
                    cpu.shift_right_a(C);
                    break;
                case 0x2A:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA D" << endl;
                    cpu.shift_right_a(D);
                    break;
                case 0x2B:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA E" << endl;
                    cpu.shift_right_a(E);
                    break;
                case 0x2C:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA H" << endl;
                    cpu.shift_right_a(H);
                    break;
                case 0x2D:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA L" << endl;
                    cpu.shift_right_a(L);
                    break;
                case 0x2E:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA (HL)" << endl;
                    cpu.shift_right_a(cpu.memo.get_HL());
                    break;
                case 0x2F:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRA A" << endl;
                    cpu.shift_right_a(A);
                    output << bitset<8>(cpu.memo.reg[A]) << endl;
                    break;
                case 0x30:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP B" << endl;
                    cpu.swap_reg(B);
                    break;
                case 0x31:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP C" << endl;
                    cpu.swap_reg(C);
                    break;
                case 0x32:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP D" << endl;
                    cpu.swap_reg(D);
                    break;
                case 0x33:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP E" << endl;
                    cpu.swap_reg(E);
                    break;
                case 0x34:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP H" << endl;
                    cpu.swap_reg(H);
                    break;
                case 0x35:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP L" << endl;
                    cpu.swap_reg(L);
                    break;
                case 0x36:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP (HL)" << endl;
                    cpu.swap_addr(cpu.memo.get_HL());
                    break;
                case 0x37:
                    output << cpu.memo.pc - 1 << " " << op_int << " SWAP A" << endl;
                    cpu.swap_reg(A);
                    output << bitset<8>(cpu.memo.reg[A]) << endl;
                    break;
                case 0x38:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL B" << endl;
                    cpu.shift_right_l(B);
                    break;
                case 0x39:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL C" << endl;
                    cpu.shift_right_l(C);
                    break;
                case 0x3A:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL D" << endl;
                    cpu.shift_right_l(D);
                    break;
                case 0x3B:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL E" << endl;
                    cpu.shift_right_l(E);
                    break;
                case 0x3C:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL H" << endl;
                    cpu.shift_right_l(H);
                    break;
                case 0x3D:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL L" << endl;
                    cpu.shift_right_l(L);
                    break;
                case 0x3E:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL (HL)" << endl;
                    cpu.shift_right_l(cpu.memo.get_HL());
                    break;
                case 0x3F:
                    output << cpu.memo.pc - 1 << " " << op_int << " SRL A" << endl;
                    cpu.shift_right_l(A);
                    output << bitset<8>(cpu.memo.reg[A]) << endl;
                    break;
                case 0x40:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 B" << endl;
                    cpu.bit_reg(0, B);
                    break;
                case 0x41:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 C" << endl;
                    cpu.bit_reg(0, C);
                    break;
                case 0x42:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 D" << endl;
                    cpu.bit_reg(0, D);
                    break;
                case 0x43:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 E" << endl;
                    cpu.bit_reg(0, E);
                    break;
                case 0x44:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 H" << endl;
                    cpu.bit_reg(0, H);
                    break;
                case 0x45:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 L" << endl;
                    cpu.bit_reg(0, L);
                    break;
                case 0x46:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 (HL)" << endl;
                    cpu.bit_addr(0, cpu.memo.get_HL());
                    break;
                case 0x47:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 0 A" << endl;
                    cpu.bit_reg(0, A);
                    break;
                case 0x48:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 B" << endl;
                    cpu.bit_reg(1, B);
                    break;
                case 0x49:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 C" << endl;
                    cpu.bit_reg(1, C);
                    break;
                case 0x4A:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 D" << endl;
                    cpu.bit_reg(1, D);
                    break;
                case 0x4B:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 E" << endl;
                    cpu.bit_reg(1, E);
                    break;
                case 0x4C:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 H" << endl;
                    cpu.bit_reg(1, H);
                    break;
                case 0x4D:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 L" << endl;
                    cpu.bit_reg(1, L);
                    break;
                case 0x4E:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 (HL)" << endl;
                    cpu.bit_addr(1, cpu.memo.get_HL());
                    break;
                case 0x4F:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 1 A" << endl;
                    cpu.bit_reg(1, A);
                    break;
                case 0x50:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 B" << endl;
                    cpu.bit_reg(2, B);
                    break;
                case 0x51:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 C" << endl;
                    cpu.bit_reg(2, C);
                    break;
                case 0x52:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 D" << endl;
                    cpu.bit_reg(2, D);
                    break;
                case 0x53:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 E" << endl;
                    cpu.bit_reg(2, E);
                    break;
                case 0x54:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 H" << endl;
                    cpu.bit_reg(2, H);
                    break;
                case 0x55:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 L" << endl;
                    cpu.bit_reg(2, L);
                    break;
                case 0x56:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 (HL)" << endl;
                    cpu.bit_addr(2, cpu.memo.get_HL());
                    break;
                case 0x57:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 2 A" << endl;
                    cpu.bit_reg(2, A);
                    break;
                case 0x58:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 B" << endl;
                    cpu.bit_reg(3, B);
                    break;
                case 0x59:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 C" << endl;
                    cpu.bit_reg(3, C);
                    break;
                case 0x5A:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 D" << endl;
                    cpu.bit_reg(3, D);
                    break;
                case 0x5B:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 E" << endl;
                    cpu.bit_reg(3, E);
                    break;
                case 0x5C:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 H" << endl;
                    cpu.bit_reg(3, H);
                    break;
                case 0x5D:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 L" << endl;
                    cpu.bit_reg(3, L);
                    break;
                case 0x5E:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 (HL)" << endl;
                    cpu.bit_addr(3, cpu.memo.get_HL());
                    break;
                case 0x5F:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 3 A" << endl;
                    cpu.bit_reg(3, A);
                    break;
                case 0x60:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 B" << endl;
                    cpu.bit_reg(4, B);
                    break;
                case 0x61:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 C" << endl;
                    cpu.bit_reg(4, C);
                    break;
                case 0x62:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 D" << endl;
                    cpu.bit_reg(4, D);
                    break;
                case 0x63:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 E" << endl;
                    cpu.bit_reg(4, E);
                    break;
                case 0x64:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 H" << endl;
                    cpu.bit_reg(4, H);
                    break;
                case 0x65:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 L" << endl;
                    cpu.bit_reg(4, L);
                    break;
                case 0x66:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 (HL)" << endl;
                    cpu.bit_addr(4, cpu.memo.get_HL());
                    break;
                case 0x67:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 4 A" << endl;
                    cpu.bit_reg(4, A);
                    break;
                case 0x68:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 B" << endl;
                    cpu.bit_reg(5, B);
                    break;
                case 0x69:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 C" << endl;
                    cpu.bit_reg(5, C);
                    break;
                case 0x6A:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 D" << endl;
                    cpu.bit_reg(5, D);
                    break;
                case 0x6B:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 E" << endl;
                    cpu.bit_reg(5, E);
                    break;
                case 0x6C:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 H" << endl;
                    cpu.bit_reg(5, H);
                    break;
                case 0x6D:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 L" << endl;
                    cpu.bit_reg(5, L);
                    break;
                case 0x6E:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 (HL)" << endl;
                    cpu.bit_addr(5, cpu.memo.get_HL());
                    break;
                case 0x6F:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 5 A" << endl;
                    cpu.bit_reg(5, A);
                    break;
                case 0x70:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 B" << endl;
                    cpu.bit_reg(6, B);
                    break;
                case 0x71:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 C" << endl;
                    cpu.bit_reg(6, C);
                    break;
                case 0x72:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 D" << endl;
                    cpu.bit_reg(6, D);
                    break;
                case 0x73:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 E" << endl;
                    cpu.bit_reg(6, E);
                    break;
                case 0x74:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 H" << endl;
                    cpu.bit_reg(6, H);
                    break;
                case 0x75:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 L" << endl;
                    cpu.bit_reg(6, L);
                    break;
                case 0x76:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 (HL)" << endl;
                    cpu.bit_addr(6, cpu.memo.get_HL());
                    break;
                case 0x77:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 6 A" << endl;
                    cpu.bit_reg(6, A);
                    break;
                case 0x78:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 B" << endl;
                    cpu.bit_reg(7, B);
                    break;
                case 0x79:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 C" << endl;
                    cpu.bit_reg(7, C);
                    break;
                case 0x7A:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 D" << endl;
                    cpu.bit_reg(7, D);
                    break;
                case 0x7B:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 E" << endl;
                    cpu.bit_reg(7, E);
                    break;
                case 0x7C:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 H" << endl;
                    cpu.bit_reg(7, H);
                    break;
                case 0x7D:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 L" << endl;
                    cpu.bit_reg(7, L);
                    break;
                case 0x7E:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 (HL)" << endl;
                    cpu.bit_addr(7, cpu.memo.get_HL());
                    break;
                case 0x7F:
                    output << cpu.memo.pc - 1 << " " << op_int << " BIT 7 A" << endl;
                    cpu.bit_reg(7, A);
                    break;
                case 0x80:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 B" << endl;
                    cpu.reset_bit_reg(0, B);
                    break;
                case 0x81:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 C" << endl;
                    cpu.reset_bit_reg(0, C);
                    break;
                case 0x82:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 D" << endl;
                    cpu.reset_bit_reg(0, D);
                    break;
                case 0x83:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 E" << endl;
                    cpu.reset_bit_reg(0, E);
                    break;
                case 0x84:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 H" << endl;
                    cpu.reset_bit_reg(0, H);
                    break;
                case 0x85:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 L" << endl;
                    cpu.reset_bit_reg(0, L);
                    break;
                case 0x86:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 (HL)" << endl;
                    cpu.reset_bit_addr(0, cpu.memo.get_HL());
                    break;
                case 0x87:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 0 A" << endl;
                    cpu.reset_bit_reg(0, A);
                    break;
                case 0x88:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 B" << endl;
                    cpu.reset_bit_reg(1, B);
                    break;
                case 0x89:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 C" << endl;
                    cpu.reset_bit_reg(1, C);
                    break;
                case 0x8A:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 D" << endl;
                    cpu.reset_bit_reg(1, D);
                    break;
                case 0x8B:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 E" << endl;
                    cpu.reset_bit_reg(1, E);
                    break;
                case 0x8C:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 H" << endl;
                    cpu.reset_bit_reg(1, H);
                    break;
                case 0x8D:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 L" << endl;
                    cpu.reset_bit_reg(1, L);
                    break;
                case 0x8E:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 (HL)" << endl;
                    cpu.reset_bit_addr(1, cpu.memo.get_HL());
                    break;
                case 0x8F:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 1 A" << endl;
                    cpu.reset_bit_reg(1, A);
                    break;
                case 0x90:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 B" << endl;
                    cpu.reset_bit_reg(2, B);
                    break;
                case 0x91:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 C" << endl;
                    cpu.reset_bit_reg(2, C);
                    break;
                case 0x92:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 D" << endl;
                    cpu.reset_bit_reg(2, D);
                    break;
                case 0x93:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 E" << endl;
                    cpu.reset_bit_reg(2, E);
                    break;
                case 0x94:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 H" << endl;
                    cpu.reset_bit_reg(2, H);
                    break;
                case 0x95:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 L" << endl;
                    cpu.reset_bit_reg(2, L);
                    break;
                case 0x96:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 (HL)" << endl;
                    cpu.reset_bit_addr(2, cpu.memo.get_HL());
                    break;
                case 0x97:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 2 A" << endl;
                    cpu.reset_bit_reg(2, A);
                    break;
                case 0x98:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 B" << endl;
                    cpu.reset_bit_reg(3, B);
                    break;
                case 0x99:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 C" << endl;
                    cpu.reset_bit_reg(3, C);
                    break;
                case 0x9A:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 D" << endl;
                    cpu.reset_bit_reg(3, D);
                    break;
                case 0x9B:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 E" << endl;
                    cpu.reset_bit_reg(3, E);
                    break;
                case 0x9C:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 H" << endl;
                    cpu.reset_bit_reg(3, H);
                    break;
                case 0x9D:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 L" << endl;
                    cpu.reset_bit_reg(3, L);
                    break;
                case 0x9E:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 (HL)" << endl;
                    cpu.reset_bit_addr(3, cpu.memo.get_HL());
                    break;
                case 0x9F:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 3 A" << endl;
                    cpu.reset_bit_reg(3, A);
                    break;
                case 0xA0:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 B" << endl;
                    cpu.reset_bit_reg(4, B);
                    break;
                case 0xA1:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 C" << endl;
                    cpu.reset_bit_reg(4, C);
                    break;
                case 0xA2:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 D" << endl;
                    cpu.reset_bit_reg(4, D);
                    break;
                case 0xA3:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 E" << endl;
                    cpu.reset_bit_reg(4, E);
                    break;
                case 0xA4:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 H" << endl;
                    cpu.reset_bit_reg(4, H);
                    break;
                case 0xA5:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 L" << endl;
                    cpu.reset_bit_reg(4, L);
                    break;
                case 0xA6:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 (HL)" << endl;
                    cpu.reset_bit_addr(4, cpu.memo.get_HL());
                    break;
                case 0xA7:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 4 A" << endl;
                    cpu.reset_bit_reg(4, A);
                    break;
                case 0xA8:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 B" << endl;
                    cpu.reset_bit_reg(5, B);
                    break;
                case 0xA9:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 C" << endl;
                    cpu.reset_bit_reg(5, C);
                    break;
                case 0xAA:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 D" << endl;
                    cpu.reset_bit_reg(5, D);
                    break;
                case 0xAB:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 E" << endl;
                    cpu.reset_bit_reg(5, E);
                    break;
                case 0xAC:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 H" << endl;
                    cpu.reset_bit_reg(5, H);
                    break;
                case 0xAD:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 L" << endl;
                    cpu.reset_bit_reg(5, L);
                    break;
                case 0xAE:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 (HL)" << endl;
                    cpu.reset_bit_addr(5, cpu.memo.get_HL());
                    break;
                case 0xAF:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 5 A" << endl;
                    cpu.reset_bit_reg(5, A);
                    break;
                case 0xB0:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 B" << endl;
                    cpu.reset_bit_reg(6, B);
                    break;
                case 0xB1:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 C" << endl;
                    cpu.reset_bit_reg(6, C);
                    break;
                case 0xB2:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 D" << endl;
                    cpu.reset_bit_reg(6, D);
                    break;
                case 0xB3:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 E" << endl;
                    cpu.reset_bit_reg(6, E);
                    break;
                case 0xB4:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 H" << endl;
                    cpu.reset_bit_reg(6, H);
                    break;
                case 0xB5:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 L" << endl;
                    cpu.reset_bit_reg(6, L);
                    break;
                case 0xB6:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 (HL)" << endl;
                    cpu.reset_bit_addr(6, cpu.memo.get_HL());
                    break;
                case 0xB7:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 6 A" << endl;
                    cpu.reset_bit_reg(6, A);
                    break;
                case 0xB8:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 B" << endl;
                    cpu.reset_bit_reg(7, B);
                    break;
                case 0xB9:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 C" << endl;
                    cpu.reset_bit_reg(7, C);
                    break;
                case 0xBA:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 D" << endl;
                    cpu.reset_bit_reg(7, D);
                    break;
                case 0xBB:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 E" << endl;
                    cpu.reset_bit_reg(7, E);
                    break;
                case 0xBC:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 H" << endl;
                    cpu.reset_bit_reg(7, H);
                    break;
                case 0xBD:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 L" << endl;
                    cpu.reset_bit_reg(7, L);
                    break;
                case 0xBE:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 (HL)" << endl;
                    cpu.reset_bit_addr(7, cpu.memo.get_HL());
                    break;
                case 0xBF:
                    output << cpu.memo.pc - 1 << " " << op_int << " RES 7 A" << endl;
                    cpu.reset_bit_reg(7, A);
                    break;
                case 0xC0:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 B" << endl;
                    cpu.set_bit_reg(0, B);
                    break;
                case 0xC1:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 C" << endl;
                    cpu.set_bit_reg(0, C);
                    break;
                case 0xC2:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 D" << endl;
                    cpu.set_bit_reg(0, D);
                    break;
                case 0xC3:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 E" << endl;
                    cpu.set_bit_reg(0, E);
                    break;
                case 0xC4:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 H" << endl;
                    cpu.set_bit_reg(0, H);
                    break;
                case 0xC5:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 L" << endl;
                    cpu.set_bit_reg(0, L);
                    break;
                case 0xC6:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 (HL)" << endl;
                    cpu.set_bit_addr(0, cpu.memo.get_HL());
                    break;
                case 0xC7:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 0 A" << endl;
                    cpu.set_bit_reg(0, A);
                    break;
                case 0xC8:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 B" << endl;
                    cpu.set_bit_reg(1, B);
                    break;
                case 0xC9:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 C" << endl;
                    cpu.set_bit_reg(1, C);
                    break;
                case 0xCA:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 D" << endl;
                    cpu.set_bit_reg(1, D);
                    break;
                case 0xCB:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 E" << endl;
                    cpu.set_bit_reg(1, E);
                    break;
                case 0xCC:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 H" << endl;
                    cpu.set_bit_reg(1, H);
                    break;
                case 0xCD:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 L" << endl;
                    cpu.set_bit_reg(1, L);
                    break;
                case 0xCE:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 (HL)" << endl;
                    cpu.set_bit_addr(1, cpu.memo.get_HL());
                    break;
                case 0xCF:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 1 A" << endl;
                    cpu.set_bit_reg(1, A);
                    break;
                case 0xD0:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 B" << endl;
                    cpu.set_bit_reg(2, B);
                    break;
                case 0xD1:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 C" << endl;
                    cpu.set_bit_reg(2, C);
                    break;
                case 0xD2:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 D" << endl;
                    cpu.set_bit_reg(2, D);
                    break;
                case 0xD3:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 E" << endl;
                    cpu.set_bit_reg(2, E);
                    break;
                case 0xD4:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 H" << endl;
                    cpu.set_bit_reg(2, H);
                    break;
                case 0xD5:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 L" << endl;
                    cpu.set_bit_reg(2, L);
                    break;
                case 0xD6:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 (HL)" << endl;
                    cpu.set_bit_addr(2, cpu.memo.get_HL());
                    break;
                case 0xD7:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 2 A" << endl;
                    cpu.set_bit_reg(2, A);
                    break;
                case 0xD8:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 B" << endl;
                    cpu.set_bit_reg(3, B);
                    break;
                case 0xD9:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 C" << endl;
                    cpu.set_bit_reg(3, C);
                    break;
                case 0xDA:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 D" << endl;
                    cpu.set_bit_reg(3, D);
                    break;
                case 0xDB:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 E" << endl;
                    cpu.set_bit_reg(3, E);
                    break;
                case 0xDC:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 H" << endl;
                    cpu.set_bit_reg(3, H);
                    break;
                case 0xDD:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 L" << endl;
                    cpu.set_bit_reg(3, L);
                    break;
                case 0xDE:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 (HL)" << endl;
                    cpu.set_bit_addr(3, cpu.memo.get_HL());
                    break;
                case 0xDF:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 3 A" << endl;
                    cpu.set_bit_reg(3, A);
                    break;
                case 0xE0:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 B" << endl;
                    cpu.set_bit_reg(4, B);
                    break;
                case 0xE1:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 C" << endl;
                    cpu.set_bit_reg(4, C);
                    break;
                case 0xE2:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 D" << endl;
                    cpu.set_bit_reg(4, D);
                    break;
                case 0xE3:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 E" << endl;
                    cpu.set_bit_reg(4, E);
                    break;
                case 0xE4:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 H" << endl;
                    cpu.set_bit_reg(4, H);
                    break;
                case 0xE5:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 L" << endl;
                    cpu.set_bit_reg(4, L);
                    break;
                case 0xE6:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 (HL)" << endl;
                    cpu.set_bit_addr(4, cpu.memo.get_HL());
                    break;
                case 0xE7:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 4 A" << endl;
                    cpu.set_bit_reg(4, A);
                    break;
                case 0xE8:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 B" << endl;
                    cpu.set_bit_reg(5, B);
                    break;
                case 0xE9:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 C" << endl;
                    cpu.set_bit_reg(5, C);
                    break;
                case 0xEA:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 D" << endl;
                    cpu.set_bit_reg(5, D);
                    break;
                case 0xEB:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 E" << endl;
                    cpu.set_bit_reg(5, E);
                    break;
                case 0xEC:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 H" << endl;
                    cpu.set_bit_reg(5, H);
                    break;
                case 0xED:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 L" << endl;
                    cpu.set_bit_reg(5, L);
                    break;
                case 0xEE:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 (HL)" << endl;
                    cpu.set_bit_addr(5, cpu.memo.get_HL());
                    break;
                case 0xEF:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 5 A" << endl;
                    cpu.set_bit_reg(5, A);
                    break;
                case 0xF0:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 B" << endl;
                    cpu.set_bit_reg(6, B);
                    break;
                case 0xF1:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 C" << endl;
                    cpu.set_bit_reg(6, C);
                    break;
                case 0xF2:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 D" << endl;
                    cpu.set_bit_reg(6, D);
                    break;
                case 0xF3:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 E" << endl;
                    cpu.set_bit_reg(6, E);
                    break;
                case 0xF4:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 H" << endl;
                    cpu.set_bit_reg(6, H);
                    break;
                case 0xF5:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 L" << endl;
                    cpu.set_bit_reg(6, L);
                    break;
                case 0xF6:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 (HL)" << endl;
                    cpu.set_bit_addr(6, cpu.memo.get_HL());
                    break;
                case 0xF7:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 6 A" << endl;
                    cpu.set_bit_reg(6, A);
                    break;
                case 0xF8:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 B" << endl;
                    cpu.set_bit_reg(7, B);
                    break;
                case 0xF9:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 C" << endl;
                    cpu.set_bit_reg(7, C);
                    break;
                case 0xFA:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 D" << endl;
                    cpu.set_bit_reg(7, D);
                    break;
                case 0xFB:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 E" << endl;
                    cpu.set_bit_reg(7, E);
                    break;
                case 0xFC:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 H" << endl;
                    cpu.set_bit_reg(7, H);
                    break;
                case 0xFD:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 L" << endl;
                    cpu.set_bit_reg(7, L);
                    break;
                case 0xFE:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 (HL)" << endl;
                    cpu.set_bit_addr(7, cpu.memo.get_HL());
                    break;
                case 0xFF:
                    output << cpu.memo.pc - 1 << " " << op_int << " SET 7 A" << endl;
                    cpu.set_bit_reg(7, A);
                    break;
                }
            }
            break;
        case 0xCC:
            output << cpu.memo.pc - 1 << " " << op_int << " CALL Z ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_Z(), addr);
            break;
        case 0xCD:
            output << cpu.memo.pc - 1 << " " << op_int << " CALL ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call(addr);
            break;
        case 0xCE:
            output << cpu.memo.pc - 1 << " " << op_int << " ADC A N" << endl;
            cpu.add_reg_c(A, cpu.memo.read());
            break;
        case 0xCF:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 08H" << endl;
            cpu.call(0x08);
            break;
        case 0xD0:
            output << cpu.memo.pc - 1 << " " << op_int << " RET NC" << endl;
            cpu.ret_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_C());
            break;
        case 0xD1:
            output << cpu.memo.pc - 1 << "POP DE" << endl;
            cpu.memo.set_DE(cpu.pop_rr());
            break;
        case 0xD2:
            output << cpu.memo.pc - 1 << " " << op_int << " JP NC ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_C(), addr);
            break;
        case 0xD4: // D3 is illegal
            output << cpu.memo.pc - 1 << " " << op_int << " CALL NC ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_C(), addr);
            break;
        case 0xD5:
            output << cpu.memo.pc - 1 << " " << op_int << " PUSH DE" << endl;
            cpu.push_rr(D);
            break;
        case 0xD6:
            output << cpu.memo.pc - 1 << " " << op_int << " SUB N" << endl;
            cpu.sub_reg(A, cpu.memo.read());
            break;
        case 0xD7:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 10H" << endl;
            cpu.nop();
            break;
        case 0xD8:
            output << cpu.memo.pc - 1 << " " << op_int << " RET C" << endl;
            cpu.ret_cnd(cpu.memo.getflag_C());
            break;
        case 0xD9:
            output << cpu.memo.pc - 1 << " " << op_int << " RETI" << endl;
            cpu.reti();
            break;
        case 0xDA:
            output << cpu.memo.pc - 1 << " " << op_int << " JP C ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0xDC: // DB is illegal
            output << cpu.memo.pc - 1 << " " << op_int << " CALL C ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0xDE: // DD is illegal
            output << cpu.memo.pc - 1 << " " << op_int << " SBC A N" << endl;
            cpu.sub_reg_c(A, cpu.memo.read());
            break;
        case 0xDF:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 18H" << endl;
            cpu.call(0x18);
            break;
        case 0xE0:
            output << cpu.memo.pc - 1 << " " << op_int << " LDH ADDR A" << endl;
            addr = 0xFF00 | cpu.memo.read();
            cpu.load_ar(addr, A);
            break;
        case 0xE1:
            output << cpu.memo.pc - 1 << " " << op_int << " POP HL" << endl;
            cpu.memo.set_HL(cpu.pop_rr());
            break;
        case 0xE2:
            output << cpu.memo.pc - 1 << " " << op_int << " LD (C) A" << endl;
            addr = 0xFF00 | cpu.memo.reg[C];
            cpu.load_ar(addr, A);
            break;
        case 0xE5: // E3 and E4 are illegal
            output << cpu.memo.pc - 1 << " " << op_int << " PUSH HL" << endl;
            cpu.push_rr(H);
            break;
        case 0xE6:
            output << cpu.memo.pc - 1 << " " << op_int << " AND A N" << endl;
            cpu.and_reg(A, cpu.memo.read());
            break;
        case 0xE7:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 20H" << endl;
            cpu.call(0x20);
            break;
        case 0xE8:
            output << cpu.memo.pc - 1 << " " << op_int << " ADD SP N" << endl;
            offset = cpu.memo.read();
            cpu.add_sp(offset);
            break;
        case 0xE9:
            output << cpu.memo.pc - 1 << " " << op_int << " JP HL" << endl;
            cpu.jump(cpu.memo.get_HL());
            break;
        case 0xEA:
            output << cpu.memo.pc - 1 << " " << op_int << " LD ADDR A" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_ar(addr, A);
            break;
        case 0xEE: // EB-ED are illegal
            output << cpu.memo.pc - 1 << " " << op_int << " XOR A N" << endl;
            cpu.xor_reg(A, cpu.memo.read());
            break;
        case 0xEF:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 28H" << endl;
            cpu.call(0x28);
            break;
        case 0xF0:
            output << cpu.memo.pc - 1 << " " << op_int << " LDH A ADDR" << endl;
            addr = 0xFF00 | cpu.memo.read();
            cpu.load_ra(A, addr);
            break;
        case 0xF1:
            output << cpu.memo.pc - 1 << " " << op_int << " POP AF" << endl;
            cpu.memo.set_AF(cpu.pop_rr());
            break;
        case 0xF2:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A (C)" << endl;
            addr = 0xFF00 | cpu.memo.reg[C];
            cpu.load_ra(A, addr);
            break;
        case 0xF3:
            output << cpu.memo.pc - 1 << " " << op_int << " DI" << endl;
            cpu.nop();
            break;
        case 0xF5: // F4 is illegal
            output << cpu.memo.pc - 1 << " " << op_int << " PUSH AF" << endl;
            cpu.push_rr(A);
            break;
        case 0xF6:
            output << cpu.memo.pc - 1 << " " << op_int << " OR A N" << endl;
            cpu.or_reg(A, cpu.memo.read());
            break;
        case 0xF7:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 30H" << endl;
            cpu.call(0x30);
            break;
        case 0xF8:
            output << cpu.memo.pc - 1 << " " << op_int << " LD HL SP+N" << endl;
            s_data = cpu.memo.sp + cpu.memo.read();
            cpu.load_rrnn(H, s_data);
            break;
        case 0xF9:
            output << cpu.memo.pc - 1 << " " << op_int << " LD SP HL" << endl;
            cpu.load_sphl();
            break;
        case 0xFA:
            output << cpu.memo.pc - 1 << " " << op_int << " LD A ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_ra(A, addr);
            break;
        case 0xFB:
            output << cpu.memo.pc - 1 << " " << op_int << " EI" << endl;
            cpu.nop();
            break;
        case 0xFD:  // illegal instruction that i'm hijacking for easy testing info
        {
            unsigned int rA = cpu.memo.reg[A];
            unsigned int rB = cpu.memo.reg[B];
            unsigned int rC = cpu.memo.reg[C];
            unsigned int rD = cpu.memo.reg[D];
            unsigned int rE = cpu.memo.reg[E];
            unsigned int rH = cpu.memo.reg[H];
            unsigned int rL = cpu.memo.reg[L];
            output << cpu.memo.pc - 1 << " " << op_int << " DEBUG ";
            output << "CPU registers: " << rA << " ";
            output << rB << " ";
            output << rC << " ";
            output << rD << " ";
            output << rE << " ";
            output << rH << " ";
            output << rL << "; ";
            output << "SP: " << cpu.memo.sp << "; ";
            output << "Flags: ";
            for (int i = 0; i < 4; i++) { output << cpu.memo.flags[i] << " "; }
            output << endl;
        }
            break;
        case 0xFE: // FC and FD are illegal
            output << cpu.memo.pc - 1 << " " << op_int << " CP A N" << endl;
            cpu.compare(A, cpu.memo.read());
            break;
        case 0xFF:
            output << cpu.memo.pc - 1 << " " << op_int << " RST 38H" << endl;
            cpu.call(0x38);
            break;
        }
    }
}

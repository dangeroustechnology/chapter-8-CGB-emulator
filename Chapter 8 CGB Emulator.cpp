// Chapter 8 CGB Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Multithreading

#include <iostream>
#include <fstream>
#include <bitset>
#include "file_reader.h"
#include "cpu_instr.h"
#include "memory.h"

using namespace std;

int main(string file)
{
    const unsigned char A = 0;
    const unsigned char B = 2;
    const unsigned char C = 3;
    const unsigned char D = 4;
    const unsigned char E = 5;
    const unsigned char H = 6;
    const unsigned char L = 7;
    const unsigned char SP = 8;
    // file "dummy" exclusively contains 0x00 - 0x0F in asc. order
    file = "C:\\Users\\itbra\\Downloads\\dummy";
    string filename = (file != "") ? file : ".\\test";
    cpu_instr cpu;
    cpu.memo.fill(filename);
    bool clock = true;
    while (clock) {
        // var declarations for use in instructions
        unsigned char opcode = cpu.memo.read();
        unsigned short addr = 0;
        unsigned char lsb = 0;
        unsigned short data = 0;
        signed short s_data = 0;
        signed char offset = 0;

        switch (opcode) {
        case 0x00:
            cout << cpu.memo.pc << " NOP" << endl;
            cpu.nop();
            break;
        case 0x01:
            cout << cpu.memo.pc << " LD BC NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(B, data);
            break;
        case 0x02:
            cout << cpu.memo.pc << " LD (BC) A" << endl;
            cpu.load_ar(cpu.memo.get_BC(), cpu.memo.reg[A]);
            break;
        case 0x03:
            cout << cpu.memo.pc << " INC BC" << endl;
            cpu.increment_16(B);
            break;
        case 0x04:
            cout << cpu.memo.pc << " INC B" << endl;
            cpu.increment(cpu.memo.reg[B]);
            break;
        case 0x05:
            cout << cpu.memo.pc << " DEC B" << endl;
            cpu.decrement(cpu.memo.reg[B]);
            break;
        case 0x06:
            cout << cpu.memo.pc << " LD B N" << endl;
            cpu.load_rn(2, cpu.memo.read());
            break;
        case 0x07:
            cout << cpu.memo.pc << " RLCA" << endl;
            cpu.rot_left_c(A);
            break;
        case 0x08:
            cout << cpu.memo.pc << " LD (NN) SP" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_nnsp(addr);
            break;
        case 0x09:
            cout << cpu.memo.pc << " ADD HL BC" << endl;
            cpu.add_16(cpu.memo.get_BC());
            break;
        case 0x0A:
            cout << cpu.memo.pc << " LD A (BC)" << endl;
            cpu.load_ra(A, cpu.memo.mem[cpu.memo.get_BC()]);
            break;
        case 0x0B:
            cout << cpu.memo.pc << " DEC B" << endl;
            cpu.decrement(cpu.memo.reg[B]);
            break;
        case 0x0C:
            cout << cpu.memo.pc << " INC C" << endl;
            cpu.increment(cpu.memo.reg[C]);
            break;
        case 0x0D:
            cout << cpu.memo.pc << " DEC C" << endl;
            cpu.decrement(cpu.memo.reg[C]);
            break;
        case 0x0E:
            cout << cpu.memo.pc << " LD C N" << endl;
            cpu.load_rn(C, cpu.memo.read());
            break;
        case 0x0F:
            cout << cpu.memo.pc << " RRCA" << endl;
            cpu.rot_right_c(A);
            break;
        case 0x10:
            cout << cpu.memo.pc << " STOP" << endl;
            cpu.stop();
            clock = false; // tho this isnt properly implemented, i use it in test files
            break;
        case 0x11:
            cout << cpu.memo.pc << " LD DE NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(D, data);
            break;
        case 0x12:
            cout << cpu.memo.pc << " LD (DE) A" << endl;
            cpu.load_ar(cpu.memo.get_DE(), A);
            break;
        case 0x13:
            cout << cpu.memo.pc << " INC DE" << endl;
            cpu.increment_16(D);
            break;
        case 0x14:
            cout << cpu.memo.pc << " INC D" << endl;
            cpu.increment(D);
            break;
        case 0x15:
            cout << cpu.memo.pc << " DEC D" << endl;
            cpu.decrement(D);
            break;
        case 0x16:
            cout << cpu.memo.pc << " LD D N" << endl;
            cpu.load_rn(D, cpu.memo.read());
            break;
        case 0x17:
            cout << cpu.memo.pc << " RLA" << endl;
            cpu.rot_left(A);
            break;
        case 0x18:
            cout << cpu.memo.pc << " JR O" << endl;
            cpu.jump_rel(cpu.memo.read());
            break;
        case 0x19:
            cout << cpu.memo.pc << " ADD HL DE" << endl;
            cpu.add_16(cpu.memo.get_DE());
            break;
        case 0x1A:
            cout << cpu.memo.pc << " LD A (DE)" << endl;
            cpu.load_ra(A, cpu.memo.get_DE());
            break;
        case 0x1B:
            cout << cpu.memo.pc << " DEC DE" << endl;
            cpu.decrement_16(D);
            break;
        case 0x1C:
            cout << cpu.memo.pc << " INC E" << endl;
            cpu.increment(E);
            break;
        case 0x1D:
            cout << cpu.memo.pc << " DEC E" << endl;
            cpu.decrement(E);
            break;
        case 0x1E:
            cout << cpu.memo.pc << " LD E N" << endl;
            cpu.load_rn(E, cpu.memo.read());
            break;
        case 0x1F:
            cout << cpu.memo.pc << " RRA" << endl;
            cpu.rot_right(A);
            break;
        case 0x20:
            cout << cpu.memo.pc << " JR NZ O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd((cpu.memo.getflag_N() && cpu.memo.getflag_Z()), addr);
            break;
        case 0x21:
            cout << cpu.memo.pc << " LD HL NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(H, data);
            break;
        case 0x22:
            cout << cpu.memo.pc << " LD (HL+) A" << endl;
            cpu.load_air(A);
            break;
        case 0x23:
            cout << cpu.memo.pc << " INC HL" << endl;
            cpu.increment_16(H);
            break;
        case 0x24:
            cout << cpu.memo.pc << " INC H" << endl;
            cpu.increment(H);
            break;
        case 0x25:
            cout << cpu.memo.pc << " DEC H" << endl;
            cpu.decrement(H);
            break;
        case 0x26:
            cout << cpu.memo.pc << " LD H N" << endl;
            cpu.load_rn(H, cpu.memo.read());
            break;
        case 0x27:
            cout << cpu.memo.pc << " DAA" << endl;
            cpu.daa();
            break;
        case 0x28:
            cout << cpu.memo.pc << " JR Z O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd(cpu.memo.getflag_Z(), addr);
            break;
        case 0x29:
            cout << cpu.memo.pc << " ADD HL HL" << endl;
            cpu.add_16(cpu.memo.get_HL());
            break;
        case 0x2A:
            cout << cpu.memo.pc << " LD A (HL+)" << endl;
            cpu.load_rai(A);
            break;
        case 0x2B:
            cout << cpu.memo.pc << " DEC HL" << endl;
            cpu.decrement_16(H);
            break;
        case 0x2C:
            cout << cpu.memo.pc << " INC L" << endl;
            cpu.increment(L);
            break;
        case 0x2D:
            cout << cpu.memo.pc << " DEC L" << endl;
            cpu.decrement(L);
            break;
        case 0x2E:
            cout << cpu.memo.pc << " LD L N" << endl;
            cpu.load_rn(L, cpu.memo.read());
            break;
        case 0x2F:
            cout << cpu.memo.pc << " CPL" << endl;
            cpu.complement_a();
            break;
        case 0x30:
            cout << cpu.memo.pc << " JR NC O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd((cpu.memo.getflag_N() && cpu.memo.getflag_C()), addr);
            break;
        case 0x31:
            cout << cpu.memo.pc << " LD SP NN" << endl;
            lsb = cpu.memo.read();
            data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(SP, data);
            break;
        case 0x32:
            cout << cpu.memo.pc << " LD (HL-) A" << endl;
            cpu.load_adr(A);
            break;
        case 0x33:
            cout << cpu.memo.pc << " INC SP" << endl;
            cpu.increment_16(SP);
            break;
        case 0x34:
            cout << cpu.memo.pc << " INC (HL)" << endl;
            cpu.increment(cpu.memo.get_HL());
            break;
        case 0x35:
            cout << cpu.memo.pc << " DEC (HL)" << endl;
            cpu.decrement(cpu.memo.get_HL());
            break;
        case 0x36:
            cout << cpu.memo.pc << " LD (HL) N" << endl;
            cpu.load_an(cpu.memo.get_HL(), cpu.memo.read());
            break;
        case 0x37:
            cout << cpu.memo.pc << " SCF" << endl;
            cpu.set_cflag(true);
            break;
        case 0x38:
            cout << cpu.memo.pc << " JR C O" << endl;
            offset = cpu.memo.mem[cpu.memo.pc++];
            addr = cpu.memo.pc + offset;
            cpu.jump_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0x39:
            cout << cpu.memo.pc << " ADD HL SP" << endl;
            cpu.add_16(cpu.memo.sp);
            break;
        case 0x3A:
            cout << cpu.memo.pc << " LD A (HL-)" << endl;
            cpu.load_rad(A);
            break;
        case 0x3B:
            cout << cpu.memo.pc << " DEC SP" << endl;
            cpu.decrement_16(SP);
            break;
        case 0x3C:
            cout << cpu.memo.pc << " INC A" << endl;
            cpu.increment(A);
            break;
        case 0x3D:
            cout << cpu.memo.pc << " DEC A" << endl;
            cpu.decrement(A);
            break;
        case 0x3E:
            cout << cpu.memo.pc << " LD A N" << endl;
            cpu.load_rn(A, cpu.memo.read());
            break;
        case 0x3F:
            cout << cpu.memo.pc << " CCF" << endl;
            cpu.complement_c();
            break;
        case 0x40: 
            cout << cpu.memo.pc << " LD B B" << endl;
            cpu.load_rr(B, B);
            break;
        case 0x41: 
            cout << cpu.memo.pc << " LD B C" << endl;
            cpu.load_rr(B, C);
            break;
        case 0x42:
            cout << cpu.memo.pc << " LD B D" << endl;
            cpu.load_rr(B, D);
            break;
        case 0x43:
            cout << cpu.memo.pc << " LD B E" << endl;
            cpu.load_rr(B, E);
            break;
        case 0x44:
            cout << cpu.memo.pc << " LD B H" << endl;
            cpu.load_rr(B, H);
            break;
        case 0x45:
            cout << cpu.memo.pc << " LD B L" << endl;
            cpu.load_rr(B, L);
            break;
        case 0x46:
            cout << cpu.memo.pc << " LD B (HL)" << endl;
            cpu.load_ra(B, cpu.memo.get_HL());
            break;
        case 0x47:
            cout << cpu.memo.pc << " LD B A" << endl;
            cpu.load_rr(B, A);
            break;
        case 0x48:
            cout << cpu.memo.pc << " LD C B" << endl;
            cpu.load_rr(C, B);
            break;
        case 0x49:
            cout << cpu.memo.pc << " LD C C" << endl;
            cpu.load_rr(C, C);
            break;
        case 0x4A:
            cout << cpu.memo.pc << " LD C D" << endl;
            cpu.load_rr(C, D);
            break;
        case 0x4B:
            cout << cpu.memo.pc << " LD C E" << endl;
            cpu.load_rr(C, E);
            break;
        case 0x4C:
            cout << cpu.memo.pc << " LD C H" << endl;
            cpu.load_rr(C, H);
            break;
        case 0x4D:
            cout << cpu.memo.pc << " LD C L" << endl;
            cpu.load_rr(C, L);
            break;
        case 0x4E:
            cout << cpu.memo.pc << " LD C (HL)" << endl;
            cpu.load_ra(C, cpu.memo.get_HL());
            break;
        case 0x4F:
            cout << cpu.memo.pc << " LD C A" << endl;
            cpu.load_rr(C, A);
            break;
        case 0x50:
            cout << cpu.memo.pc << " LD D B" << endl;
            cpu.load_rr(D, B);
            break;
        case 0x51:
            cout << cpu.memo.pc << " LD D C" << endl;
            cpu.load_rr(D, C);
            break;
        case 0x52:
            cout << cpu.memo.pc << " LD D D" << endl;
            cpu.load_rr(D, D);
            break;
        case 0x53:
            cout << cpu.memo.pc << " LD D E" << endl;
            cpu.load_rr(D, E);
            break;
        case 0x54:
            cout << cpu.memo.pc << " LD D H" << endl;
            cpu.load_rr(D, H);
            break;
        case 0x55:
            cout << cpu.memo.pc << " LD D L" << endl;
            cpu.load_rr(D, L);
            break;
        case 0x56:
            cout << cpu.memo.pc << " LD D (HL)" << endl;
            cpu.load_ra(D, cpu.memo.get_HL());
            break;
        case 0x57:
            cout << cpu.memo.pc << " LD D A" << endl;
            cpu.load_rr(D, A);
            break;
        case 0x58:
            cout << cpu.memo.pc << " LD E B" << endl;
            cpu.load_rr(E, B);
            break;
        case 0x59:
            cout << cpu.memo.pc << " LD E C" << endl;
            cpu.load_rr(E, C);
            break;
        case 0x5A:
            cout << cpu.memo.pc << " LD E D" << endl;
            cpu.load_rr(E, D);
            break;
        case 0x5B:
            cout << cpu.memo.pc << " LD E E" << endl;
            cpu.load_rr(E, E);
            break;
        case 0x5C:
            cout << cpu.memo.pc << " LD E H" << endl;
            cpu.load_rr(E, H);
            break;
        case 0x5D:
            cout << cpu.memo.pc << " LD E L" << endl;
            cpu.load_rr(E, L);
            break;
        case 0x5E:
            cout << cpu.memo.pc << " LD E (HL)" << endl;
            cpu.load_ra(E, cpu.memo.get_HL());
            break;
        case 0x5F:
            cout << cpu.memo.pc << " LD E A" << endl;
            cpu.load_rr(E, A);
            break;
        case 0x60:
            cout << cpu.memo.pc << " LD H B" << endl;
            cpu.load_rr(H, B);
            break;
        case 0x61:
            cout << cpu.memo.pc << " LD H C" << endl;
            cpu.load_rr(H, C);
            break;
        case 0x62:
            cout << cpu.memo.pc << " LD H D" << endl;
            cpu.load_rr(H, D);
            break;
        case 0x63:
            cout << cpu.memo.pc << " LD H E" << endl;
            cpu.load_rr(H, E);
            break;
        case 0x64:
            cout << cpu.memo.pc << " LD H H" << endl;
            cpu.load_rr(H, H);
            break;
        case 0x65:
            cout << cpu.memo.pc << " LD H L" << endl;
            cpu.load_rr(H, L);
            break;
        case 0x66:
            cout << cpu.memo.pc << " LD H (HL)" << endl;
            cpu.load_ra(H, cpu.memo.get_HL());
            break;
        case 0x67:
            cout << cpu.memo.pc << " LD H A" << endl;
            cpu.load_rr(H, A);
            break;
        case 0x68:
            cout << cpu.memo.pc << " LD L B" << endl;
            cpu.load_rr(L, B);
            break;
        case 0x69:
            cout << cpu.memo.pc << " LD L C" << endl;
            cpu.load_rr(L, C);
            break;
        case 0x6A:
            cout << cpu.memo.pc << " LD L D" << endl;
            cpu.load_rr(L, D);
            break;
        case 0x6B:
            cout << cpu.memo.pc << " LD L E" << endl;
            cpu.load_rr(L, E);
            break;
        case 0x6C:
            cout << cpu.memo.pc << " LD L H" << endl;
            cpu.load_rr(L, H);
            break;
        case 0x6D:
            cout << cpu.memo.pc << " LD L L" << endl;
            cpu.load_rr(L, L);
            break;
        case 0x6E:
            cout << cpu.memo.pc << " LD L (HL)" << endl;
            cpu.load_ra(L, cpu.memo.get_HL());
            break;
        case 0x6F:
            cout << cpu.memo.pc << " LD L A" << endl;
            cpu.load_rr(L, A);
            break;
        case 0x70:
            cout << cpu.memo.pc << " LD (HL) B" << endl;
            cpu.load_ar(cpu.memo.get_HL(), B);
            break;
        case 0x71:
            cout << cpu.memo.pc << " LD (HL) C" << endl;
            cpu.load_ar(cpu.memo.get_HL(), C);
            break;
        case 0x72:
            cout << cpu.memo.pc << " LD (HL) D" << endl;
            cpu.load_ar(cpu.memo.get_HL(), D);
            break;
        case 0x73:
            cout << cpu.memo.pc << " LD (HL) E" << endl;
            cpu.load_ar(cpu.memo.get_HL(), E);
            break;
        case 0x74:
            cout << cpu.memo.pc << " LD (HL) H" << endl;
            cpu.load_ar(cpu.memo.get_HL(), H);
            break;
        case 0x75:
            cout << cpu.memo.pc << " LD (HL) L" << endl;
            cpu.load_ar(cpu.memo.get_HL(), L);
            break;
        case 0x76:
            cout << cpu.memo.pc << " HALT" << endl;
            cpu.halt();
            break;
        case 0x77:
            cout << cpu.memo.pc << " LD (HL) A" << endl;
            cpu.load_ar(cpu.memo.get_HL(), A);
            break;
        case 0x78:
            cout << cpu.memo.pc << " LD A B" << endl;
            cpu.load_rr(A, B);
            break;
        case 0x79:
            cout << cpu.memo.pc << " LD A C" << endl;
            cpu.load_rr(A, C);
            break;
        case 0x7A:
            cout << cpu.memo.pc << " LD A D" << endl;
            cpu.load_rr(A, D);
            break;
        case 0x7B:
            cout << cpu.memo.pc << " LD A E" << endl;
            cpu.load_rr(A, E);
            break;
        case 0x7C:
            cout << cpu.memo.pc << " LD A H" << endl;
            cpu.load_rr(A, H);
            break;
        case 0x7D:
            cout << cpu.memo.pc << " LD A L" << endl;
            cpu.load_rr(A, L);
            break;
        case 0x7E:
            cout << cpu.memo.pc << " LD A (HL)" << endl;
            cpu.load_ra(A, cpu.memo.get_HL());
            break;
        case 0x7F:
            cout << cpu.memo.pc << " LD A A" << endl;
            cpu.load_rr(A, A);
            break;
        case 0x80:
            cout << cpu.memo.pc << " ADD A B" << endl;
            cpu.add_reg(A, cpu.memo.reg[B]);
            break;
        case 0x81:
            cout << cpu.memo.pc << " ADD A C" << endl;
            cpu.add_reg(A, cpu.memo.reg[C]);
            break;
        case 0x82:
            cout << cpu.memo.pc << " ADD A D" << endl;
            cpu.add_reg(A, cpu.memo.reg[D]);
            break;
        case 0x83:
            cout << cpu.memo.pc << " ADD A E" << endl;
            cpu.add_reg(A, cpu.memo.reg[E]);
            break;
        case 0x84:
            cout << cpu.memo.pc << " ADD A H" << endl;
            cpu.add_reg(A, cpu.memo.reg[H]);
            break;
        case 0x85:
            cout << cpu.memo.pc << " ADD A L" << endl;
            cpu.add_reg(A, cpu.memo.reg[L]);
            break;
        case 0x86:
            cout << cpu.memo.pc << " ADD A (HL)" << endl;
            cpu.add_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x87:
            cout << cpu.memo.pc << " ADD A A" << endl;
            cpu.add_reg(A, cpu.memo.reg[A]);
            break;
        case 0x88:
            cout << cpu.memo.pc << " ADC A B" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x89:
            cout << cpu.memo.pc << " ADC A C" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8A:
            cout << cpu.memo.pc << " ADC A D" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8B:
            cout << cpu.memo.pc << " ADC A E" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8C:
            cout << cpu.memo.pc << " ADC A H" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8D:
            cout << cpu.memo.pc << " ADC A L" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x8E:
            cout << cpu.memo.pc << " ADC A (HL)" << endl;
            cpu.add_reg_c(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x8F:
            cout << cpu.memo.pc << " ADC A A" << endl;
            cpu.add_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x90:
            cout << cpu.memo.pc << " SUB A B" << endl;
            cpu.sub_reg(A, cpu.memo.reg[B]);
            break;
        case 0x91:
            cout << cpu.memo.pc << " SUB A C" << endl;
            cpu.sub_reg(A, cpu.memo.reg[C]);
            break;
        case 0x92:
            cout << cpu.memo.pc << " SUB A D" << endl;
            cpu.sub_reg(A, cpu.memo.reg[D]);
            break;
        case 0x93:
            cout << cpu.memo.pc << " SUB A E" << endl;
            cpu.sub_reg(A, cpu.memo.reg[E]);
            break;
        case 0x94:
            cout << cpu.memo.pc << " SUB A H" << endl;
            cpu.sub_reg(A, cpu.memo.reg[H]);
            break;
        case 0x95:
            cout << cpu.memo.pc << " SUB A L" << endl;
            cpu.sub_reg(A, cpu.memo.reg[L]);
            break;
        case 0x96:
            cout << cpu.memo.pc << " SUB A (HL)" << endl;
            cpu.sub_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x97:
            cout << cpu.memo.pc << " SUB A A" << endl;
            cpu.sub_reg(A, cpu.memo.reg[A]);
            break;
        case 0x98:
            cout << cpu.memo.pc << " SBC A B" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x99:
            cout << cpu.memo.pc << " SBC A C" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9A:
            cout << cpu.memo.pc << " SBC A D" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9B:
            cout << cpu.memo.pc << " SBC A E" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9C:
            cout << cpu.memo.pc << " SBC A H" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9D:
            cout << cpu.memo.pc << " SBC A L" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0x9E:
            cout << cpu.memo.pc << " SBC A (HL)" << endl;
            cpu.sub_reg_c(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0x9F:
            cout << cpu.memo.pc << " SBC A A" << endl;
            cpu.sub_reg_c(A, cpu.memo.reg[B]);
            break;
        case 0xA0:
            cout << cpu.memo.pc << " AND A B" << endl;
            cpu.and_reg(A, cpu.memo.reg[B]);
            break;
        case 0xA1:
            cout << cpu.memo.pc << " AND A C" << endl;
            cpu.and_reg(A, cpu.memo.reg[C]);
            break;
        case 0xA2:
            cout << cpu.memo.pc << " AND A D" << endl;
            cpu.and_reg(A, cpu.memo.reg[D]);
            break;
        case 0xA3:
            cout << cpu.memo.pc << " AND A E" << endl;
            cpu.and_reg(A, cpu.memo.reg[E]);
            break;
        case 0xA4:
            cout << cpu.memo.pc << " AND A H" << endl;
            cpu.and_reg(A, cpu.memo.reg[H]);
            break;
        case 0xA5:
            cout << cpu.memo.pc << " AND A L" << endl;
            cpu.and_reg(A, cpu.memo.reg[L]);
            break;
        case 0xA6:
            cout << cpu.memo.pc << " AND A (HL)" << endl;
            cpu.and_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xA7:
            cout << cpu.memo.pc << " AND A A" << endl;
            cpu.and_reg(A, cpu.memo.reg[A]);
            break;
        case 0xA8:
            cout << cpu.memo.pc << " XOR A B" << endl;
            cpu.xor_reg(A, cpu.memo.reg[B]);
            break;
        case 0xA9:
            cout << cpu.memo.pc << " XOR A C" << endl;
            cpu.xor_reg(A, cpu.memo.reg[C]);
            break;
        case 0xAA:
            cout << cpu.memo.pc << " XOR A D" << endl;
            cpu.xor_reg(A, cpu.memo.reg[D]);
            break;
        case 0xAB:
            cout << cpu.memo.pc << " XOR A E" << endl;
            cpu.xor_reg(A, cpu.memo.reg[E]);
            break;
        case 0xAC:
            cout << cpu.memo.pc << " XOR A H" << endl;
            cpu.xor_reg(A, cpu.memo.reg[H]);
            break;
        case 0xAD:
            cout << cpu.memo.pc << " XOR A L" << endl;
            cpu.xor_reg(A, cpu.memo.reg[L]);
            break;
        case 0xAE:
            cout << cpu.memo.pc << " XOR A (HL)" << endl;
            cpu.xor_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xAF:
            cout << cpu.memo.pc << " XOR A A" << endl;
            cpu.xor_reg(A, cpu.memo.reg[A]);
            break;
        case 0xB0:
            cout << cpu.memo.pc << " OR A B" << endl;
            cpu.or_reg(A, cpu.memo.reg[B]);
            break;
        case 0xB1:
            cout << cpu.memo.pc << " OR A C" << endl;
            cpu.or_reg(A, cpu.memo.reg[C]);
            break;
        case 0xB2:
            cout << cpu.memo.pc << " OR A D" << endl;
            cpu.or_reg(A, cpu.memo.reg[D]);
            break;
        case 0xB3:
            cout << cpu.memo.pc << " OR A E" << endl;
            cpu.or_reg(A, cpu.memo.reg[E]);
            break;
        case 0xB4:
            cout << cpu.memo.pc << " OR A H" << endl;
            cpu.or_reg(A, cpu.memo.reg[H]);
            break;
        case 0xB5:
            cout << cpu.memo.pc << " OR A L" << endl;
            cpu.or_reg(A, cpu.memo.reg[L]);
            break;
        case 0xB6:
            cout << cpu.memo.pc << " OR A (HL)" << endl;
            cpu.or_reg(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xB7:
            cout << cpu.memo.pc << " OR A A" << endl;
            cpu.or_reg(A, cpu.memo.reg[A]);
            break;
        case 0xB8:
            cout << cpu.memo.pc << " CP B" << endl;
            cpu.compare(A, cpu.memo.reg[B]);
            break;
        case 0xB9:
            cout << cpu.memo.pc << " CP C" << endl;
            cpu.compare(A, cpu.memo.reg[C]);
            break;
        case 0xBA:
            cout << cpu.memo.pc << " CP D" << endl;
            cpu.compare(A, cpu.memo.reg[D]);
            break;
        case 0xBB:
            cout << cpu.memo.pc << " CP E" << endl;
            cpu.compare(A, cpu.memo.reg[E]);
            break;
        case 0xBC:
            cout << cpu.memo.pc << " CP H" << endl;
            cpu.compare(A, cpu.memo.reg[H]);
            break;
        case 0xBD:
            cout << cpu.memo.pc << " CP L" << endl;
            cpu.compare(A, cpu.memo.reg[L]);
            break;
        case 0xBE:
            cout << cpu.memo.pc << " CP (HL)" << endl;
            cpu.compare(A, cpu.memo.mem[cpu.memo.get_HL()]);
            break;
        case 0xBF:
            cout << cpu.memo.pc << " CP A" << endl;
            cpu.compare(A, cpu.memo.reg[A]);
            break;
        case 0xC0:
            cout << cpu.memo.pc << " RET NZ" << endl;
            cpu.ret_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_Z());
            break;
        case 0xC1:
            cout << cpu.memo.pc << " POP BC" << endl;
            cpu.memo.set_BC(cpu.pop_rr());
            break;
        case 0xC2:
            cout << cpu.memo.pc << " JP NZ ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_Z(), addr);
            break;
        case 0xC3:
            cout << cpu.memo.pc << " JP ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump(addr);
            break;
        case 0xC4:
            cout << cpu.memo.pc << " CALL NZ ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_Z(), addr);
            break;
        case 0xC5:
            cout << cpu.memo.pc << " PUSH BC" << endl;
            cpu.push_rr(B);
            break;
        case 0xC6:
            cout << cpu.memo.pc << " ADD A N" << endl;
            cpu.add_reg(A, cpu.memo.read());
            break;
        case 0xC7:
            cout << cpu.memo.pc << " RST 00" << endl;
            cpu.call(0x0);
            break;
        case 0xC8:
            cout << cpu.memo.pc << " RET Z" << endl;
            cpu.ret_cnd(cpu.memo.getflag_Z());
            break;
        case 0xC9:
            cout << cpu.memo.pc << " RET" << endl;
            cpu.ret();
            break;
        case 0xCA:
            cout << cpu.memo.pc << " JP Z ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_Z(), addr);
        case 0xCB:                                                  // TODO
            cout << cpu.memo.pc << " PREFIX" << endl;
            cpu.nop();
            break;
        case 0xCC:
            cout << cpu.memo.pc << " CALL Z ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_Z(), addr);
            break;
        case 0xCD:
            cout << cpu.memo.pc << " CALL ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call(addr);
            break;
        case 0xCE:
            cout << cpu.memo.pc << " ADC A N" << endl;
            cpu.add_reg_c(A, cpu.memo.read());
            break;
        case 0xCF:
            cout << cpu.memo.pc << " RST 08H" << endl;
            cpu.call(0x08);
            break;
        case 0xD0:
            cout << cpu.memo.pc << " RET NC" << endl;
            cpu.ret_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_C());
            break;
        case 0xD1:
            cout << cpu.memo.pc << "POP DE" << endl;
            cpu.memo.set_DE(cpu.pop_rr());
            break;
        case 0xD2:
            cout << cpu.memo.pc << " JP NC ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_C(), addr);
            break;
        case 0xD4: // D3 is illegal
            cout << cpu.memo.pc << " CALL NC ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_N() && cpu.memo.getflag_C(), addr);
            break;
        case 0xD5:
            cout << cpu.memo.pc << " PUSH DE" << endl;
            cpu.push_rr(D);
            break;
        case 0xD6:
            cout << cpu.memo.pc << " SUB N" << endl;
            cpu.sub_reg(A, cpu.memo.read());
            break;
        case 0xD7:
            cout << cpu.memo.pc << " RST 10H" << endl;
            cpu.nop();
            break;
        case 0xD8:
            cout << cpu.memo.pc << " RET C" << endl;
            cpu.ret_cnd(cpu.memo.getflag_C());
            break;
        case 0xD9:
            cout << cpu.memo.pc << " RETI" << endl;
            cpu.reti();
            break;
        case 0xDA:
            cout << cpu.memo.pc << " JP C ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.jump_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0xDC: // DB is illegal
            cout << cpu.memo.pc << " CALL C ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.call_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0xDE: // DD is illegal
            cout << cpu.memo.pc << " SBC A N" << endl;
            cpu.sub_reg_c(A, cpu.memo.read());
            break;
        case 0xDF:
            cout << cpu.memo.pc << " RST 18H" << endl;
            cpu.call(0x18);
            break;
        case 0xE0:
            cout << cpu.memo.pc << " LDH ADDR A" << endl;
            addr = 0xFF00 | cpu.memo.read();
            cpu.load_ar(addr, A);
        case 0xE1:
            cout << cpu.memo.pc << " POP HL" << endl;
            cpu.memo.set_HL(cpu.pop_rr());
            break;
        case 0xE2:
            cout << cpu.memo.pc << " LD (C) A" << endl;
            addr = 0xFF00 | cpu.memo.reg[C];
            cpu.load_ar(addr, A);
            break;
        case 0xE5: // E3 and E4 are illegal
            cout << cpu.memo.pc << " PUSH HL" << endl;
            cpu.push_rr(H);
            break;
        case 0xE6:
            cout << cpu.memo.pc << " AND A N" << endl;
            cpu.and_reg(A, cpu.memo.read());
            break;
        case 0xE7:
            cout << cpu.memo.pc << " RST 20H" << endl;
            cpu.call(0x20);
            break;
        case 0xE8:
            cout << cpu.memo.pc << " ADD SP N" << endl;
            offset = cpu.memo.read();
            cpu.memo.sp += offset;
            break;
        case 0xE9:
            cout << cpu.memo.pc << " JP HL" << endl;
            cpu.jump(cpu.memo.get_HL());
            break;
        case 0xEA:
            cout << cpu.memo.pc << " LD ADDR A" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_ar(addr, A);
            break;
        case 0xEE: // EB-ED are illegal
            cout << cpu.memo.pc << " XOR A N" << endl;
            cpu.xor_reg(A, cpu.memo.read());
            break;
        case 0xEF:
            cout << cpu.memo.pc << " RST 28H" << endl;
            cpu.call(0x28);
            break;
        case 0xF0:
            cout << cpu.memo.pc << " LDH A ADDR" << endl;
            addr = 0xFF | cpu.memo.read();
            cpu.load_ra(A, addr);
            break;
        case 0xF1:
            cout << cpu.memo.pc << " POP AF" << endl;
            cpu.memo.set_AF(cpu.pop_rr());
            break;
        case 0xF2:
            cout << cpu.memo.pc << " LD A (C)" << endl;
            addr = 0xFF00 | cpu.memo.reg[C];
            cpu.load_ra(A, addr);
            break;
        case 0xF3:
            cout << cpu.memo.pc << " DI" << endl;
            cpu.nop();
            break;
        case 0xF5: // F4 is illegal
            cout << cpu.memo.pc << " PUSH AF" << endl;
            cpu.push_rr(A);
            break;
        case 0xF6:
            cout << cpu.memo.pc << " OR A N" << endl;
            cpu.or_reg(A, cpu.memo.read());
            break;
        case 0xF7:
            cout << cpu.memo.pc << " RST 30H" << endl;
            cpu.call(0x30);
            break;
        case 0xF8:
            cout << cpu.memo.pc << " LD HL SP+N" << endl;
            s_data = cpu.memo.sp + cpu.memo.read();
            cpu.load_rrnn(H, s_data);
            break;
        case 0xF9:
            cout << cpu.memo.pc << " LD SP HL" << endl;
            cpu.load_sphl();
            break;
        case 0xFA:
            cout << cpu.memo.pc << " LD A ADDR" << endl;
            lsb = cpu.memo.read();
            addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_ra(A, addr);
            break;
        case 0xFB:
            cout << cpu.memo.pc << " EI" << endl;
            cpu.nop();
            break;
        case 0xFD:  // illegal instruction that i'm hijacking for easy testing info
            cout << "CPU registers: " << cpu.memo.get_AF() << " ";
            cout << cpu.memo.get_BC() << " ";
            cout << cpu.memo.get_DE() << " ";
            cout << cpu.memo.get_HL() << "; ";
            cout << "SP: " << cpu.memo.sp << endl;
        case 0xFE: // FC and FD are illegal
            cout << cpu.memo.pc << " CP A N" << endl;
            cpu.compare(A, cpu.memo.read());
            break;
        case 0xFF:
            cout << cpu.memo.pc << " RST 38H" << endl;
            cpu.call(0x38);
            break;
        }
    }
}

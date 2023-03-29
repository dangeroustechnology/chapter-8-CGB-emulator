// Chapter 8 CGB Emulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Multithreading
// Function pointers

#include <iostream>
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
    //*
    // file "dummy" exclusively contains 0x00 - 0x0F in asc.order
    cpu_instr cpu;
    cpu.memo.fill("C:\\Users\\itbra\\Downloads\\dummy");
    bool clock = true;
    while (clock) {
        unsigned char opcode = cpu.memo.read();
        switch (opcode) {
        case 0x00:
            cout << cpu.memo.pc << "NOP" << endl;
            cpu.nop();
            break;
        case 0x01:
            cout << cpu.memo.pc << "LD BC NN" << endl;
            unsigned char lsb = cpu.memo.read();
            unsigned short data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(B, data);
            break;
        case 0x02:
            cout << cpu.memo.pc << "LD (BC) A" << endl;
            cpu.load_ar(cpu.memo.get_BC(), cpu.memo.reg[A]);
            break;
        case 0x03:
            cout << cpu.memo.pc << "INC BC" << endl;
            cpu.increment_16(B);
            break;
        case 0x04:
            cout << cpu.memo.pc << "INC B" << endl;
            cpu.increment(cpu.memo.reg[B]);
            break;
        case 0x05:
            cout << cpu.memo.pc << "DEC B" << endl;
            cpu.decrement(cpu.memo.reg[B]);
            break;
        case 0x06:
            cout << cpu.memo.pc << "LD B N" << endl;
            cpu.load_rn(2, cpu.memo.read());
            break;
        case 0x07:                                                  // TODO
            cout << cpu.memo.pc << "RLCA" << endl;
            cpu.nop();
            break;
        case 0x08:
            cout << cpu.memo.pc << "LD (NN) SP" << endl;
            unsigned char lsb = cpu.memo.read();
            unsigned short addr = cpu.memo.read();
            addr = addr << 8;
            addr |= lsb;
            cpu.load_nnsp(addr);
            break;
        case 0x09:
            cout << cpu.memo.pc << "ADD HL BC" << endl;
            cpu.add_16(cpu.memo.get_BC());
            break;
        case 0x0A:
            cout << cpu.memo.pc << "LD A (BC)" << endl;
            cpu.load_ra(A, cpu.memo.mem[cpu.memo.get_BC()]);
            break;
        case 0x0B:
            cout << cpu.memo.pc << "DEC B" << endl;
            cpu.decrement(cpu.memo.reg[B]);
            break;
        case 0x0C:
            cout << cpu.memo.pc << "INC C" << endl;
            cpu.increment(cpu.memo.reg[C]);
            break;
        case 0x0D:
            cout << cpu.memo.pc << "DEC C" << endl;
            cpu.decrement(cpu.memo.reg[C]);
            break;
        case 0x0E:
            cout << cpu.memo.pc << "LD C N" << endl;
            cpu.load_rn(C, cpu.memo.read());
            break;
        case 0x0F:                                                  // TODO
            cout << cpu.memo.pc << "RRCA" << endl;
            cpu.nop();
            break;
        case 0x10:
            cout << cpu.memo.pc << "STOP" << endl;
            cpu.stop();
            break;
        case 0x11:
            cout << cpu.memo.pc << "LD DE NN" << endl;
            unsigned char lsb = cpu.memo.read();
            unsigned short data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(D, data);
            break;
        case 0x12:
            cout << cpu.memo.pc << "LD (DE) A" << endl;
            cpu.load_ar(cpu.memo.get_DE(), A);
            break;
        case 0x13:
            cout << cpu.memo.pc << "INC DE" << endl;
            cpu.increment_16(D);
            break;
        case 0x14:
            cout << cpu.memo.pc << "INC D" << endl;
            cpu.increment(D);
            break;
        case 0x15:
            cout << cpu.memo.pc << "DEC D" << endl;
            cpu.decrement(D);
            break;
        case 0x16:
            cout << cpu.memo.pc << "LD D N" << endl;
            cpu.load_rn(D, cpu.memo.read());
            break;
        case 0x17:                                                  // TODO
            cout << cpu.memo.pc << "RLA" << endl;
            cpu.nop();
            break;
        case 0x18:
            cout << cpu.memo.pc << "JR O" << endl;
            cpu.jump_rel(cpu.memo.read());
            break;
        case 0x19:
            cout << cpu.memo.pc << "ADD HL DE" << endl;
            cpu.add_16(cpu.memo.get_DE());
            break;
        case 0x1A:
            cout << cpu.memo.pc << "LD A (DE)" << endl;
            cpu.load_ra(A, cpu.memo.get_DE());
            break;
        case 0x1B:
            cout << cpu.memo.pc << "DEC DE" << endl;
            cpu.decrement_16(D);
            break;
        case 0x1C:
            cout << cpu.memo.pc << "INC E" << endl;
            cpu.increment(E);
            break;
        case 0x1D:
            cout << cpu.memo.pc << "DEC E" << endl;
            cpu.decrement(E);
            break;
        case 0x1E:
            cout << cpu.memo.pc << "LD E N" << endl;
            cpu.load_rn(E, cpu.memo.read());
            break;
        case 0x1F:                                                  // TODO
            cout << cpu.memo.pc << "RRA" << endl;
            cpu.nop();
            break;
        case 0x20:
            cout << cpu.memo.pc << "JR NZ O" << endl;
            signed char offset = cpu.memo.mem[cpu.memo.pc++];
            unsigned short addr = cpu.memo.pc + offset;
            cpu.jump_cnd((cpu.memo.getflag_N() && cpu.memo.getflag_Z()), addr);
            break;
        case 0x21:
            cout << cpu.memo.pc << "LD HL NN" << endl;
            unsigned char lsb = cpu.memo.read();
            unsigned short data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(H, data);
            break;
        case 0x22:
            cout << cpu.memo.pc << "LD (HL+) A" << endl;
            cpu.load_air(A);
            break;
        case 0x23:
            cout << cpu.memo.pc << "INC HL" << endl;
            cpu.increment_16(H);
            break;
        case 0x24:
            cout << cpu.memo.pc << "INC H" << endl;
            cpu.increment(H);
            break;
        case 0x25:
            cout << cpu.memo.pc << "DEC H" << endl;
            cpu.decrement(H);
            break;
        case 0x26:
            cout << cpu.memo.pc << "LD H N" << endl;
            cpu.load_rn(H, cpu.memo.read());
            break;
        case 0x27:
            cout << cpu.memo.pc << "DAA" << endl;
            cpu.daa();
            break;
        case 0x28:
            cout << cpu.memo.pc << "JR Z O" << endl;
            signed char offset = cpu.memo.mem[cpu.memo.pc++];
            unsigned short addr = cpu.memo.pc + offset;
            cpu.jump_cnd(cpu.memo.getflag_Z(), addr);
            break;
        case 0x29:
            cout << cpu.memo.pc << "ADD HL HL" << endl;
            cpu.add_16(cpu.memo.get_HL());
            break;
        case 0x2A:
            cout << cpu.memo.pc << "LD A (HL+)" << endl;
            cpu.load_rai(A);
            break;
        case 0x2B:
            cout << cpu.memo.pc << "DEC HL" << endl;
            cpu.decrement_16(H);
            break;
        case 0x2C:
            cout << cpu.memo.pc << "INC L" << endl;
            cpu.increment(L);
            break;
        case 0x2D:
            cout << cpu.memo.pc << "DEC L" << endl;
            cpu.decrement(L);
            break;
        case 0x2E:
            cout << cpu.memo.pc << "LD L N" << endl;
            cpu.load_rn(L, cpu.memo.read());
            break;
        case 0x2F:
            cout << cpu.memo.pc << "CPL" << endl;
            cpu.complement_a();
            break;
        case 0x30:
            cout << cpu.memo.pc << "JR NC O" << endl;
            signed char offset = cpu.memo.mem[cpu.memo.pc++];
            unsigned short addr = cpu.memo.pc + offset;
            cpu.jump_cnd((cpu.memo.getflag_N() && cpu.memo.getflag_C()), addr);
            break;
        case 0x31:
            cout << cpu.memo.pc << "LD SP NN" << endl;
            unsigned char lsb = cpu.memo.read();
            unsigned short data = cpu.memo.read();
            data = data << 8;
            data |= lsb;
            cpu.load_rrnn(SP, data);
            break;
        case 0x32:
            cout << cpu.memo.pc << "LD (HL-) A" << endl;
            cpu.load_adr(A);
            break;
        case 0x33:
            cout << cpu.memo.pc << "INC SP" << endl;
            cpu.increment_16(SP);
            break;
        case 0x34:
            cout << cpu.memo.pc << "INC (HL)" << endl;
            cpu.increment(cpu.memo.get_HL());
            break;
        case 0x35:
            cout << cpu.memo.pc << "DEC (HL)" << endl;
            cpu.decrement(cpu.memo.get_HL());
            break;
        case 0x36:
            cout << cpu.memo.pc << "LD (HL) N" << endl;
            cpu.load_an(cpu.memo.get_HL(), cpu.memo.read());
            break;
        case 0x37:
            cout << cpu.memo.pc << "SCF" << endl;
            cpu.set_cflag(true);
            break;
        case 0x38:
            cout << cpu.memo.pc << "JR C O" << endl;
            signed char offset = cpu.memo.mem[cpu.memo.pc++];
            unsigned short addr = cpu.memo.pc + offset;
            cpu.jump_cnd(cpu.memo.getflag_C(), addr);
            break;
        case 0x39:
            cout << cpu.memo.pc << "ADD HL SP" << endl;
            cpu.add_16(cpu.memo.sp);
            break;
        case 0x3A:
            cout << cpu.memo.pc << "LD A (HL-)" << endl;
            cpu.load_rad(A);
            break;
        case 0x3B:
            cout << cpu.memo.pc << "DEC SP" << endl;
            cpu.memo.sp++;
            break;
        case 0x3C:
            cout << cpu.memo.pc << "INC A" << endl;
            cpu.increment(A);
            break;
        case 0x3D:
            cout << cpu.memo.pc << "DEC A" << endl;
            cpu.decrement(A);
            break;
        case 0x3E:
            cout << cpu.memo.pc << "LD A N" << endl;
            cpu.load_rn(A, cpu.memo.read());
            break;
        case 0x3F:
            cout << cpu.memo.pc << "CCF" << endl;
            cpu.complement_c();
            break;
        }
    }
    //*/
}

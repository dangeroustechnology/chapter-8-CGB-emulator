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
            unsigned short data = 0x0;
            data = cpu.memo.mem[cpu.memo.pc];
            cpu.memo.pc++;
            data = data << 8;
            data |= cpu.memo.mem[cpu.memo.pc];
            cpu.memo.pc++;
            cpu.load_rrnn(2, data);
            break;
        case 0x02:
            cout << cpu.memo.pc << "LD (BC) A" << endl;

        }
    }
    //*/
}

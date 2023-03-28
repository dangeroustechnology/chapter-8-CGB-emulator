#include "file_reader.h"
#include <string>

#pragma once

class memory
{
public:
    memory();
    file_reader fr;
    unsigned char mem[65536];
    unsigned short pc = 0;
    unsigned char reg[8];
    unsigned char stack[64];
    unsigned short sp = 0;
    bool flags[4] = { false, false, false, false };
    void fill(std::string filename);
    unsigned short get_AF();
    unsigned short get_BC();
    unsigned short get_DE();
    unsigned short get_HL();
    void set_AF(unsigned short data);
    void set_BC(unsigned short data);
    void set_DE(unsigned short data);
    void set_HL(unsigned short data);
    bool getflag_Z();
    bool getflag_N();
    bool getflag_H();
    bool getflag_C();
    void setflag_Z(bool flag);
    void setflag_N(bool flag);
    void setflag_H(bool flag);
    void setflag_C(bool flag);
    unsigned char read();
    unsigned char* dump();
};


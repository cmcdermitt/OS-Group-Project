//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_CPU_H
#define OS_GROUP_PROJECT_CPU_H
#include "Ram.h"
#include <iostream>

class CPU {
    private:
        int Register[16];
        RAM ram;
        bool RD();
        bool WR();
        bool ST(int addr, int regNum);
        bool LW(int addr, int regNum);
        bool MOV(int fromReg, int toReg);
        bool ADD(int S1, int S2, int D);
        bool SUB(int S1, int S2, int D);
        bool DIV(int S1, int S2, int D);
        bool MUL(int S1, int S2, int D);
        bool AND(int S1, int S2, int D);
        bool OR(int S1, int S2, int D);
        bool MOVI(int val, int toReg);
        bool ADDI(int val, int toReg);
        bool DIVI(int val, int toReg);
        bool MULI(int val, int toReg);
        bool JMP(int lineNo);
        bool LDI(int val, int D);
        bool SLT(int S, int B, int D);
        bool SLTI(int S, int val, int D);
        bool HLT();
        bool NOP();
        bool BEQ(int B, int D, int addr);
        bool BNE(int B, int D, int addr);
        bool BEZ(int B, int addr);
        bool BNZ(int B, int addr);
        bool BGZ(int B, int addr);
        bool BLZ(int B, int addr);

    public:
        //code is the instruction being passed; returns the thing
        bool Operate(int code);
        CPU(RAM ram);
        int* dump_registers();
};


#endif //OS_GROUP_PROJECT_CPU_H

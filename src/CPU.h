//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_CPU_H
#define OS_GROUP_PROJECT_CPU_H
#include "Ram.h"
#include <iostream>
#include "PCB.h"
struct Op{
    std::string opType;
    std::string opCode;
    int sReg1;
    int sReg2;
    int dReg;
    int bReg;
    int address;
};
enum mode{debug,production};
class CPU {
    private:
        int Register[16];
        int PC;
        RAM* ram;
        mode cpumode;
        bool RD(int s1, int s2, int address);
        bool WR(int s1, int s2, int address);
        bool ST(int addr, int regNum);
        bool LW(int addr, int regNum);
        bool MOV(int fromReg, int toReg);
        bool ADD(int S1, int S2, int D);
        bool SUB(int S1, int S2, int D);
        bool DIV(int S1, int S2, int D);
        bool MUL(int S1, int S2, int D);
        bool AND(int S1, int S2, int D);
        bool OR(int S1, int S2, int D);
        bool MOVI(int val, int D);
        bool ADDI(int val, int D);
        bool DIVI(int val, int D);
        bool MULI(int val, int D);
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
        void execute(Op op);
    public:
        PCB state;
        bool Operate();
        void loadPCB(PCB *p);
        PCB* storePCB();
        CPU(RAM* ram,mode);
        int* dump_registers();
        void pass(std::string val);
        static void test();

    std::string fetch(int i);

    Op decode(std::string basic_string);



};


#endif //OS_GROUP_PROJECT_CPU_H

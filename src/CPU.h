//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_CPU_H
#define OS_GROUP_PROJECT_CPU_H
#include "Ram.h"
#include <iostream>
#include "PCB.h"
#include <vector>
#include "Cache.h"
struct Op{
    std::string op_type;
    std::string op_code;
    int sreg1;
    int sreg2;
    int dreg;
    int breg;
    int address;
};
enum mode{debug,production};
class CPU {
    private:
        int Register[16];
        int PC;
        RAM* ram;
        mode cpumode;
        Cache cache;
        bool RD(int s1, int s2, int address);
        bool WR(int s1, int s2, int address);
        bool ST(int addr, int breg, int dreg);
        bool LW(int addr, int breg, int dreg);
        bool MOV(int S1, int S2);
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
        bool JMP(int line_no);
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
    bool has_been_used;
    public:
        PCB *state;
        bool Operate();
        void load_pcb(PCB *p);
        PCB* store_pcb();
        CPU(RAM* ram,mode);
        int* dump_registers();
        void pass(std::string val);
        static void test();


    bool get_has_been_used();
    bool set_to_used();

    std::string fetch(int i);

    Op decode(std::string basic_string);



};


#endif //OS_GROUP_PROJECT_CPU_H

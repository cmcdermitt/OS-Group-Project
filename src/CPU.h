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
        bool ST(int regNum);
        bool LW(int addr, int regNum);
        bool MOV(int fromReg, int toReg);

    public:
        //code is the instruction being passed; returns the thing
        bool Operate(int code);
        CPU(RAM ram);
        int* dump_registers() const;
};


#endif //OS_GROUP_PROJECT_CPU_H

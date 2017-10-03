//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_CPU_H
#define OS_GROUP_PROJECT_CPU_H
#include "Ram.h"
#include <iostream>

class CPU {
    private:
        __int32_t Register[16];
        
        
    public:
        bool Operate(int code);
        CPU(RAM ram);
};


#endif //OS_GROUP_PROJECT_CPU_H

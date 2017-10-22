//
// Created by Zach Auzenne on 10/18/17.
//

#ifndef OS_GROUP_PROJECT_DISPATCHER_H
#define OS_GROUP_PROJECT_DISPATCHER_H

#include "CPU.h"
#include "PCB.h"
#include "Ram.h"


class Dispatcher {
private:
    enum threadMode{SINGLE,MULTI};
    RAM *ram;
    PCB *current;
    CPU **cpuList;
    threadMode mode;
    int coreLength;

public:
    Dispatcher(CPU **c, RAM *r, int size);
    PCB *context_switch(PCB *to_load, CPU **c);
    void awaitCPU();
};

#endif //OS_GROUP_PROJECT_DISPATCHER_H

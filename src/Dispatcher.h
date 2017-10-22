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
    Cache* buildCache(PCB *pcb, RAM *r);
    PCB *context_switch(PCB *to_load);
    int awaitCPU();
    Dispatcher(CPU **c, RAM *r, int size);


};

#endif //OS_GROUP_PROJECT_DISPATCHER_H

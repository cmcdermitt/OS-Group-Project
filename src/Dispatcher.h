//
// Created by Zach Auzenne on 10/18/17.
//

#ifndef OS_GROUP_PROJECT_DISPATCHER_H
#define OS_GROUP_PROJECT_DISPATCHER_H

#include "CPU.h"
#include "PCB.h"
#include "Ram.h"
class Semaphore;
class Dispatcher {
private:
    enum threadMode{SINGLE,MULTI};
    RAM *ram;
    PCB *current;
    CPU *cpu;
    threadMode mode;
    int coreLength;
    Semaphore* coreSemaphore;
public:
    Dispatcher(CPU *c, RAM *r, int size);

    void load_PCB(PCB *p); //Singular for now
    PCB *unload_PCB();

    PCB *context_switch(PCB *to_load);


    //void stop_jobs(); //Singular

    void awaitAvailable();
};

#endif //OS_GROUP_PROJECT_DISPATCHER_H

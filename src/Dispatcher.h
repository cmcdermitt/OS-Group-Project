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
    RAM *ram;
    PCB *current;
    CPU *cpu;

public:
    Dispatcher(CPU *c, RAM *r);

    void load_PCB(PCB *p); //Singular for now
    PCB *unload_PCB();

    PCB *context_switch(PCB *to_load);


    //void stop_jobs(); //Singular

};

#endif //OS_GROUP_PROJECT_DISPATCHER_H

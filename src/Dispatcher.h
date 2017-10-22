//
// Created by Zach Auzenne on 10/18/17.
//

#ifndef OS_GROUP_PROJECT_DISPATCHER_H
#define OS_GROUP_PROJECT_DISPATCHER_H

#include "CPU.h"
#include "PCB.h"
#include "Ram.h"


class Semaphore
{
public:
    int val;
    std::mutex j;
    Semaphore(int value);
    void wait();
    void signal();

};

class Dispatcher {
private:
    enum threadMode{SINGLE,MULTI};
    RAM *ram;
    PCB *current;
    CPU *cpu;
    threadMode mode;
    int coreLength;

public:
    Dispatcher(CPU *c, RAM *r, int size);

     //Singular for now
   static void load_PCB(PCB *p);
    static void load_PCB(PCB *p, CPU *c);
    PCB *unload_PCB();

    PCB *context_switch(PCB *to_load, CPU **c);
    static Semaphore* coreSemaphore;

    //void stop_jobs(); //Singular

    void awaitAvailable();

   static void operateCPU(CPU *cpu, RAM *ram, Semaphore *sem);

    static void add_completed_job(int i);
    static void remove_completed_job(int i);

    static std::vector<int> *completed_jobs;
};

#endif //OS_GROUP_PROJECT_DISPATCHER_H

//
// Created by Charlie McDermitt on 10/10/2017.
//

#ifndef OS_GROUP_PROJECT_LT_SCHEDULER_H
#define OS_GROUP_PROJECT_LT_SCHEDULER_H

#include "Disk.h"
#include "Ram.h"
#include "PCB.h"
#include <list>
#include <vector>

struct free_ram {
    int position;
    int offset;
};

class Scheduler {
private:
    std::list<PCB*> pcbs;
    Disk disk;
    RAM ram;
    free_ram ram_space;
    std::list<PCB*> ready_queue;


    void get_ram_start(PCB *p); //sets *p->ramStartAddress
    void load_pcb(PCB *p, RAM &r); //puts PCB in RAM
    void remove_pcb(PCB *p, RAM &r);



public:
    Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use);
    void lt_sched(std::list<PCB*> pcbs, Disk& disk, RAM& ram);
    PCB* lt_get_next_pcb(std::list<PCB*> pcbs, bool is_priority = false); //returns pointer to next PCB
    void st_sched(std::list<PCB*> pcbs, Disk& disk, RAM& ram);//Might have to add in a parameter for dispatcher as well, or just call to a function, not sure yet
};

#endif //OS_GROUP_PROJECT_LT_SCHEDULER_H

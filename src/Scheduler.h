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
    free_ram(int pos, int off) {position = pos; offset = off;}
};

class Scheduler {
private:
    std::list<PCB*> pcbs;
    Disk disk;
    RAM* ram;
    std::list<free_ram> ram_space;
    std::list<PCB*> ready_queue;


    bool get_ram_start(PCB *p); //sets *p->ramStartAddress
    void load_pcb(PCB *p, RAM &r); //puts PCB in RAM
    void remove_pcb(PCB *p, RAM &r);



public:
    Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use);
    void lt_sched();
    PCB* lt_get_next_pcb(std::list<PCB*> pcbs, bool is_priority = false); //returns pointer to next PCB
    void st_sched();
    void lt_test();
};


//returns true if p1 has a smaller job_id - used for sorting
bool comp_fifo(PCB* p1, PCB* p2);
//returns true if p1 has higher priority than p2 - used for sorting
bool comp_priority(PCB* p1, PCB* p2);


#endif //OS_GROUP_PROJECT_LT_SCHEDULER_H

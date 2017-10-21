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
#include "Scheduler.h"
#include "Dispatcher.h"

struct free_ram {
    int position;
    bool is_free;

    free_ram(int pos, bool is_free) {
        position = pos;
        is_free = false;
    }
};

class Scheduler {
private:
    std::list<PCB*> pcbs;
    Disk disk;
    RAM *ram;
    Dispatcher *disp;
    std::list<free_ram> ram_space;
    std::list<PCB*> ready_queue;
    enum SCHEDULING_TYPE {FIFO, PRIORITY, SJF};
    const SCHEDULING_TYPE sched_type = SCHEDULING_TYPE::FIFO;


    bool get_ram_start(PCB *p); //sets *p->ramStartAddress to an open space in RAM
    void load_pcb(PCB *p); //puts PCB in RAM
    void remove_pcb(PCB *p); //removes PCB from RAM
    void clean_ram_space();

    void describe_ram_space();

    bool lt_sched_complete;
    int jobsAllocated;
    int jobsCompleted;


public:
    Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use, Dispatcher *dispatcher);

    void lt_sched(bool *still_has_work);

    PCB *lt_get_next_pcb(std::list<PCB*> pcbs); //returns pointer to next PCB
    void st_sched(bool *st_still_has_work);

    void lt_test();
};


//returns true if p1 has a smaller job_id - used for sorting
bool comp_fifo(PCB *p1, PCB *p2);

//returns true if p1 has higher priority than p2 - used for sorting
bool comp_priority(PCB *p1, PCB *p2);


#endif //OS_GROUP_PROJECT_LT_SCHEDULER_H

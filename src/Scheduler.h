//
// Created by Charlie McDermitt on 10/10/2017.
//

#ifndef OS_GROUP_PROJECT_LT_SCHEDULER_H
#define OS_GROUP_PROJECT_LT_SCHEDULER_H

#include "Disk.h"
#include "Ram.h"
#include "PCB.h"
#include <queue>
#include <map>

namespace scheduler {
    std::deque<PCB> ready_queue; //using deque for access to more functions and iterators
    std::vector<std::vector<int>> free_ram; //2D vector - first is start address, second is offset

    void lt_sched(std::list<PCB> pcbs, Disk disk, RAM ram);

    void st_sched(std::list<PCB> pcbs, Disk disk, RAM ram);//Might have to add in a parameter for dispatcher as well, or just call to a function, not sure yet
}

#endif //OS_GROUP_PROJECT_LT_SCHEDULER_H

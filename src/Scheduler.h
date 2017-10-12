//
// Created by Charlie McDermitt on 10/10/2017.
//

#ifndef OS_GROUP_PROJECT_LT_SCHEDULER_H
#define OS_GROUP_PROJECT_LT_SCHEDULER_H

#include "Disk.h"
#include "Ram.h"
#include "PCB.h"
#include <queue>

namespace scheduler {
    std::queue<PCB> ready_queue;
    std::list<int> free_space;

    void lt_sched(std::list<PCB> pcbs, Disk disk, RAM ram);
}

#endif //OS_GROUP_PROJECT_LT_SCHEDULER_H

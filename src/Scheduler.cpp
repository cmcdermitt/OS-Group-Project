//
// Created by Charlie McDermitt on 10/10/2017.


#include "Scheduler.h"

//FCFS for now - add priority later
void scheduler::lt_sched(std::list<PCB> pcbs, Disk disk, RAM ram)
{
    for (std::list<PCB>::iterator cursor = pcbs.begin(); cursor != pcbs.end(); ++cursor)
    {
       /*if (ram used + pcc.total_size < RAM.SIZE)
        {
            ready_queue.push(current PCB (will cursor work?));
            string temp;
            for (int j = 0; j < limit; j++)
            {
               temp = disk.read(start + j);
               ram.write(temp, start + j);
            }
        } else {
            break; //quit when next job won't fit - add to for loop later/switch to while?
        }

        */
    }
}




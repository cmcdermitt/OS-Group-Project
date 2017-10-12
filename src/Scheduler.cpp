//
// Created by Charlie McDermitt on 10/10/2017.


#include "Scheduler.h"

//FCFS for now - add priority later
void scheduler::lt_sched(std::list<PCB> pcbs, Disk disk, RAM ram)
{
    for (std::list<PCB>::iterator cursor = pcbs.begin(); cursor != pcbs.end(); ++cursor)
    {
        //todo: find appropriate starting location in RAM
        //set it to cursor->job_address
        //if there is no location, break




        //copy each item in the job to RAM and put it on the ready queue
        std::string temp;
        for (int j = 0; j < cursor->total_size; j++)
        {
            temp = disk.read(cursor->job_disk_address + j);
            ram.write(cursor->job_address + j, temp);
        }
        ready_queue.push(*cursor);


    }
}




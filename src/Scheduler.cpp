//
// Created by Charlie McDermitt on 10/10/2017.


#include "Scheduler.h"

Scheduler::Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use) {
    pcbs = pcb_list;
    disk = disk_in_use;
    ram = ram_in_use;
}

//TODO: test Scheduler, need loader to test
//returns pointer to next PCB
PCB* Scheduler::lt_get_next_pcb(std::list<PCB*> pcbs, bool is_priority) {
    if(is_priority) {
    } else {
        bool found = false;
        for (std::list<PCB*>::iterator cursor = pcbs.begin(); cursor != pcbs.end(); ++cursor) {
            for (std::list<PCB*>::iterator it = ready_queue.begin(); it != ready_queue.end(); ++it) {
                if ((*cursor)->job_id == (*it)->job_id)
                    found = true;
            }
            if (found) {
                return *cursor;
            }
        }
    }
}


void get_ram_start(PCB *p) {

}

void load_pcb(PCB *p, RAM &r); //puts PCB in RAM
void remove_pcb(PCB *p, RAM &r);


//FCFS for now - add priority later
void Scheduler::lt_sched(std::list<PCB*> pcbs, Disk& disk, RAM& ram) {
//    //if the ready queue is empty, there's nothing in RAM, so all the space is free
//    //the ready queue should always be empty the first time lt_sched is called
//    if (ready_queue.size() == 0) {
//        free_ram.clear();
//        free_ram[0][0] = 0;
//        free_ram[0][1] = ram.SIZE;
//    }
//
//    PCB next;
//    //find next job which isn't in ready_queue
//    bool found = false;
//    for (std::list<PCB*>::iterator *cursor = pcbs.begin(); cursor != pcbs.end(); ++cursor) {
//
//        for (std::list<PCB*>::iterator it = ready_queue.begin(); it != ready_queue.end(); ++it) {
//            if (cursor->job_id = it->job_id)
//                found = true;
//        }
//        if (found) {
//            next = *cursor;
//            break; //if we have the next one, leave the loop
//        }
//    }
//
//    //if there isn't a next job (i.e. all jobs are in ready_queue or no jobs left), return - nothing else to schedule
//    if (!found)
//        return;
//
//    //find free space for job and set next.job_address
//    //currently first-fit method
//    int i = 0;
//    bool is_space = false;
//    while (i < free_ram.size() && !is_space) {
//        if (free_ram[i][1] >= next.total_size)
//        {
//            is_space = true;
//            next.job_address = free_ram[i][0];
//
//            //modify free_ram to take out space process uses
//            if (free_ram[i][1] == next.total_size)
//                free_ram.erase(free_ram.begin() + i);
//            else //free_ram[i][1] > next.total_size
//                free_ram[i][1] = free_ram[i][1] + next.total_size;
//        }
//        ++i;
//    }
//
//    //if there's no space for the next job, return - can't schedule it
//    if (!is_space)
//        return;
//
//
//    //copy each item in the job to RAM and put it on the ready queue
//    std::string temp;
//    for (int j = 0; j < next.total_size; j++) {
//        temp = disk.read(next.job_disk_address + j);
//        ram.write(next.job_address + j, temp);
//    }
//    ready_queue.push_front(next);

}



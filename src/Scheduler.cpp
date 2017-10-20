//
// Created by Charlie McDermitt on 10/10/2017.
#include <vector>
#include "Scheduler.h"
#include "Log.h"
#include "Utility.h"

// Initalizes the Scheduler and gives it the job list, disk, ram, and dispatcher
Scheduler::Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use, Dispatcher *dispatcher) {
    pcbs = pcb_list;
    disk = disk_in_use;
    ram = &ram_in_use;
    disp = dispatcher;
    ram_space.push_front(free_ram(0, true));
    jobsAllocated = 0;
    jobsCompleted = 0;
    lt_sched_complete = false;
}

// Long Term Scheduler
void Scheduler::lt_sched(bool *still_has_work) {
    PCB *temp;
    // Continues until no more jobs can be loaded or there are no more jobs
    while (true) {
       // describe_ram_space();
        temp = lt_get_next_pcb(pcbs);
        if (temp == nullptr)
        {
            *still_has_work = false;
            break;
        }

        if (!get_ram_start(temp)) {
            std::cout << "DID NOT GET RAM START" << std::endl;
            break;
        }
            load_pcb(temp, *ram);
            jobsAllocated++;
        Debug::debug(Debug::DEBUG_SCHEDULER, "YAllocated " + std::to_string(jobsAllocated));
    }
}

// Short Term Scheduler
void Scheduler::st_sched(bool *st_still_has_work)
{
    std::cout << "\nREADY QUEUE START SIZE " << ready_queue.size();
    PCB *temp;

    ready_queue.sort(comp_fifo);

    if(!ready_queue.empty())
    {
        temp = ready_queue.front(); //Access first sorted PCB

        if(temp != nullptr) {
            temp = disp->context_switch(temp);
            //Send PCB to Dispatcher
            //Receive PCB on either completion or interrupt

            remove_pcb(temp, ram);
            jobsCompleted++;
            Debug::debug(Debug::DEBUG_SCHEDULER, "GCompleted " + std::to_string(jobsCompleted));

        }
    }
    else
    {
        *st_still_has_work = false;
    }
    std::cout << "\nREADY QUEUE END SIZE " << ready_queue.size();
}

//returns pointer to next PCB, returns null pointer if no next PCB
PCB* Scheduler::lt_get_next_pcb(std::list<PCB*> pcbs, bool is_priority) {
    if(is_priority)
    {
        PCB *temp;
        int priority = 1000;
        for(PCB *p : pcbs)
        {
            if(p->state == PCB::PROCESS_STATUS::NEW && p->job_pri < priority)
            {
                priority = p->job_pri;
                temp = p;
            }
        }
        if(priority != 1000)
        {
            return temp;
        }
        return  nullptr;
    }

    else {

        PCB* next = new PCB();
        next->job_id = -1;
        bool in_ready_queue = false;
//        for (std::list<PCB*>::iterator cursor = pcbs.begin(); cursor != pcbs.end(); ++cursor) {
//            for (std::list<PCB*>::iterator it = ready_queue.begin(); it != ready_queue.end(); ++it) {
//                if ((*cursor)->job_id == (*it)->job_id)
//                    in_ready_queue = true;
//            }
//            if (!in_ready_queue) {
//                next = *cursor;
//                return next; //returns a pointer to a PCB in pcbs
//            }
//        }
        for(PCB *p : pcbs)
        {
            if(p->state == PCB::PROCESS_STATUS::NEW)
            {
                return p;
            }
        }
        return nullptr;
    }
}

void Scheduler::describe_ram_space() {

    Debug::debug(Debug::DEBUG_SCHEDULER, "Describing Ram Space \n");
    for(free_ram f : ram_space)
    {
        Debug::debug(Debug::DEBUG_SCHEDULER, "The Position is " + std::to_string(f.position));
        Debug::debug(Debug::DEBUG_SCHEDULER, "The status of its freedom " + Utility::boolToString(f.is_free));
    }

}

void Scheduler::clean_ram_space() {
    std::list<free_ram>::iterator it = ram_space.begin();
    while(it != ram_space.end())
    {
     if(it->is_free )
         while(std::next(it)->is_free &&  std::next(it) != ram_space.end()) {
            ram_space.erase(std::next(it));
         }
        it++;
    }
}

//sets p->job_ram_address to start location
//if there's no room, p->job_ram_address will stay unset
bool Scheduler::get_ram_start(PCB *p) {

    clean_ram_space();
    bool is_space = false;
    std::list<free_ram>::iterator it = ram_space.begin();
    int nextPos = 0;
    int currentPos = 0;


    while (it != ram_space.end() && !is_space) {
        if (it->is_free)
        {
            currentPos = it->position;
            // If we have to insert it at the end
            if(std::next(it) == ram_space.end()) {

                if (RAM::SIZE - it->position == p->total_size)
                {
                    p->job_ram_address = it->position;
                    it->is_free = false;
                    is_space = true;
                    Debug::debug(Debug::DEBUG_SCHEDULER, "Fit exactly at end");
                    return is_space;

                }

                else if(RAM::SIZE - it->position > p->job_size){
                    // We give part of that to a new used ram_space
                    free_ram *to_be_added = new free_ram(it->position, false);
                    p->job_ram_address = it->position;
                    it->position = it->position + p->total_size;
                    ram_space.insert(it, *to_be_added);
                    is_space = true;
                    Debug::debug(Debug::DEBUG_SCHEDULER, "Fit inside at end");
                    return is_space;
                }

                    // There is not enough space at the end of RAM
                else{
                    return is_space;
                }

            }

                // If we have to insert it at any other place
            else
            {
               currentPos = it->position;
               nextPos = std::next(it)->position;
               if(nextPos - currentPos == p->total_size)
               {
                   it->is_free = false;
                   p->job_ram_address = currentPos;
                   is_space = true;
                   Debug::debug(Debug::DEBUG_SCHEDULER, "Fit exactly somewhere in the middle");
                   return is_space;
               }
                else if (nextPos - currentPos > p->total_size){
                   p->job_ram_address = currentPos;
                   is_space = true;
                   it->is_free = false;
                   free_ram *to_be_added = new free_ram(currentPos + p->total_size, true);
                   ram_space.insert(std::next(it), *to_be_added);
                   is_space = true;
                   Debug::debug(Debug::DEBUG_SCHEDULER, "Fit partially somewhere in the middle");
                   return is_space;

               }

            }

        }
        ++it;
    }
  //  std::cout << "Current Position:\t" << ram_space[0].position << "\nCurrent Offset\t" << ram_space[0].offset << std::endl;
    return is_space;

}

void Scheduler::load_pcb(PCB *p, RAM &r) { //puts PCB in RAM and ready_queue deal with sorting later
    static int times = 0;
    times++;
    //std::cout << "RUNNING OUT OF TIME:\t" << times << std::endl;
    //std::cout << "START HERE:\t" << p->job_ram_address << std::endl;
    ready_queue.push_back(p);
    p->wait_time->turnOff();
    p->state = PCB::PROCESS_STATUS::READY;
    int ramStart = p->job_ram_address;
    int diskStart = p->data_disk_address;
    std::vector<std::string> push_list = std::vector<std::string>();
    // Put on ram
    for(int i = 0; i < p->total_size; i++) { // may need to be <=
        push_list.push_back(disk.read(diskStart + i));
    }
        r.write(ramStart, push_list);
        //ram->write(i + ramStart, disk.read(i + diskStart));

}


// Removes PCB form
// Needs Testing because written at 3:45 in morning
void Scheduler::remove_pcb(PCB *p, RAM *r)
{
    if (p->state == PCB::PROCESS_STATUS::READY) {
        return;
        //return b/c nothing to remove - PCB still needs to run
    }

    if (p->state == PCB::PROCESS_STATUS::BLOCKED) {
        //send p to back to RQ - maybe not right idea but works for now
        ready_queue.pop_front();
        ready_queue.push_back(p);
    }

    if (p->state == PCB::PROCESS_STATUS::COMPLETED) {
        //write 0s over process location in RAM
        std::vector<std::string> s = std::vector<std::string>(p->total_size, "0");
        r->write(p->job_ram_address, s);
        std::list<free_ram>::iterator ramIterator = std::list<free_ram>::iterator();
        ramIterator = ram_space.begin();
        while(ramIterator->position != p->job_ram_address && ramIterator != ram_space.end())
            ramIterator++;
        ramIterator->is_free = true;
        std::list<PCB*>::iterator queueIterator = std::list<PCB*>::iterator();
        queueIterator = ready_queue.begin();
        while((*queueIterator)->job_id != p->job_id)
            queueIterator++;
        ready_queue.erase(queueIterator);

    }
    }



void Scheduler::lt_test() {
    ready_queue.sort(comp_priority);
    printPCBs(ready_queue);

    /*for(free_ram r : ram_space)
    {
        std::cout << "Position:\t" << r.position << "\nOffset:\t" << r.offset << std::endl;
    }

    for(int i = 0; i < 1024; i++)
    {
        std::cout << ram->read(i) << std::endl;
    }*/


}

//returns true if p1 has a smaller job_id - used for sorting
bool comp_fifo(PCB* p1, PCB* p2) {
    return p1->job_id < p2->job_id;
}
//returns true if p1 has lower priority than p2 - used for sorting
bool comp_priority(PCB* p1, PCB* p2) {
    return p1->job_pri > p2->job_pri;
}

//OLD FUNCTION
//void Scheduler::lt_sched(std::list<PCB*> pcbs, Disk& disk, RAM& ram) {
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
//    //find free space for job and set next.job_ram_address
//    //currently first-fit method
//    int i = 0;
//    bool is_space = false;
//    while (i < free_ram.size() && !is_space) {
//        if (free_ram[i][1] >= next.total_size)
//        {
//            is_space = true;
//            next.job_ram_address = free_ram[i][0];
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
//        ram.write(next.job_ram_address + j, temp);
//    }
//    ready_queue.push_front(next);
//
//}





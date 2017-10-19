//
// Created by Charlie McDermitt on 10/10/2017.
#include <vector>

#include "Scheduler.h"


Scheduler::Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use, Dispatcher *dispatcher) {
    pcbs = pcb_list;
    disk = disk_in_use;
    ram = &ram_in_use;
    disp = dispatcher;
    ram_space.push_front(free_ram(0, ram->SIZE));
}

void Scheduler::lt_sched() {
    PCB *temp;
    int count = 0;
// Continues until no more jobs can be loaded or there are no more jobs
    while(true)
    {
        temp = lt_get_next_pcb(pcbs);
        if(temp == nullptr)
            break;
        if(!get_ram_start(temp))
            break;
        load_pcb(temp, *ram);
        count++;
    }
    std::cout << "count:\t" << count << std::endl;

}



void Scheduler::st_sched()
{
    PCB *temp;

    ready_queue.sort(comp_fifo);

    if(!ready_queue.empty())
    {
        printPCBs(ready_queue);
        temp = ready_queue.front(); //Access first sorted PCB

        if(temp != nullptr) {
            temp = disp->context_switch(temp);
            //Send PCB to Dispatcher
            //Receive PCB on either completion or interrupt
            std::cout << std::endl << "PERFORMED JOB(S): " << std::endl;
            std::cout << temp->job_id << "\t" << temp->state << std::endl;
            std::cout << temp->registers;


            if (temp->state == PCB::PROCESS_STATUS::COMPLETED)
                ready_queue.pop_front();
            //remove_pcb(temp, *ram); //Not written yet
            if (temp->state == PCB::PROCESS_STATUS::BLOCKED)
                ready_queue.pop_front();
            ready_queue.push_back(temp); //Places PCB at back of queue to reassess next go around
        }
    }
}

//TODO: test Scheduler, need loader to test
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


//sets p->job_ram_address to start location
//if there's no room, p->job_ram_address will stay unset
bool Scheduler::get_ram_start(PCB *p) {
    bool is_space = false;
    std::list<free_ram>::iterator it = ram_space.begin();
    while (it != ram_space.end() && !is_space) {
        if (it->offset >= p->total_size)
        {
            is_space = true;
            p->job_ram_address = it->position;

            //modify ram_space to take out space process uses
            if (it->offset == p->total_size) {
                ram_space.erase(it++);
            }
            else //free_ram[i].offset > next.total_size
            {
                it->position = it->position + p->total_size;
                it->offset = it->offset - p->total_size;
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
    p->state = PCB::PROCESS_STATUS::READY;
    int ramStart = p->job_ram_address;
    int diskStart = p->data_disk_address;
    std::vector<std::string> push_list = std::vector<std::string>();
    // Put on ram
    for(int i = 0; i < p->total_size; i++) { // may need to be <=
        push_list.push_back(disk.read(diskStart + i));
    }
        r.write(diskStart, push_list);
        //ram->write(i + ramStart, disk.read(i + diskStart));

}


// Removes PCB form
// Needs Testing because written at 3:45 in morning
void Scheduler::remove_pcb(PCB *p, RAM &r)
{
std::vector<std::string> s = std::vector<std::string>(p->total_size, "0") ;
r.write(p->job_ram_address, s);
    std::list<free_ram>::iterator ramIterator = std::list<free_ram>::iterator();
    ramIterator = ram_space.begin();
    bool foundSpot = false;
    while(!foundSpot)
    {
        if((ramIterator->position >= p->job_disk_address)) {
            ramIterator->offset = ramIterator->offset + p->job_size;
            foundSpot = true;
        }
        ramIterator++;
    }

    std::list<PCB*>::iterator readyIt = std::list<PCB*>::iterator();
     readyIt = ready_queue.begin();

    while(readyIt != ready_queue.end() )
    {
        if((*readyIt)->job_id == p->job_id)
        {
            ready_queue.erase(readyIt);
            break;
        }


    }

    p->state = PCB::PROCESS_STATUS::COMPLETED;

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





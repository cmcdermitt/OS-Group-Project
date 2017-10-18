//
// Created by Charlie McDermitt on 10/10/2017.


#include "Scheduler.h"

Scheduler::Scheduler(std::list<PCB*> &pcb_list, Disk &disk_in_use, RAM &ram_in_use) {
    pcbs = pcb_list;
    disk = disk_in_use;
    ram = &ram_in_use;
    ram_space.push_back(free_ram ());
    ram_space[0].position = 0;
    ram_space[0].offset = ram->SIZE;

    
}

void Scheduler::lt_sched()
{
    PCB *temp;
    int count = 0;
// Continues until no more jobs can be loaded or there are no more jobs
    while(1)
    {
       temp = lt_get_next_pcb(pcbs);
        if(temp == nullptr)
            break;
       if(!get_ram_start(temp))
           break;
        load_pcb(temp, *ram);
        count++;
    }
    // std::cout << "count:\t" << count << std::endl;

}

void Scheduler::st_sched()
{
    PCB *temp;
    while(!ready_queue.empty()) //Ends on empty ready queue
    {
        temp = ready_queue.front(); //Access first sorted PCB
        ready_queue.pop_front();

        if(temp == nullptr) //Making sure it's not null
            break;

        //temp = Dispatcher(temp);  //Send PCB to Dispatcher
        //Receive PCB on either completion or interrupt

        if (temp->state == PCB::PROCESS_STATUS::COMPLETED)
            remove_pcb(temp, *ram); //Not written yet
        if (temp->state == PCB::PROCESS_STATUS::BLOCKED)
            ready_queue.push_front(temp); //Places PCB back at the front to reassess next go around
        //Will eventually have a method for resorting PCBs on return based on priority and job_size

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
    int i = 0;
    bool is_space = false;
    while (i < ram_space.size() && !is_space) {
        if (ram_space[i].offset >= p->total_size)
        {
            is_space = true;
            p->job_ram_address = ram_space[i].position;

            //modify ram_space to take out space process uses
            if (ram_space[i].offset == p->total_size) {
                ram_space.erase(ram_space.begin() + i);
            }
            else //free_ram[i].offset > next.total_size
            {
                ram_space[i].position = ram_space[i].position + p->total_size;
                ram_space[i].offset = ram_space[i].offset - p->total_size;
            }
        }
        ++i;
    }
  //  std::cout << "Current Position:\t" << ram_space[0].position << "\nCurrent Offset\t" << ram_space[0].offset << std::endl;
    return is_space;

}

void Scheduler::load_pcb(PCB *p, RAM &r) { //puts PCB in RAM and ready_queue deal with sorting later
    static int times = 0;
    times++;
    std::cout << "RUNNING OUT OF TIME:\t" << times << std::endl;
    std::cout << "START HERE:\t" << p->job_ram_address << std::endl;
    ready_queue.push_back(p);
    p->state = PCB::PROCESS_STATUS::READY;
    int ramStart = p->job_ram_address;
    int diskStart = p->data_disk_address;

    // Put on ram
    for(int i = 0; i < p->total_size; i++){ // may need to be <=
    ram->write(i + ramStart, disk.read(i + diskStart));
    }
}

void Scheduler::remove_pcb(PCB *p, RAM &r)
{

}

void Scheduler::lt_test() {
    for(free_ram r : ram_space)
    {
        std::cout << "Position:\t" << r.position << "\nOffset:\t" << r.offset << std::endl;
    }

    for(int i = 0; i < 1024; i++)
    {
        std::cout << ram->read(i) << std::endl;
    }


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



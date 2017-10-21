//
// Created by Charlie McDermitt on 10/10/2017.
#include <vector>
#include "Scheduler.h"
#include "Log.h"
#include "Utility.h"

// Initalizes the Scheduler and gives it the job list, disk, ram, and dispatcher
Scheduler::Scheduler(std::list<PCB *> &pcb_list, Disk &disk_in_use, RAM &ram_in_use, Dispatcher *dispatcher) {
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
        if (temp == nullptr) {
            *still_has_work = false;
            break;
        }

        if (!get_ram_start(temp)) {
            std::cout << "DID NOT GET RAM START" << std::endl;
            break;
        }
        load_pcb(temp);
        jobsAllocated++;
        Debug::debug(Debug::DEBUG_SCHEDULER, "YAllocated " + std::to_string(jobsAllocated));
    }
}

// Short Term Scheduler
void Scheduler::st_sched(bool *st_still_has_work) {
    std::cout << "\nREADY QUEUE START SIZE " << ready_queue.size();
    PCB *temp;

    if (sched_type == SCHEDULING_TYPE::FIFO)
        ready_queue.sort(comp_fifo);
    else if (sched_type == SCHEDULING_TYPE::PRIORITY)
        ready_queue.sort(comp_priority);

    if (!ready_queue.empty()) {
        temp = ready_queue.front(); //Access first PCB in ready queue

        if (temp != nullptr) {
            temp = disp->context_switch(temp); //send PCB to dispatcher and get it back when done

            remove_pcb(temp); //remove_pcb handles unloading or return to RQ
            jobsCompleted++;
            Debug::debug(Debug::DEBUG_SCHEDULER, "GCompleted " + std::to_string(jobsCompleted));
        }
    } else {//nothing is in the ready queue
        *st_still_has_work = false;
    }
    std::cout << "\nREADY QUEUE END SIZE " << ready_queue.size();
}

//returns pointer to next PCB, returns null pointer if no next PCB
PCB* Scheduler::lt_get_next_pcb(std::list<PCB *> pcbs) {
    if (sched_type == SCHEDULING_TYPE::PRIORITY) {
        PCB *temp;
        int priority = 1000;

        //find new PCB with LOWEST? priority?
        for (PCB *p : pcbs) {
            if (p->state == PCB::PROCESS_STATUS::NEW && p->job_pri < priority) {
                priority = p->job_pri;
                temp = p;
            }
        }

        if (priority != 1000) { //i.e. if priority has been set by finding a valid PCB
            return temp;
        }

        return nullptr; //if there's no job to run
    } else { //if FIFO
        PCB *next = new PCB();
        next->job_id = -1;

        //find next new PCB
        for (PCB *p : pcbs) {
            if (p->state == PCB::PROCESS_STATUS::NEW) {
                return p;
            }
        }
        return nullptr;
    }
}

//sets p->job_ram_address to start location
//if there's no room, p->job_ram_address will stay unset
bool Scheduler::get_ram_start(PCB *p) {

    clean_ram_space(); //combines contiguous free spaces

    bool is_space = false;
    std::list<free_ram>::iterator it = ram_space.begin();
    int next_pos = 0;
    int current_pos = 0;


    while (it != ram_space.end() && !is_space) { //while we haven't found anything and we aren't at the end of ram_space
        if (it->is_free) //if it is a free space
        {
            current_pos = it->position; //store current position


            if (std::next(it) == ram_space.end()) { //if we're at the end of the ram space list

                if (RAM::SIZE - it->position ==
                    p->total_size) //if the free space at the end is exactly the size of the PCB
                {
                    //set the address and that the space is used, then return
                    p->job_ram_address = it->position;
                    it->is_free = false;
                    is_space = true;
                    Debug::debug(Debug::DEBUG_SCHEDULER, "Fit exactly at end");
                    return is_space;

                } else if ((RAM::SIZE - it->position) >
                           p->job_size) { //if we're at the end of the list and there's more than enough space

                    //set address, insert new space, and return
                    p->job_ram_address = current_pos;
                    is_space = true;
                    it->is_free = false;
                    free_ram *to_be_added = new free_ram(current_pos + p->total_size, true); //new space starts in address after end of p
                    to_be_added->position = current_pos + p->total_size;
                    to_be_added->is_free = true;
                    ram_space.insert(std::next(it), *to_be_added);
                    is_space = true;
                }

                    // There is not enough space at the end of RAM, so return false
                else {
                    return is_space;
                }

            } else { //if we aren't at the end of the list

                next_pos = std::next(it)->position; //store position of next space (current_pos initialized at top)

                if (next_pos - current_pos == p->total_size) {//if there's exactly enough room before the next process
                    //set is_free and address, then return
                    it->is_free = false;
                    p->job_ram_address = current_pos;
                    is_space = true;
                    Debug::debug(Debug::DEBUG_SCHEDULER, "Fit exactly somewhere in the middle");
                    return is_space;

                } else if (next_pos - current_pos > p->total_size) { //if there's more than enough room
                    //set is_free and address, create and insert new space, and return
                    p->job_ram_address = current_pos;
                    is_space = true;
                    it->is_free = false;
                    free_ram *to_be_added = new free_ram(current_pos + p->total_size + 1, true); //new space starts in address after end of p
                    to_be_added->is_free = true;
                    to_be_added->position = current_pos + p->total_size;
                    ram_space.insert(std::next(it), *to_be_added);
                    is_space = true;
                    Debug::debug(Debug::DEBUG_SCHEDULER, "Fit partially somewhere in the middle");
                    return is_space;
                } //if we can't fit in this space, we loop again since we aren't at the end yet
            }
        }
        ++it;
    }
    //  std::cout << "Current Position:\t" << ram_space[0].position << "\nCurrent Offset\t" << ram_space[0].offset << std::endl;
    return is_space;

}

void Scheduler::load_pcb(PCB *p) { //puts PCB in RAM and ready_queue deal with sorting later
    static int times = 0;
    times++;
    //std::cout << "RUNNING OUT OF TIME:\t" << times << std::endl;
    //std::cout << "START HERE:\t" << p->job_ram_address << std::endl;
    ready_queue.push_back(p);
    p->wait_time->turn_off();
    p->state = PCB::PROCESS_STATUS::READY;

    int ram_start = p->job_ram_address;
    int disk_start = p->job_disk_address;
    std::vector<std::string> push_list = std::vector<std::string>();
    // Put on ram
    for (int i = 0; i < p->total_size; i++) { // may need to be <=
        push_list.push_back(disk.read(disk_start + i));
    }
    ram->write(ram_start, push_list);
    //ram->write(i + ram_start, disk.read(i + disk_start));

}


// Removes PCB from RAM, or puts back on ready queue if not completed
// Needs Testing because written at 3:45 in morning
void Scheduler::remove_pcb(PCB *p) {
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
        //should copy PCB data to disk

        //write 0s over process location in RAM
        std::vector<std::string> s = std::vector<std::string>(p->total_size, "0");
        ram->write(p->job_ram_address, s);

        //free PCB's entry in ram_space
        std::list<free_ram>::iterator ram_iterator = std::list<free_ram>::iterator();
        ram_iterator = ram_space.begin();
        while (ram_iterator->position != p->job_ram_address && ram_iterator != ram_space.end())
            ram_iterator++;
        ram_iterator->is_free = true;

        //remove PCB's entry in ready_queue
        std::list<PCB*>::iterator queue_iterator = std::list<PCB *>::iterator();
        queue_iterator = ready_queue.begin();
        while ((*queue_iterator)->job_id != p->job_id)
            queue_iterator++;
        ready_queue.erase(queue_iterator);

    }
}

void Scheduler::describe_ram_space() { //prints ram_space
    Debug::debug(Debug::DEBUG_SCHEDULER, "Describing Ram Space \n");
    for (free_ram f : ram_space) {
        Debug::debug(Debug::DEBUG_SCHEDULER, "The Position is " + std::to_string(f.position));
        Debug::debug(Debug::DEBUG_SCHEDULER, "The status of its freedom " + Utility::bool_to_string(f.is_free));
    }
}

void Scheduler::clean_ram_space() { //combines contiguous free spaces in RAM
    std::list<free_ram>::iterator it = ram_space.begin();
    while (it != ram_space.end()) {
        if (it->is_free)
            while (std::next(it) != ram_space.end() && std::next(it)->is_free) {
                ram_space.erase(std::next(it));
            }
        it++;
    }
}

void Scheduler::lt_test() {
    ready_queue.sort(comp_priority);
    print_pcbs(ready_queue);

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
bool comp_fifo(PCB *p1, PCB *p2) {
    return p1->job_id < p2->job_id;
}

//returns true if p1 has lower priority than p2 - used for sorting
bool comp_priority(PCB *p1, PCB *p2) {
    return p1->job_pri > p2->job_pri;
}
//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"
#include "Log.h"
#include <mutex>
#include <thread>

class Semaphore{
    int val;
    std::mutex j;
public: Semaphore(int val){
        this->val = val;
    }
    void wait(){
        j.lock();
        while(val<=0);
        val--;
        j.unlock();
    }
    void signal(){
        j.lock();
        val++;
        j.unlock();
    }
};



Dispatcher::Dispatcher(CPU *c, RAM *r,int size=1) {
    ram = r;
    if(size==1){cpu = c; this->mode=SINGLE;}
    else{
        cpu = c;
        this->mode=MULTI;
        coreLength = size;
        coreSemaphore = new Semaphore(coreLength);
    }

}

void Dispatcher::load_PCB(PCB *p) {
    current = p;
    current->wait_time->turn_off();
    current->wait_time->record_data();
    current->wait_time->record_log();
    current->comp_time->turn_on();
    current->state = PCB::PROCESS_STATUS::RUNNING;
    cpu->load_pcb(p);
}

PCB *Dispatcher::unload_PCB() {

    PCB *temp = cpu->store_pcb();
    temp->comp_time->turn_off();
    temp->comp_time->record_data();
    temp->comp_time->record_log();
    temp->state = PCB::PROCESS_STATUS::COMPLETED;
    Debug::debug(Debug::DISPATCHER, "Unloading");
    return temp;
}

PCB *Dispatcher::context_switch(PCB *to_load) {
    /* get PCB
     * Wait for a CPU
     * - Await AVAILABLE_CORES semaphore
     * - iterate over cores, look for first completed core (thread::isJoinable?)
     * assign core with new constructor using the PCB
     * - loads onto that CPU
     * - Operates continuously
     * - unload_PCB increments the semaphore
     * decrements the semaphore
     *
     */


    if(this->mode==MULTI){

    }
    else{
        Debug::debug(Debug::DISPATCHER, " Job RAM Address " + std::to_string(to_load->job_ram_address));
        load_PCB(to_load);
        while (cpu->state.state == PCB::RUNNING) cpu->Operate();
        return unload_PCB();
    }

}



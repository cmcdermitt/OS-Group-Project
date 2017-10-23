//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"
#include "Log.h"
#include <mutex>
#include <thread>
#include "Dispatcher.h"

          static std::mutex jobs_protection;
   std::vector<int> *Dispatcher::completed_jobs = new std::vector<int>();

Semaphore::Semaphore(int s){
    this->val = s;
}
void Semaphore::wait(){

    while(val<=0);
    j.lock();
    val--;
    j.unlock();
}
void Semaphore::signal(){
    j.lock();
    val++;
    j.unlock();
}

Semaphore *Dispatcher::coreSemaphore  = new Semaphore(4);

 void Dispatcher::operateCPU(CPU *cpu, RAM *ram, Semaphore *sem) {
    while (cpu->state->state == PCB::RUNNING) cpu->Operate();
     cpu->store_pcb();
     coreSemaphore->signal();

}

Dispatcher::Dispatcher(CPU *c, RAM *r,int size=1) {
    ram = r;
    if(size==1){cpu = c; this->mode=SINGLE;}
    else{
        cpu = c;
        this->mode=MULTI;
        coreLength = size;

    }

}

 void Dispatcher::load_PCB(PCB *p, CPU *c) {

    p->wait_time->turn_off();
    p->wait_time->record_data();
    p->wait_time->record_log();
    p->comp_time->turn_on();
    p->state = PCB::PROCESS_STATUS::RUNNING;
    c->load_pcb(p);
}



PCB *Dispatcher::context_switch(PCB *to_load, CPU **cpu) {
    coreSemaphore->wait();
    for (int i = 0; i < coreLength; i++) {
        if (!(cpu[i]->get_has_been_used()) || cpu[i]->state->state == PCB::COMPLETED) {
            Debug::debug(Debug::DISPATCHER, "Using CPU " + std::to_string(i));
            cpu[i]->set_to_used();
            if (to_load->state == PCB::READY) {
                to_load->state = PCB::RUNNING;
                load_PCB(to_load, cpu[i]);
                std::thread thread(Dispatcher::operateCPU, cpu[i], ram, coreSemaphore);
                thread.detach();
                break;
            }
        }
    }
}



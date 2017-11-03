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
    j.lock();
    while(val<=0);
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

    while (cpu->state->state == PCB::RUNNING) cpu->Operate(); coreSemaphore->signal();
                                  add_completed_job(cpu->state->job_id);

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

PCB *Dispatcher::unload_PCB() {

    PCB *temp = cpu->store_pcb();
    temp->comp_time->turn_off();
    temp->comp_time->record_data();
    temp->comp_time->record_log();
    temp->state = PCB::PROCESS_STATUS::COMPLETED;
    Debug::debug(Debug::DISPATCHER, "Unloading");
    return temp;
}

PCB *Dispatcher::context_switch(PCB *to_load, CPU **cpu) {
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

    static int count = 0;

    if (this->mode == MULTI) {
        coreSemaphore->wait();
        for (int i = 0; i < coreLength; i++) {
//            if (!(cpu[count]->get_has_been_used()) || cpu[count]->state->state == PCB::COMPLETED) {
//                Debug::debug(Debug::DISPATCHER, "Using CPU " + std::to_string(count));
//                cpu[count]->set_to_used();
//                if (to_load->state == PCB::RUNNING) {
//                    cpu[count]->set_to_used();
//                    to_load->state = PCB::RUNNING;
//                    load_PCB(to_load, cpu[count]);
//                    std::thread thread(Dispatcher::operateCPU, cpu[count], ram, coreSemaphore);
//                    thread.join();
//                    count++;
//                    if(count == 4) count = 0;
//                    break;
//                }
//            }
            if (!(cpu[i]->get_has_been_used()) || cpu[i]->state->state == PCB::COMPLETED) {
                Debug::debug(Debug::DISPATCHER, "Using CPU " + std::to_string(i));
                cpu[i]->set_to_used();
                if (to_load->state == PCB::RUNNING) {
                    cpu[i]->set_to_used();
                    to_load->state = PCB::RUNNING;
                    load_PCB(to_load, cpu[i]);
                    std::thread thread(Dispatcher::operateCPU, cpu[i], ram, coreSemaphore);
                    thread.detach();
                    count++;
                    break;
                }
            } else {
                Debug::debug(Debug::DISPATCHER, " Job RAM Address " + std::to_string(to_load->job_ram_address));
                load_PCB(to_load, cpu[0]);
                while (cpu[0]->state->state == PCB::RUNNING) cpu[0]->Operate();
                return unload_PCB();r
            }
        }
    }
}

void Dispatcher::add_completed_job(int i) {
                  jobs_protection.lock();
    completed_jobs->push_back(i);
    jobs_protection.unlock();
}

void Dispatcher::remove_completed_job(int i) {
                             for(int i = 0; i < completed_jobs->size(); i++)
                                 if(i == completed_jobs->at(i))
                                     completed_jobs->erase(completed_jobs->begin() + i);
}



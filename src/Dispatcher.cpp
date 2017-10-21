//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"
#include "Log.h"

Dispatcher::Dispatcher(CPU *c, RAM *r) {
    cpu = c;
    ram = r;
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
    Debug::debug(Debug::DISPATCHER, " Job RAM Address " + std::to_string(to_load->job_ram_address));
    load_PCB(to_load);
    while (cpu->state.state == PCB::RUNNING) cpu->Operate();
    return unload_PCB();
}
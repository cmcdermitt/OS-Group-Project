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
    current->state = PCB::PROCESS_STATUS::RUNNING;
    cpu->loadPCB(p);
}

PCB* Dispatcher::unload_PCB() {
    PCB* temp = cpu->storePCB();
    temp->state = PCB::PROCESS_STATUS::COMPLETED;
    Debug::debug(Debug::DEBUG_DISPATCHER, "Unloading");
    return temp;
}

PCB* Dispatcher::context_switch(PCB *to_load) {
    Debug::debug(Debug::DEBUG_DISPATCHER, "BSJNADBKJHBF" + std::to_string(to_load->job_ram_address));
    load_PCB(to_load);
    while(cpu->state.state == PCB::RUNNING) cpu->Operate();
    return unload_PCB();
}
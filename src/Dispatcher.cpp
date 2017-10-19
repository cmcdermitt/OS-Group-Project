//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"

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
    return temp;
}

PCB* Dispatcher::context_switch(PCB *to_load) {
    load_PCB(to_load);
    while(cpu->state.state == PCB::RUNNING) cpu->Operate();
    return unload_PCB();
}
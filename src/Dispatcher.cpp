//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"

// Initalizes Dispatcher with the system cpu and ram
Dispatcher::Dispatcher(CPU *c, RAM *r) {
    cpu = c;
    ram = r;
}

// Loads PCB into current PCB being worked on
void Dispatcher::load_PCB(PCB *p) {
    current = p;
    current->state = PCB::PROCESS_STATUS::RUNNING; // Sets RUNNING status
    cpu->loadPCB(p);
}

// Takes PCB off and stores it in CPU
PCB* Dispatcher::unload_PCB() {
    PCB* temp = cpu->storePCB();
    temp->state = PCB::PROCESS_STATUS::COMPLETED; // Sets COMPLETED status
    return temp;
}

// Switches context of current PCB/CPU
PCB* Dispatcher::context_switch(PCB *to_load) {
    load_PCB(to_load);
    while(cpu->state.state == PCB::RUNNING) cpu->Operate();
    return unload_PCB();
}
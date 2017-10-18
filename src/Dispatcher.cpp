//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"

void Dispatcher::load_PCB(PCB *p, RAM *r) {
    ram = r;
    current = p;
    current->state = PCB::PROCESS_STATUS::RUNNING;
    //computer loads PCB and begins operations
}
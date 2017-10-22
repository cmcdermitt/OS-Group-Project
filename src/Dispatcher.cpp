//
// Created by Zach Auzenne on 10/18/17.
//

#include "Dispatcher.h"
#include "Log.h"
#include "Cache.h"

Dispatcher::Dispatcher(CPU **c, RAM *r, int size) {
    cpuList  = c;
    for(int i=0;i<size;i++){
        std::thread (CPU::runCPU,c[i]);
    }
    ram = r;
    coreLength = size;
    current = new PCB();
}

Cache *Dispatcher::buildCache(PCB *p, RAM *r) {
    Cache* c = new Cache();
    std::vector<std::string> data;

    data = ram->read(p->job_ram_address, p->total_size);
    c->write(p->job_ram_address, data);
    return c;
}

PCB *Dispatcher::context_switch(PCB *to_load) {
    Debug::debug(Debug::DISPATCHER, " Job RAM Address " + std::to_string(to_load->job_ram_address));
    Cache *cache = buildCache(to_load, ram);
    CPU *c = cpuList[awaitCPU()];
    c->load_pcb(to_load,cache);
    while (c->state.state == PCB::RUNNING) c->Operate();
    return c->store_pcb();
}

int Dispatcher::awaitCPU() {
      while(1)
      {
          for (int i = 0; i < coreLength; ++i) {
              if(cpuList[i]->isOpen())
                  return i;
          }
      }
}


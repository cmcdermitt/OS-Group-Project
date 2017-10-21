//
// Created by Eshin Griffith on 9/26/17.
//

#include <iostream>
#include "Driver.h"
#include "Dispatcher.h"

Driver::Driver() {
    disk = Disk();
    ram = new RAM();
    loader = Loader();
    cpu = new CPU(ram, production);
    pcbs = std::list<PCB *>();
    log = new Log("Driver");
    testLog = new Log("Test");
    disp = new Dispatcher(cpu, ram);
    lt_still_has_work = true;
    st_still_has_work = true;

}

void Driver::run() {
    log->turn_on();
    loader.init(disk, pcbs);

    Scheduler sched = Scheduler(pcbs, disk, *ram, disp);
    while (lt_still_has_work || st_still_has_work) {

        sched.lt_sched(&lt_still_has_work);

        sched.st_sched(&st_still_has_work);

    }
    //sched.lt_test();
    //  std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;
    log->turn_off();


    //  std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;


    delete log;
}

void Driver::test() {
    CPU::test();
//		testLog->turn_on();for(int i= 0; i < 2048; i++) std::cout << disk.read(i) << std::endl;
    testLog->turn_off();
    delete testLog;
}




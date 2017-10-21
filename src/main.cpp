#include <iostream>
#include <list>
#include "Loader.h"
#include "PCB.h"
#include "Log.h"
#include "Scheduler.h"
#include "Ram.h"
#include "CPU.h"
#include "Utility.h"

int main() { //main now does what Driver did before
    //declare variables
    Disk disk = Disk();
    RAM *ram = new RAM();
    Loader loader = Loader();
    CPU *cpu = new CPU(ram, production);
    std::list<PCB*>pcbs = std::list<PCB*>();
    Log *log = new Log("Driver");
    Dispatcher *disp = new Dispatcher(cpu, ram);
    bool lt_still_has_work = true;
    bool st_still_has_work = true;
    void driver_test();

    log->turnOn();

    loader.init(disk, pcbs);

    Scheduler sched = Scheduler(pcbs, disk, *ram, disp);
    while(lt_still_has_work || st_still_has_work) {

        sched.lt_sched(&lt_still_has_work);

        sched.st_sched(&st_still_has_work);
    }

    //driver_test();

    log->turnOff();
    delete log;

 }

void driver_test()
{
    Log* testLog = new Log("Test");
    CPU::test();
    //testLog->turnOn();for(int i= 0; i < 2048; i++) std::cout << disk.read(i) << std::endl;
    testLog->turnOff();
    delete testLog;
}

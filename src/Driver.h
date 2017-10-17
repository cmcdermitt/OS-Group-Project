//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DRIVER_H
#define OS_GROUP_PROJECT_DRIVER_H

//  The driver will have a loader, disk, ram, long term Scheduler, log, CPU and ram objects.
// The Driver will have a function called run(), that will execute the OS, and
// run all of its overarching commands.
// The run function will execute several lower functions as follows:
// load.load(): Reads the program file into the disk
// The next functions are run in a loop:
// scheduleNext(): Calls functions from long term Scheduler and short term Scheduler to load
// jobs onto the ready queue and the ram.
// cpu.execute(): The cpu is permitted to run until job completion or interrupt.
#include "Loader.h"
#include "Driver.h"
#include<list>
#include "PCB.h"
#include "Log.h"
#include "Scheduler.h"
#include "Ram.h"
#include "CPU.h"
class Driver {

public:
Driver();
void run();
void test();
std::list<PCB*> pcbs;
private:
   Loader loader;
   Disk disk;
    RAM *ram;
   Log *log; 
   Log *testLog; 
};


#endif //OS_GROUP_PROJECT_DRIVER_H

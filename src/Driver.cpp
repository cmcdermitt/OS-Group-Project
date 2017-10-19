//
// Created by Eshin Griffith on 9/26/17.
//

#include <iostream>
#include "Driver.h"
#include "Dispatcher.h"

//Sets up disk, ram, loader, cpu, pcb lists, log files, and dispatcher
    Driver::Driver(){
        disk = Disk();
        ram = new RAM();
        loader = Loader();
        cpu = new CPU(ram, production);
	    pcbs = std::list<PCB*>();
	    log = new Log("Driver");
	    testLog = new Log("Test");
        disp = new Dispatcher(cpu, ram);

    }
//Runs driver and schedulers
    void Driver::run() {
		log->turnOn(); 
        loader.init(disk, pcbs);

            Scheduler sched = Scheduler(pcbs, disk, *ram, disp); //Passes list of pcbs to scheduler
            sched.lt_sched(); //Calls long term scheduler
            sched.st_sched(); //Calls short term scheduler
            //sched.lt_test();
            //  std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;
            log->turnOff();

      //  std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;


		delete log; 

    }

    void Driver::test()
    {
        CPU::test();
//		testLog->turnOn();for(int i= 0; i < 2048; i++) std::cout << disk.read(i) << std::endl;
		testLog->turnOff(); 
		delete testLog;
    }




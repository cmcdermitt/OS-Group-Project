//
// Created by Eshin Griffith on 9/26/17.
//

#include <iostream>
#include "Driver.h"
#include "Disk.h"
#include "Loader.h"
#include "PCB.h"


#include <list>
#include <string>
#include "Log.h"

    Driver::Driver(){
         disk = Disk();
        ram = RAM();
       loader = Loader();
	   pcbs = std::list<PCB*>();
	   log = new Log("Driver"); 
	   testLog = new Log("Test");

    }

    void Driver::run() {
		log->turnOn(); 
        loader.init(disk, pcbs);

        Scheduler sched = Scheduler(pcbs, disk, ram);
        std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;
		log->turnOff(); 
		delete log; 

    }

    void Driver::test()
    {
		testLog->turnOn();
        for(int i= 0; i < 2048; i++)
            std::cout << disk.read(i) << std::endl;
		testLog->turnOff(); 
		delete testLog;
    }




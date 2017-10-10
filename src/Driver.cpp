//
// Created by Eshin Griffith on 9/26/17.
//

#include "Driver.h"
#include "Disk.h"
#include "Loader.h"
#include "PCB.h"
#include <list>


    Driver::Driver(){
         disk = new Disk();
       loader = new Loader();
	   pcbs = new std::list<PCB>();
    }

    void Driver::run() {
        loader->init(disk, pcbs);


    }

    void Driver::test()
    {
        for(int i= 0; i < 2048; i++)
            std::cout << disk->read(i) << std::endl;

    }




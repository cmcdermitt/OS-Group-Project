//
// Created by Eshin Griffith on 9/26/17.
//

#include "Driver.h"
#include "Disk.h"
#include "Loader.h"



    Driver::Driver(){
        Disk disk = Disk();
        Loader loader = Loader();
    }

    void Driver::run() {
        loader.init(&disk);


    }




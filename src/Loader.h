//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_LOADER_H
#define OS_GROUP_PROJECT_LOADER_H

#include "Disk.h"
#include "PCB.h"
#include "Log.h"

class Loader {
public:
    void init(Disk &disk_to_load, std::list<PCB *> &pcbs, std::vector<Log*> &logs); // Loads all of the data into the disk and creates a job list
    Loader();

private:
    Disk disk;
    Log *l;

};


#endif //OS_GROUP_PROJECT_LOADER_H

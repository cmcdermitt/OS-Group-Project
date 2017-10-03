//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_LOADER_H
#define OS_GROUP_PROJECT_LOADER_H

#include "Disk.h"

class Loader {
public:
    void init(Disk disk_to_load); // Loads all of the data into the disk and creates a job list
private:
    const std::string CODEFILENAME = "ProgramFile.txt"
    Disk disk;
    
}


#endif //OS_GROUP_PROJECT_LOADER_H

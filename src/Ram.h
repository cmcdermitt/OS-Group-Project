//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_RAM_H
#define OS_GROUP_PROJECT_RAM_H
#include <iostream>
#include <stdlib.h>
 #include <stdint.h>
 #include <mutex>
#include <vector>
#include "Log.h"

//The RAM will contain a 1024 location array containing a dedicated 8-character Hex word
//The read(int address) function is called by the Fetch class, which locates
//a literal address in the RAM array and returns the word at that location.


class RAM {


public:
    std::mutex mutex;
    std::string read(int address);
    void write(int address, std::string data);
    void write(int address, std::vector<std::string> s);
    const static int SIZE = 1024;
    Log *ram_log = new Log("Ram_Log");
    RAM();
    ~RAM();

private:
    std::string ram_data[SIZE];
    int ram_used;
    //not sure what else
};


#endif //OS_GROUP_PROJECT_RAM_H

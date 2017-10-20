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
//The RAM will contain a 1024 locations containing a dedicated 8-character Hex word
//The read(int address) function is called by the Fetch class, which locates
//a literal address in the RAM array and returns the word at that location.


class RAM {


public:
    std::mutex mutex;
    std::string read(int address);
    void write(int address, std::string data);
    void write(int address, std::vector<std::string> s);
    RAM();
    const static int SIZE = 1024;
    void testRam();

private:
     std::string ram_data[SIZE];
    //not sure what else
};


#endif //OS_GROUP_PROJECT_RAM_H

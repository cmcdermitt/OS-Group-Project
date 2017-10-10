//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_RAM_H
#define OS_GROUP_PROJECT_RAM_H
#include <iostream>
#include <stdlib.h>
 #include <stdint.h>

//The RAM will contain a 1024 locations containing a dedicated 8-character Hex word
//The read(int address) function is called by the Fetch class, which locates
//a literal address in the RAM array and returns the word at that location.


class RAM {
public:
    int read(int address);
    void write(int address, int data);
    RAM();

private:
     int ram_data[1024];
    //not sure what else
};


#endif //OS_GROUP_PROJECT_RAM_H

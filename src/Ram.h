//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_RAM_H
#define OS_GROUP_PROJECT_RAM_H
#include <iostream>
//The RAM will contain a 1024 locations containing a dedicated 8-character Hex word
//The read(int address) function is called by the Fetch class, which locates
//a literal address in the RAM array and returns the word at that location.


class RAM {
public:
    __int32 read(__int32 address);
    void write(__int32 address, __int32 data);

private:
     __int32 array[1024];
    //not sure what else
};


#endif //OS_GROUP_PROJECT_RAM_H

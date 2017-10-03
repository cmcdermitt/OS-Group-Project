//
// Created by Eshin Griffith on 9/26/17.
//

#include "Disk.h"
#include <iostream>
#include <stdlib.h>

__int32 Disk::read(__int32 address)
{
    if(address >= 2048 || address < 0)
        return -1;
    return diskData[address];
}

void Disk::write(__int32 address, __int32 data)
{
    if(address >= 2048 || address < 0)
        exit(EXIT_FAILURE);
    diskData[address] = data;

}

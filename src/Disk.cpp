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

Disk::Disk()
{

}

void static test()
{
Disk *disk = new Disk();
disk->write(234, 4538);
std::cout << "234: should be 3539:\t" << disk->read(234);
std::cout << "0: should be 0:\t" << disk->read(0);
disk->write(235, 12344);
disk->write(234, 2333);
std::cout << "234: should be 2333:\t" << disk->read(234);
std::cout << "235: should be 12344:\t" <<  disk->read(235);
std::cout << "236: should be 0:\t" << disk->read(236);

}

//
// Created by Eshin Griffith on 9/26/17.
//

#include "Disk.h"
#include <iostream>




void Disk::write(int address, int data)
{
    if(address >= 2048 || address < 0)
        exit(EXIT_FAILURE);
    diskData[address] = data;

}

int Disk::read(int address)
{
    if(address >= 2048 || address < 0)
        return -1;
    return diskData[address];
}
Disk::Disk()
{
for(int i = 0; i < SIZE; i++)
    diskData[i] = 0;
}

void  Disk::test()
{
Disk *disk = new Disk();
disk->write(234, 4538);
std::cout << "\n234: should be 4538:\t" << disk->read(234);
std::cout << "\n0: should be 0:\t" << disk->read(0);
disk->write(235, 12344);
disk->write(234, 2333);
std::cout << "\n234: should be 2333:\t" << disk->read(234);
std::cout << "\n235: should be 12344:\t" <<  disk->read(235);
std::cout << "\n236: should be 0:\t" << disk->read(236);

}

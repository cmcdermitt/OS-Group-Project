//
// Created by Eshin Griffith on 9/26/17.
//

#include "Disk.h"
#include <iostream>
#include <stdlib.h>
#include <string>

// Writes string data to the array address
void Disk::write(int address, std::string data) {
    if (address >= SIZE || address < 0)
        exit(EXIT_FAILURE);
    disk_data[address] = data;
}

// Reads string data from the array address
std::string Disk::read(int address) {
    return disk_data[address];
}

// Construct Disk and set size to global variable SIZE
Disk::Disk() {
    for (int i = 0; i < SIZE; i++)
        disk_data[i] = "";
}

// Assess the read and write methods of the Disk
void Disk::test() {
    Disk *disk = new Disk();
    disk->write(234, "2323");
    std::cout << "\n234: should be 4538:\t" << disk->read(234);
    std::cout << "\n0: should be 0:\t" << disk->read(0);
    disk->write(235, "23232");
    disk->write(234, "34434");
    std::cout << "\n234: should be 2333:\t" << disk->read(234);
    std::cout << "\n235: should be 12344:\t" << disk->read(235);
    std::cout << "\n236: should be 0:\t" << disk->read(236);
    for (int i = 0; i < 2048; i++)
        std::cout << disk_data[i] << std::endl;
}

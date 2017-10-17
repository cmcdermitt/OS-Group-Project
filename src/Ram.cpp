//
// Created by Eshin Griffith on 9/26/17.
//

#include "RAM.h"
#include <iostream>
#include <stdlib.h>
 #include <stdint.h>

    void RAM::write(int address, std::string data)
    {
        mutex.lock();
        if(address >= SIZE || address < 0)
            exit(EXIT_FAILURE);
        ram_data[address] = data;
        mutex.unlock();
    }

    std::string RAM::read(int address)
    {
        mutex.lock();
        return ram_data[address];
        mutex.unlock(); 
    }

    RAM::RAM()
    {
        mutex = std::mutex();
        for(int i = 0; i < SIZE; i++)
            ram_data[i] = "";
    }

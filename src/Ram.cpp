//
// Created by Eshin Griffith on 9/26/17.
//

#include "RAM.h"
#include <iostream>
#include <stdlib.h>
 #include <stdint.h>

    void RAM::write(int address, int data)
    {
        if(address >= 1024 || address < 0)
            exit(EXIT_FAILURE);
        ram_data[address] = data;

    }

    int RAM::read(int address)
    {
        if(address >= 1024 || address < 0)
            return -1;
        return ram_data[address];
    }

    RAM::RAM()
    {
        for(int i = 0; i < 1024; i++)
            ram_data[i] = 0;
    }

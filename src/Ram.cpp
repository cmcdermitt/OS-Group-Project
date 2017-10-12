//
// Created by Eshin Griffith on 9/26/17.
//

#include "RAM.h"
#include <iostream>
#include <stdlib.h>
 #include <stdint.h>

    void RAM::write(int address, std::string data)
    {
        if(address >= SIZE || address < 0)
            exit(EXIT_FAILURE);
        ram_data[address] = data;

    }

    std::string RAM::read(int address)
    {
        return ram_data[address];
    }

    RAM::RAM()
    {
        for(int i = 0; i < SIZE; i++)
            ram_data[i] = "";
    }

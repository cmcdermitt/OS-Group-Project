//
// Created by Eshin Griffith on 9/26/17.
//
#include <vector>
#include "Ram.h"

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
        std::string rd =  ram_data[address];
        mutex.unlock();
        return rd;
    }

    void RAM::write(int address, std::vector<std::string> data)
    {
        mutex.lock();
        for(int i = 0; i < data.size(); i++) {
        this->ram_data[i + address] =  data[i];
        }
        mutex.unlock();
    }

    RAM::RAM()
    {
        for(int i = 0; i < SIZE; i++)
            ram_data[i] = "";
    }

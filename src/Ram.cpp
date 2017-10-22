//
// Created by Eshin Griffith on 9/26/17.
//
#include <vector>
#include "Ram.h"


std::string RAM::read(int address) {
    mutex.lock();
    std::string rd = ram_data[address];
    mutex.unlock();
    return rd;
}

std::vector<std::string> RAM::read(int address, int size)
{
    std::vector<std::string> s = std::vector<std::string>();
    for(int i = address; i < address + size; i++)
    {
        mutex.lock();
        s.push_back(ram_data[address]);
        mutex.unlock();
    }
}


void RAM::write(int address, std::string data) {
    mutex.lock();
    if (data == "0")
        ram_used -= 1;
    else
        ram_used += 1;
    if (address >= SIZE || address < 0)
        exit(EXIT_FAILURE);
    ram_data[address] = data;
    mutex.unlock();
}

void RAM::write(int address, std::vector<std::string> data) {
    mutex.lock();
    if (data[0] == "0")
        ram_used -= data.size();
    else
        ram_used += data.size();
    for (int i = 0; i < data.size(); i++) {
        this->ram_data[i + address] = data[i];
    }
    mutex.unlock();
}

RAM::RAM() {
    for (int i = 0; i < SIZE; i++)
        ram_data[i] = "0";
    ram_used = 0;

}

RAM::~RAM() {
    ram_log->record_data();

}

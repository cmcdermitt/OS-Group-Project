//
// Created by Eshin Griffith on 9/26/17.
//
#include <vector>
#include "Ram.h"


std::string RAM::read(int address) {
    mutex.lock();
    std::string rd = ram_data[address];
    ram_log->add_point("r",ram_used);
    mutex.unlock();
    return rd;
}

void RAM::write(int address, std::string data) {
    mutex.lock();
  
    ram_log->add_point("Ram", ram_used);
    if (address >= SIZE || address < 0)
        exit(EXIT_FAILURE);
    ram_data[address] = data;
    ram_log->add_point("r",ram_used);
    mutex.unlock();
}

void RAM::write(int address, std::vector<std::string> data) {
    mutex.lock();
    if (data[0] == "0")
        ram_used -= data.size();
    else
        ram_used += data.size();
    ram_log->add_point("Ram", ram_used);
    for (int i = 0; i < data.size(); i++) {
        this->ram_data[i + address] = data[i];
    }
    ram_log->add_point("r",ram_used);
    mutex.unlock();
}

RAM::RAM() {
    for (int i = 0; i < SIZE; i++)
        ram_data[i] = "0";
    ram_used = 0;
    ram_log = new Log("Ram");
    ram_log->add_graph("r");

}

RAM::~RAM() {
    ram_log->record_data();
    ram_log->record_log();

}

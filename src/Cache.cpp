//
// Created by charlie on 10/22/17.
//

#include "Cache.h"

std::string Cache::read(int address) {
    std::string rd = cache_data[address];
    return rd;
}

void Cache::write(int address, std::string data) {
    if (address >= SIZE || address < 0)
        exit(EXIT_FAILURE);
    cache_data[address] = data;
}

void Cache::write(int address, std::vector<std::string> data) {
    for (int i = 0; i < data.size(); i++) {
        this->cache_data[i + address] = data[i];
    }
}

Cache::Cache() {
    for (int i = 0; i < SIZE; i++)
        cache_data[i] = "0";

}

Cache::~Cache() {
    cache_log->record_data();

}
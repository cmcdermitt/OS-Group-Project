//
// Created by charlie on 10/22/17.
//

#include "Cache.h"

std::string Cache::read(int address) {
    std::string rd = cache_data[address];
    return rd;
}
std::vector<std::string> Cache::read(int address, int length){
   std::vector<std::string> strList = std::vector<std::string>();
    for (int i = 0; i < length; ++i) {
        strList.push_back(cache_data[address+i]);
    }
    return strList;
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
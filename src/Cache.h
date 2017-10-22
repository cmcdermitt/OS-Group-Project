//
// Created by charlie on 10/22/17.
//

#ifndef OS_GROUP_PROJECT_CACHE_H
#define OS_GROUP_PROJECT_CACHE_H

#include <string>
#include <vector>
#include "Log.h"


class Cache {


public:
    std::string read(int address);
    void write(int address, std::string data);
    void write(int address, std::vector<std::string> s);
    const static int SIZE = 128;
    Log *cache_log = new Log("Cache_Log");
    Cache();
    ~Cache();


private:
    std::string cache_data[SIZE];
};


#endif //OS_GROUP_PROJECT_CACHE_H

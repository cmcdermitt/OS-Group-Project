//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DISK_H
#define OS_GROUP_PROJECT_DISK_H

//
// Comprised of an array limited to 2048 words (or locations)
// Each location will hold a hex word "0x000000"
//

#include <iostream>
#include <vector>


class Disk {

public:
    const static int SIZE = 2048;

    std::string read(int address); // Reads string data from an address
    void write(int address, std::string data); // Writes string data to an address
    void write(int address, std::vector<std::string> s);//writes vector of strings to addresses
    Disk(); // Constructor

    void test(); // Tests the read and write methods of the Disk

private:
    std::string diskData[SIZE];

};

#endif //OS_GROUP_PROJECT_DISK_H

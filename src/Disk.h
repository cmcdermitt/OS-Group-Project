//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DISK_H
#define OS_GROUP_PROJECT_DISK_H

//Comprised of an array limited to 2048 words (or locations)
//Each location will hold a hex word "0x000000"
#include <iostream>

const static int SIZE = 2048;

class Disk {

  private:

      std::string diskData[SIZE];
      //not sure what else

  public:

    std::string read(int address); // Returns data from location
    void write(int address, std::string data); // Writes data to location
    Disk(); // Constructor
    // Uses the functions in Disk to see if they work; do not use in
    // main project
 void test();

};


#endif //OS_GROUP_PROJECT_DISK_H

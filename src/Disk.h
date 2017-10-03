//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DISK_H
#define OS_GROUP_PROJECT_DISK_H

//Comprised of an array limited to 2048 words (or locations)
//Each location will hold a hex word "0x000000"
#include <iostream>
#include <stdlib.h>
const int SIZE = 2048;

class Disk {

  private:

      int diskData[SIZE];
      //not sure what else

  public:

    int read(int address); // Returns data from location
    void write(int address, int data); // Writes data to location
    Disk(); // Constructor
    // Uses the functions in Disk to see if they work; do not use in
    // main project


};


#endif //OS_GROUP_PROJECT_DISK_H

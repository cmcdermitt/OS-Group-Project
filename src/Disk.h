//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DISK_H
#define OS_GROUP_PROJECT_DISK_H

//Comprised of an array limited to 2048 words (or locations)
//Each location will hold a hex word "0x000000"

class Disk {
    __int32 read(__int32 address);
    void write(__int32 address, __int32 data);

    private:
    const int SIZE = 2048;
    __int32[SIZE] array;
      
     
};


#endif //OS_GROUP_PROJECT_DISK_H

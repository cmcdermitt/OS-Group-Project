//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DISK_H
#define OS_GROUP_PROJECT_DISK_H

//Comprised of an array limited to 2048 words (or locations)
//Each location will hold a hex word "0x000000"

class Disk {
    /* need address type?
      __int32 read(address);
      void write(address, __int32 data);
      */

  private:
      __int32[2048] array;
      //not sure what else
      
     
};


#endif //OS_GROUP_PROJECT_DISK_H

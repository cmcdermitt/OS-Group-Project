//
// Created by Eshin Griffith on 9/26/17.
//

#ifndef OS_GROUP_PROJECT_DISK_H
#define OS_GROUP_PROJECT_DISK_H

//Comprised of an array limited to 2048 words (or locations)
//Each location will hold a hex word "0x000000"

class Disk {
<<<<<<< HEAD
    /* need address type?
      __int32 read(address);
      void write(address, __int32 data);


  private:
      __int32[2048] array;
      //not sure what else


=======
    __int32 read(__int32 address);
    void write(__int32 address, __int32 data);

    private:
    const int SIZE = 2048;
    __int32[SIZE] array;
      
     
>>>>>>> 40ae89f903f0a80cd776c9d48d43e3bd69f08ef1
};


#endif //OS_GROUP_PROJECT_DISK_H

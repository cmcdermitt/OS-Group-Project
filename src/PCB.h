#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED

#include<list>
#include "Log.h"
//Created by Charlie McDermitt on 10/3/2017

//PCB struct; may replace the class later


struct PCB {
    //Job
    int job_id;
    int job_size;
    int job_pri;
    int in_buf_size;
    int out_buf_size;
    int temp_buf_size;
    int total_size;
    enum PROCESS_STATUS {RUNNING, READY, BLOCKED, NEW, COMPLETED};
    enum PROCESS_STATUS state;
    int job_disk_address;
    int job_ram_address;
    int prgm_counter;
    int registers[16];
    Log *wait_time;
    Log *comp_time;

    //Data
    int data_disk_address;

};

void print_pcbs(std::list<PCB *> p);

#endif // PCB_H_INCLUDED

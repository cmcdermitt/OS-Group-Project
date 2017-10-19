#include <iostream>
#include "PCB.h"

void printPCBs(std::list<PCB*> p)
{
//    std::list<PCB*>::iterator eshen = p->begin();
//    while(eshen != p->end())
//    {
//        p++;
//    }

    for(PCB *pcb : p)
    {
        std::cout << "ID\t" << pcb->job_id << std::endl;
        std::cout << "Job Size:\t" << pcb->job_size << std::endl;
        std::cout << "JobPri:\t" << pcb->job_pri << std::endl;
        std::cout << "InSize:\t" << pcb->in_buf_size << std::endl;
        std::cout << "OutSize:\t" << pcb->out_buf_size << std::endl;
        std::cout << "TempSize:\t" << pcb->temp_buf_size << std::endl;
        std::cout << "Total Size:\t" << pcb->total_size << std::endl;
        std::string s;
        switch(pcb->state)
        {
            case 0: {
                s = "RUNNING";
                break;
            }
            case 1: {
                s = "READY";
                break;
            }
            case 2: {
                s = "BLOCKED";
                break;
            }
            case 3: {
                s = "NEW";
                break;
            }
            case 4: {
                s = "COMPLETED";
                break;
            }
        }
        std::cout << "State:\t" << s << std::endl;
        std::cout << std::endl;
    }

    if (p.empty())
        std::cout << ("No PCBs to print.") << std::endl;

}


//p->job_id = data[0];
//p->job_size = data[1];
//p->job_pri = data[2];
//p->in_buf_size = data[3];
//p->out_buf_size = data[4];
//p->temp_buf_size = data[5];
//p->total_size = p->job_size + p->in_buf_size + p->out_buf_size + p->temp_buf_size;
//p->state = PCB::PROCESS_STATUS::NEW;
//
// Created by Zachary Auzenne on 10/03/17.
//
//
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//class PCB {
//   private:
//  //Job
//    int jobId;
//    int jobSize;
//    int jobPri;
//    enum PROCESS_STATUS {RUNNING, READY, BLOCKED, NEW, COMPLETED};
//    enum PROCESS_STATUS state;
//    int jobAddress;
//    int prgmCounter;
//    bool hasRan;
//    bool inMemory;
//    int registers [16];
//
//    //Data
//    int dataDiskAddress;
//    int dataMemoryAddress;
//  public:
//
//  PCB ();
//
//  void setId (int id);
//  int getId ();
//
//  void setSize (int size);
//  int getSize ();
//
//  void setPri (int priority);
//  int getPri();
//
//  void setStatus (PROCESS_STATUS proc);
//  PROCESS_STATUS getStatus();
//
//  void setJobAddress (int address);
//  int getJobAddress ();
//
//  void setPrgmCounter (int counter);
//  int getPrgmCounter ();
//
//  void setRan (bool var);
//  bool getRan ();
//
//  void setMemory (bool var);
//  bool getMemory ();
//
//  void setReg (int reg[]);
//  int[] getReg ();
//
//  void setDataDisk (int address);
//  int getDataDisk ();
//
//  void setDataMem (int address);
//  int getDataMem ();
//
//
//
////Implementation
//
//PCB::PCB () {
//  jobId = 0;
//  jobSize = 0;
//  jobPri = 0;
//  state = NEW;
//  jobAddress = 0;
//  prgmCounter = 0;
//  hasRan = false;
//  inMemory = false;
//  registers.fill(0);
//
//  dataDiskAddress = 0;
//  dataMemoryAddress = 0;
// }
//
//void setId (int id) {
//  jobId = id;
//}
//
//int getId () {
//  return jobId;
//}
//
//void setSize (int size) {
//  jobSize = size;
//}
//
//int getSize () {
//  return jobSize;
//}
//
//void setPri (int priority) {
//  jobPri = priority;
//}
//
//int getPri() {
//  return jobPri;
//}
//
//void setStatus (PROCESS_STATUS proc) {
//  state = proc;
//}
//
//PROCESS_STATUS getStatus()
//  return state;
//}
//
//void setJobAddress (int address) {
//  jobAddress = address;
//}
//
//int getJobAddress () {
//  return jobAddress;
//}
//
//void setPrgmCounter (int counter) {
//  prgmCounter = counter;
//}
//
//int getPrgmCounter () {
//  return prgmCounter;
//}
//
//void setRan (boolean var) {
//  hasRan = var;
//}
//
//boolean getRan () {
//  return hasRan;
//}
//
//void setMemory (boolean var) {
//  inMemory = var;
//}
//
//boolean getMemory () {
//  return inMemory;
//}
//
//void setReg (int reg[]) {
//  registers = reg;
//}
//
//int[] getReg () {
//  return registers;
//}
//
//void setDataDisk (int address) {
//  dataDiskAddress = address;
//}
//
//int getDataDisk () {
//  return dataDiskAddress;
//}
//
//void setDataMem (int address) {
//  dataMemoryAddress = address;
//}
//
//int getDataMem () {
//  return dataMemoryAddress;
//}
//
//
//};

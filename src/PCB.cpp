#include <iostream>
#include "PCB.h"
void printPCBs(std::list<PCB> *p)
{
    std::list::iterator eshen = p.begin();
    while(eshen != p.end())
    {


    }
}



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

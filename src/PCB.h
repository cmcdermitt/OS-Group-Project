#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED
#include<list>
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
	enum PROCESS_STATUS { RUNNING, READY, BLOCKED, NEW, COMPLETED };
	enum PROCESS_STATUS state;
	int job_address;
	int prgm_counter;
	bool has_ran;
	bool in_memory;
	int registers[16];

	//Data
	int data_disk_address;
	int data_memory_address;

};
#endif // PCB_H_INCLUDED

//class PCB {
//  public:
//
//  PCB ();
//
//  void set_id (int id);
//  int get_id ();
//
//  void set_size (int size);
//  int get_size ();
//
//  void set_pri (int priority);
//  int get_pri();
//
//  void set_in_buf_size(int size);
//  int get_in_buf_size() {return in_buf_size};
//
//    void set_out_buf_size(int size);
//    int get_out_buf_size() {return out_buf_size};
//
//
//    void set_temp_buf_size(int size);
//    int get_temp_buf_size {return temp_buf_size};
//
//
//  void set_status (PROCESS_STATUS proc);
//  PROCESS_STATUS get_status();
//
//  void set_job_address (int address);
//  int get_job_address ();
//
//  void set_prgm_counter (int counter);
//  int get_prgm_counter ();
//
//  void set_ran (bool var);
//  bool get_ran ();
//
//  void set_memory (bool var);
//  bool get_memory ();
//
//  void set_reg (int reg[]);
//  int[] get_reg ();
//
//  void set_data_disk (int address);
//  int get_data_disk ();
//
//  void set_data_mem (int address);
//  int get_data_mem ();
//
//  private:
//  //Job
//    int job_id;
//    int job_size;
//    int job_pri;
//    int in_buf_size;
//    int out_buf_size;
//    int temp_buf_size;
//    enum PROCESS_STATUS {RUNNING, READY, BLOCKED, NEW, COMPLETED};
//    enum PROCESS_STATUS state;
//    int job_address;
//    int prgm_counter;
//    bool has_ran;
//    bool in_memory;
//    int registers [16];
//
//    //Data
//    int data_disk_address;
//    int data_memory_address;
//
////Implementation
//
//
//#endif // PCB_H_INCLUDED
//
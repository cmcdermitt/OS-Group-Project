#include "Loader.h"
#include<list>
#include "PCB.h"
#include "Log.h"
#include "Scheduler.h"
#include "Ram.h"
#include "CPU.h"

int main() {
    std::vector<Log*> logs = std::vector<Log*>();
    Debug::translate_program_file_to_binary();
    Disk disk = Disk();
    RAM *ram = new RAM();
    Loader loader = Loader();
    CPU *cpu = new CPU(ram, production);
    std::list<PCB*> pcbs = std::list<PCB*>();
    Log *log = new Log("Driver");
    Log *test_log = new Log("Test");
    Dispatcher *disp = new Dispatcher(cpu, ram);
    bool lt_still_has_work = true;
    bool st_still_has_work = true;

    log->turn_on();
    loader.init(disk, pcbs, logs);

    Scheduler sched = Scheduler(pcbs, disk, *ram, disp);
    while (lt_still_has_work || st_still_has_work) {

        sched.lt_sched(&lt_still_has_work);

        sched.st_sched(&st_still_has_work);


    }
    //sched.lt_test();
    //  std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;
    ;

    log->turn_off();


    //  std::cout << sched.lt_get_next_pcb(pcbs)->job_id << std::endl;


    delete log;
    delete ram;
    //driver_test(test_log)
     Log::total_average_wait_time(logs);
    Log::logEverything();
}

void driver_test(Log* test_log) {
    CPU::test();
//	test_log->turn_on();for(int i= 0; i < 2048; i++) std::cout << disk.read(i) << std::endl;
    test_log->turn_off();
    delete test_log;
}


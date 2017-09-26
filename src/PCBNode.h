typedef struct PCB {
cpuid: // information the assigned CPU (for multiprocessor system)
program-counter // the job’s pc holds the address of the instruction to fetch
struct state: // record of environment that is saved on interrupt
              // including the pc, registers, permissions, buffers, caches, active
              // pages/blocks
code-size; // extracted from the //JOB control line
struct registers: // accumulators, index, general
struct sched: // burst-time, priority, queue-type, time-slice, remain-time
struct accounts: // cpu-time, time-limit, time-delays, start/end times, io-times
struct memories: // page-table-base, pages, page-size
                 // base-registers – logical/physical map, limit-reg
struct progeny: // child-procid, child-code-pointers
parent: ptr; // pointer to parent (if this process is spawned, else ‘null’)
struct resources: // file-pointers, io-devices – unitclass, unit#, open-file-tables
status; // {running, ready, blocked, new}
status_info: // pointer to ‘ready-list of active processes’ or
             // ‘resource-list on blocked processes’
priority: integer; // of the process, extracted from the //JOB control line
}

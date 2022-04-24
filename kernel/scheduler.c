//
// Created by veljk on 12/15/2021.
//
#include "scheduler.h"
Scheduler SCHEDULERS[MAX_NUMBER_OF_SCHEDULERS];
//CREATE SCHEDULER FOR CPU; CHANGE ALGORITHM FOR CPU
void create_scheduler(int ID) {
    //SET DEFAULT SCHEDULER ARLOGRITHM AND INIT SCHEDULER
    Scheduler *scheduler = &SCHEDULERS[ID];
    scheduler->ID = ID;
    create_heap(&scheduler->processes_cpu);

    scheduler->get = get_CFS;
    scheduler->put = put_CFS;
    scheduler->processes_cpu.cmp = cfs_cmp;
    scheduler->algorithm = CFS;
}
//CHANGES ALGORITHM WHICH IS USED IN SCHEDULING
void
change_algorithm(int ID, ALGORITHM algorithm) {
    Scheduler *scheduler = &SCHEDULERS[ID];
    if (algorithm == scheduler->algorithm) return;
    scheduler->algorithm = algorithm;
    switch (algorithm) {
        case SJF:
            scheduler->get = get_SJF;
            scheduler->put = put_SJF;
            scheduler->processes_cpu.cmp = sjf_cmp;
            break;
        case CFS:
            scheduler->get = get_CFS;
            scheduler->put = put_CFS;
            scheduler->processes_cpu.cmp = cfs_cmp;
            break;
    }
    unsigned char next = 0;
    void *dataset[MAX_NODES_PER_HEAP];
    while (!is_empty(scheduler)) {
        dataset[next++] = scheduler->get(scheduler);
    }
    for (int i = 0; i < next; i++) {
        scheduler->put(scheduler, dataset[i]);
    }
}
//IS EMPTY
bool
is_empty(Scheduler *scheduler) {
    if (scheduler->processes_cpu.size == 0) {
        return true;
    }
    return false;
}
//SYSTEM CALL FOR SETTING ALPHA PARAMETER
void
set_alpha(unsigned char alpha, unsigned char ID) {
    SCHEDULERS[ID].alpha = alpha;
}
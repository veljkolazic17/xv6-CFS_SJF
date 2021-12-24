//
// Created by veljk on 12/15/2021.
//
#ifndef UNTITLED_SCHEDULER_H
#define UNTITLED_SCHEDULER_H
#include "pheap.h"
#define  MAX_NUMBER_OF_SCHEDULERS 64
//COMPARE FUNCTIONS UESED
bool sjf_cmp(NODE *, NODE *);
bool cfs_cmp(NODE *, NODE *);
//ENUMERATION USED TO SELECT TYPE OF ALGORITHM
enum ALGORITHM{SJF,CFS};
typedef enum ALGORITHM ALGORITHM;
//ENUMERATION USED FOR SJF
enum TYPE{PREEMT};
//DEFINITION OF SCHEDULER
typedef struct Scheduler Scheduler;
struct Scheduler{
    void* (*get)(struct Scheduler* scheduler);
    void (*put)(struct Scheduler* scheduler,void* data);
    HEAP processes_cpu;
    ALGORITHM algorithm;
    int ID;
    unsigned char alpha;
};
//SCHEDULER ARRAY FOR EVERY PROCESSOR
extern Scheduler SCHEDULERS[MAX_NUMBER_OF_SCHEDULERS];
//CREATE SCHEDULER FOR CPU; CHANGE ALGORITHM FOR CPU
void create_scheduler(int ID);
void change_algorithm(int ID, ALGORITHM algorithm);
//IS EMPTY
bool is_empty(Scheduler* scheduler);
//ALGORITHMS
void* get_SJF(Scheduler* scheduler);
void* get_CFS(Scheduler* scheduler);
void put_SJF(Scheduler* scheduler,void* data);
void put_CFS(Scheduler* scheduler,void* data);
//CHANGE ALPHA
void set_alpha(unsigned char alpha,unsigned char ID);
#endif //UNTITLED_SCHEDULER_H

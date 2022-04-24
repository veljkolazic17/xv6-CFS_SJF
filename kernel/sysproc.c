#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if(argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//CHANGED
// changes scheduling algorithm basedon system call arguments
// arguments: "algorithm" [type] [alpha]

struct spinlock algoc_lock;

uint64
sys_algoc(void){
    char algorithm[14]; // 1 -> SJF; 0 -> CFS
    int type; // 0 -> Preemptive; 1 -> Nonpreemptive;
    int alpha;
    if(argstr(0,algorithm,14)<0){
        return -1;
    }

    if(algorithm[0] == 'C' && algorithm[1] == 'F' && algorithm[2] == 'S'){
        intr_off();
        for(int i = 0;i<NCPU;i++){
            change_algorithm(i,CFS);
        }
    }
    else if(algorithm[0] == 'S' && algorithm[1] == 'J' && algorithm[2] == 'F'){
        if(argint(1,&type) < 0){
            return -1;
        }
        if(argint(2,&alpha) < 0){
            return -1;
        }
        intr_off();
        for(int i = 0;i<NCPU;i++){
            change_algorithm(i,SJF);
            SCHEDULERS[i].alpha = alpha;
        }
        switch (type) {
            case 1:
                SCHEDULING_TYPE = NONPREEMPTIVE;
                printf("Type: NONPREEMPTIVE\n");
                break;
            case 0:
                SCHEDULING_TYPE = PREEMPTIVE;
                printf("Type: PREEMPTIVE\n");
                break;
        }

    }
    else{
        return -2;
    }
    intr_on();
    printf("Algorithm changed to %s!\n",algorithm);
    return 0;
}
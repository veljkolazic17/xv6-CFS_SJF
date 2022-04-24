# XV6 Scheduling Algorithms
Changed default *Round Robin* algorithm and added:
- CFS
- SJF (preemptive, nonpreemptive)

To change scheduling algorithm, there is a **algoc** system call. First argument of a call is string determining which algorithm is being used, second argument is for SJF.\
Second Argument:
- 0 = Preemptive
- 1 = Nonpreemptive
## Scheduling algorithms priority queue
Both algorithms use **pairing heap** for priority queue implementation. *(Implementation can be found in **kernel\pheap.c**)*
## Scheduling algorithms implementation
### CFS
#### .GET
```c
void *
get_CFS(Scheduler *scheduler) {
    if (is_empty(scheduler))return 0;
    struct proc *p = (struct proc *) pop(&scheduler->processes_cpu);
    uint maximum_execution_time;
    if(scheduler->processes_cpu.size) {
        maximum_execution_time = (ticks - p->blocked_tick) / scheduler->processes_cpu.size +1;
    }else {
        maximum_execution_time = (ticks - p->blocked_tick)+1;
    }
    p->timeslice = maximum_execution_time;
    return p;
}
```
#### .PUT
```c
void
put_CFS(Scheduler *scheduler, void *data) {
    struct proc *p = ((struct proc *) data);
    p->blocked_tick = ticks;
    insert(&scheduler->processes_cpu, data);
}
```
### SJF
#### .GET
```c
void *
get_SJF(Scheduler *scheduler) {
    if (is_empty(scheduler)) return 0;
    struct proc *p = (struct proc *) pop(&scheduler->processes_cpu);
    if(SCHEDULING_TYPE == PREEMPTIVE) {
        p->timeslice = p->default_timeslice;
    }else{
        p->timeslice = 0;
    }
    return p;
}
```
#### .PUT
```c
void
put_SJF(Scheduler *scheduler, void *data) {
    unsigned long alpha = scheduler->alpha;
    struct proc *p = ((struct proc *) data);
    if (p->blocked_by_IO){
        p->tau_n = (p->t_n * alpha + p->tau_n * (100 - alpha)) / 100;
        p->blocked_by_IO = false;
        p->t_n = 0;
    }
    insert(&scheduler->processes_cpu, data);
}
```
# Changes
> Changed parts of code are marked as **CHANGED**!
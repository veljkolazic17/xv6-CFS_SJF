//
// Created by os on 12/24/21.
//
#include "../kernel/types.h"
#include "user.h"
#include "../kernel/stat.h"

void
main(){
    uint t = uptime();
    for(int f = 0;f<50;f++) {
        if (fork() == 0) {
            for (int k = 0; k < 10; k++) {
//                printf("Fork%d -> %d\n",f, k + 1);
                for (int i = 0; i < 100; i++) {
                    for (int j = 0; j < 300; j++);
                }
            }
            exit(0);
        }
    }
    for(int k = 0;k<10;k++){
//        printf("Tekst%d\n",k+1);
        for(int i = 0;i<10000;i++) {
            for (int j = 0; j < 6000; j++);
        }
    }
    t = uptime()-t;
    printf("TIME:%d\n",t);
    exit(0);
}

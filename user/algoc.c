//
// Created by os on 1/2/22.
//
#include "../kernel/types.h"
#include "user.h"
#include "../kernel/stat.h"

void
main(int argc,char* argv[]){
    if(argc == 2){
        algoc(argv[1],-1,-1);
    }
    else if(argc == 4){
        algoc(argv[1],atoi(argv[2]),atoi(argv[3]));
    }else{
        exit(1);
    }
    exit(0);
}

#include <stdio.h>
#include "rkboot_control.h"
#include <string.h>
int main(int argc, char *argv[]){
    //1. bootsucceed
    //2. bootactivity
    if(argc != 2){
        printf("Error: bootcontrol parameter error.\n");
        struct rk_ab info;
        readMisc(&info);
        display(info);
        return -1;
    }

    if(strcmp(argv[1], "bootsucceed") == 0){
        printf("set now slot to succeed.\n");
        return setSlotSucceed();
    }else if(strcmp(argv[1], "bootactivity") == 0){
        printf("set other slot to activity.\n");
        return setSlotActivity();
    }

    return 0;
}

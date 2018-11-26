/*************************************************************************
	> File Name: bootcontrol.cpp
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Tue 04 Dec 2018 03:43:16 PM CST
 ************************************************************************/

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "partition.h"
#include "bootcontrol.h"

using namespace std;


int setSlotToActive(){
    int currentSlot = getNowSlot();
    char slotWhere[3];
    if(currentSlot == 0){
        strcpy(slotWhere, "1");
    }else if(currentSlot == 1){
        strcpy(slotWhere, "0");
    }else{
        strcpy(slotWhere, "2");
    }

    pid_t pid;
    pid = fork();
    int status;

    char *const control_argv[] = {"bootcontrol", "bootactive", slotWhere, 0};
    
    if(pid == 0){
        execv(binPath, control_argv);
    }else if(pid > 0){
        waitpid(pid, &status, 0);
    }else{
        
    }
}

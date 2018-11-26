/*************************************************************************
	> File Name: main.cpp
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Thu 01 Nov 2018 10:29:22 AM CST
 ************************************************************************/

#include <iostream>
#include "rkimage.h"
#include "partition.h"
#include "log.h"
#include "data.h"
#include "tomcat.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

using namespace std;

void getDataFromFile(char *filename){
    /* Try to open the image.
    */
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        LOGE("Can't open %s\n", filename);
        return ;
    }
    struct ImageData data;
    struct ImageData *pData = &data;
    pData->data = (char*)malloc(READ_SIZE);
    pData->offset = 0;
    while(pData->size = read(fd, pData->data, READ_SIZE)){
        writeDataToPartition(pData);
        pData->offset += pData->size;
        if(pData->size != READ_SIZE){
            break;
        }
    }
    free(pData->data);
}

void getDataFromInternel(){
    char url[256] = "http://172.16.21.75:8080/update.img";
    getDataFromUrl(url);
}

#include "kugou.h"

void handle_upgrade_callback(void *user_data, RK_Upgrade_Status_t status){

}
int main(int argc, char *argv[]){
    char url[256] = "http://172.16.21.75:8080/update.img";
    RK_ota_set_url(url);
    RK_ota_start(handle_upgrade_callback);
    RK_ota_get_progress();

    return 0;
}

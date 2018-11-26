/*************************************************************************
	> File Name: rkimage.cpp
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Tue 30 Oct 2018 09:56:15 AM CST
 ************************************************************************/
#include <stdio.h>
#include "rkimage.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "log.h"
#include <errno.h>
#include "data.h"
#include "partition.h"

#define DEBUG_READ_IMAGE 0

void display_RKIMAGE_ITEM(RKIMAGE_ITEM *item){
    //char name[PART_NAME];
    //char file[RELATIVE_PATH];
    //unsigned int offset;
    //unsigned int flash_offset;
    //unsigned int usespace;
    //unsigned int size;

    LOGD("name = %s", item->name);
    LOGD("file = %s", item->file);
    LOGD("offset = %d", item->offset);
    LOGD("flash_offset = %d", item->flash_offset);
    LOGD("usespace = %d", item->usespace);
    LOGD("size = %d", item->size);
}

void display_RKIMAGE_HDR(RKIMAGE_HDR* hdr){
    //unsigned int tag;
    //unsigned int size;
    //char machine_model[MAX_MACHINE_MODEL];
    //char manufacturer[MAX_MANUFACTURER];
    //unsigned int version;
    //int item_count;
    //RKIMAGE_ITEM item[MAX_PACKAGE_FILES];

    LOGD("tag = %d", hdr->tag);
    LOGD("size = %d", hdr->size);
    LOGD("machine_model = %s", hdr->machine_model);
    LOGD("manufacturer = %s", hdr->manufacturer);
    LOGD("version = %d", hdr->version);
    for(int i = 0; i < hdr->item_count; i++){
        LOGI("================================================");
        display_RKIMAGE_ITEM(&(hdr->item[i]));
    }
}

void adjustFileOffset(RKIMAGE_HDR* hdr, int offset)
{
    for(int i = 0; i< hdr->item_count; i++)
        hdr->item[i].offset += offset;
    return;
}

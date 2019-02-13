/*************************************************************************
	> File Name: rkboot_control.h
	> Author: jkand.huang
	> Mail: jkand.huang@rock-chips.com
	> Created Time: Wed 09 Jan 2019 02:57:43 PM CST
 ************************************************************************/

#ifndef _RKBOOT_CONTROL_H
#define _RKBOOT_CONTROL_H

#define AB_MAGIC     "\0AB0"
#define AB_MAGIC_LEN 4
#define AB_SLOT_NUM  2
#define RETRY_MAX    7
#define AB_VERSION   0

#define MISC_OFFSET 2048
#define MISC_OFFSET_CMDLINE 4096
#define MISC_PARTITION_NMAE "/dev/block/by-name/misc"

#define CMDLINE_LENGTH 2048

#define CMD_WIPE_USERDATA "cmd_wipe_userdata"

struct rk_ab {
    unsigned char magic[AB_MAGIC_LEN];
    unsigned int version;
    int last_boot;
    int use_a;
    int use_b;
    int current_boot;
    unsigned char reserved[12];
    unsigned int crc32;
};

int setSlotActivity();
int setSlotSucceed();
int readMisc(struct rk_ab* info);
void display(struct rk_ab info);

bool wipe_userdata(bool auto_reboot);
#endif

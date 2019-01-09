#include <iostream>
#include "update.h"
void handle_upgrade_callback(void *user_data, RK_Upgrade_Status_t status){

}

void handle_upgrade_callback_reboot(void *user_data, RK_Upgrade_Status_t status){
    if(status == RK_UPGRADE_FINISHED){
        reboot(RB_AUTOBOOT);
    }
}

int main(int argc, char *argv[]){
    //char url[256] = "http://148.70.52.169:8080/update.img";
    if(argc == 2){
        RK_ota_set_url(argv[1]);
        RK_ota_start(handle_upgrade_callback);
        RK_ota_get_progress();
    }else if(argc == 3){
        RK_ota_set_url(argv[1]);
        RK_ota_start(handle_upgrade_callback_reboot);
        RK_ota_get_progress();
    }
    return 0;
}

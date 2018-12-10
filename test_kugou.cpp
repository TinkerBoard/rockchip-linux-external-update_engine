#include <iostream>
#include "kugou.h"

void handle_upgrade_callback(void *user_data, RK_Upgrade_Status_t status){

}

int main(int argc, char *argv[]){
    char url[256] = "http://148.70.52.169:8080/update.img";
    RK_ota_set_url(url);
    RK_ota_start(handle_upgrade_callback);
    RK_ota_get_progress();

    return 0;
}

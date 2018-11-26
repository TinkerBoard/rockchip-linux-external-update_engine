#include <iostream>
#include "kugou.h"
#include "deviceInfo.h"
#include "log.h"
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

#include "tomcat.h"

static char * _url;
static pthread_t a_thread;

static void *thread_function(void *arg){
    int res;
    res = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if(res != 0){
        LOGE("Thread pthread_setcancelstate failed.\n");
        exit(EXIT_FAILURE);
    }
    //res = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    res = pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    if(res != 0){
        LOGE("Thread pthread_setcanceltype failed");
        exit(EXIT_FAILURE);
    }
    LOGI("thread_function is running\n");
    getDataFromUrl(_url);
    LOGI("thread_function is stop\n");

    pthread_exit(0);
}

void RK_ota_set_url(char *url){
    if(url == NULL){
        LOGE("RK_ota_set_url : url is NULL.\n");
        return ;

    }
    _url = url;
}

void RK_ota_start(RK_upgrade_callback cb){
    LOGI("start RK_ota_start.\n");
    int res;
    void *thread_result;

    cb(NULL, RK_UPGRADE_START);
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if(res != 0){
        LOGE("Thread creation failed.");
        cb(NULL, RK_UPGRADE_ERR);
        return ;
    }
    LOGI("waiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if(res != 0){
        LOGE("Thread join failed.\n");
        cb(NULL, RK_UPGRADE_ERR);
        exit(EXIT_FAILURE);
    }
    cb(NULL, RK_UPGRADE_FINISHED);
}

void RK_ota_stop(){
    int res;
    LOGI("start RK_ota_stop.\n");
    res = pthread_cancel(a_thread);
    if(res != 0){
        LOGE("Thread cancelation failed");
        exit(EXIT_FAILURE);
    }
}


int RK_ota_get_progress(){
    return showProgressValue();
}

void RK_ota_get_sw_version(char *buffer, int maxLength){
    DeviceInfoInternel info;
    info.setCurrentConfig();

    std::string ver = info.getCurrentVersion();
    if(ver.size() <= maxLength){
        memcpy(buffer, ver.c_str(), ver.size());
    }
}

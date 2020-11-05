#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t taskHandle1=NULL;
TaskHandle_t taskHandle2=NULL;

void myTask1(void *p){
    while(1){
        printf("hello world\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void myTask2(void *p){
    TickType_t mylastunblock=xTaskGetTickCount();
    while(1){
        printf("SRA is Great\n");
        vTaskDelayUntil(&mylastunblock,500/portTICK_PERIOD_MS);
    }
}

void app_main(){
    xTaskCreate(myTask1,"Task 1",2048,NULL,5,taskHandle1);
    xTaskCreate(myTask2,"Task 2",2048,NULL,5,taskHandle2);

}
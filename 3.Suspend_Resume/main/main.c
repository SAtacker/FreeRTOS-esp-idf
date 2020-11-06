#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t taskhandle1=NULL;
TaskHandle_t taskhandle2=NULL;

void myTask1(void *p){
    int count =0;
    while(1){
        printf("Hello World: %d\n",count++);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}

void myTask2(void *p){
    while(1){
        vTaskDelay(5000/portTICK_PERIOD_MS);
        vTaskSuspend(taskhandle1);
        vTaskDelay(5000/portTICK_PERIOD_MS);
        vTaskResume(taskhandle1);
    }
}

void app_main(){
    xTaskCreate(myTask1,"Task 1",2048,NULL,5,&taskhandle1);
    xTaskCreate(myTask2,"Task 2",2048,NULL,5,&taskhandle2);
}
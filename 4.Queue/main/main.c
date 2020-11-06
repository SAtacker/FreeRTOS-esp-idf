#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

QueueHandle_t queue;

void listenForHTTP(void *p){
    int count=0 ;
    
    while(1){
        count++;
        printf("Received HTTP message \n");
        long ok=xQueueSend(queue,&count,1000/portTICK_PERIOD_MS);
        if(ok){
            printf("added message to queue\n");
        }
        else{
            printf("failed to add message to the queue\n");
        }
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

void Task1(void *params){
    while(true){
        int rxInt;
        if(xQueueReceive(queue,&rxInt,5000/portTICK_PERIOD_MS)){
            printf("doing something with http %d\n\n",rxInt);
        }
        
    }
}

void app_main(void){
    queue=xQueueCreate(3,sizeof(int));
    xTaskCreate(&listenForHTTP,"get HTTP",2048,NULL,2,NULL);
    xTaskCreate(&Task1,"Task 1",2048,NULL,1,NULL);
}
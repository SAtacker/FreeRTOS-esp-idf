#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void mytask1(void *p){
    while(1){
        printf("Hello %s\n",(char *)p);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void app_main(){
    char* name="Gautam";
    xTaskCreate(mytask1,"task1",2048,name,5,NULL);
    //parameters 
    //pvTaskCode:-Pointer to the task entry function (just the name of the function that implements the task
    //pcName:-A descriptive name for the task. This is mainly used to facilitate debugging, but can also be used to obtain a task handle.
    //usStackDepth:-The number of words (not bytes!) to allocate for use as the task’s stack
    //pvParameters:-A value that will passed into the created task as the task’s parameter.
    //uxPriority:-The priority at which the created task will execute.
    //pxCreatedTask:-Used to pass a handle to the created task out of the xTaskCreate() function
    //Returns:If the task was created successfully then pdPASS is returned. Otherwise errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY is returned.
}
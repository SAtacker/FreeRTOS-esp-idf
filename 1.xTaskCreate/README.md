# xTaskCreate

xTaskCreate() can only be used to create a task that has unrestricted access to the entire microcontroller memory map.

Parameters | Description
--- | --- 
**pvTaskCode** | Pointer to the task entry function (just the name of the function that implements the task)
**pcName** | A descriptive name for the task. This is mainly used to facilitate debugging, but can also be used to obtain a task handle.
**usStackDepth**|The number of words (not bytes!) to allocate for use as the task’s stack. For example, if the stack is 16-bits wide and usStackDepth is 100, then 200 bytes will be allocated for use as the task’s stack.
**pvParameters**|A value that will passed into the created task as the task’s parameter.It can be set to be NULL if there is no parameters.
**uxPriority**|The priority at which the created task will execute.This should be between 1-10 for general use.
**pxCreatedTask**|Used to pass a handle to the created task out of the xTaskCreate() function. pxCreatedTask is optional and can be set to NULL.

## **Returns**
If the task was created successfully then pdPASS is returned. Otherwise errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY is returned
            

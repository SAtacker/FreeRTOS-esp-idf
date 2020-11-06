# vTaskSuspend
void vTaskSuspend( TaskHandle_t xTaskToSuspend );
* Suspend any task. When suspended a task will never get any microcontroller processing time, no matter what its priority.
* Calls to vTaskSuspend are not accumulative – i.e. calling vTaskSuspend () twice on the same task still only requires one call to vTaskResume () to ready the suspended task.
* It does not return anything.

Parameters|Description
--- | ---
**xTaskToSuspend**|Handle to the task being suspended. Passing a NULL handle will cause the calling task to be suspended.

# vTaskResume
void vTaskResume( TaskHandle_t xTaskToResume )
* Resumes a suspended task.
* A task that has been suspended by one or more calls to vTaskSuspend () will be made available for running again by a single call to vTaskResume.
* It also doesn't return anything.

Parameters|Description
--- | ---
**xTaskToResume**|Handle to the task being readied.




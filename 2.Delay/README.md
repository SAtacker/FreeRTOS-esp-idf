# vTaskDelay
* Delay a task for a given number of ticks.The actual time that the task remains blocked depends on the tick rate.
* The constant portTICK_PERIOD_MS can be used to calculate real time from the tick rate – with the resolution of one tick period.vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called.

Parameters|Description
--- | ---
**xTicksToDelay**|The amount of time, in tick periods, that the calling task should block.


* Note:- The FreeRTOS will run other task in background while the vTaskDelay is running,and it will comeback and check whether the task is completed or not,so it may sometimes gives more delay than required.vTaskDelay will make sure you get the delay of minimum of the given parameters, example :- It may give the delay of 1020ms instead of 1000ms. So to avoid this problem we use vTaskDelayUntil().


# vTaskDelayUntil
* Delay a task until a specified time. This function can be used by periodic tasks to ensure a constant execution frequency.
* This function differs from vTaskDelay() in one important aspect: vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called, whereas vTaskDelayUntil() specifies an absolute time at which the task wishes to unblock.

Parameters|Description
--- | ---
**pxPreviousWakeTime**|Pointer to a variable that holds the time at which the task was last unblocked. The variable must be initialised with the current time prior to its first use. Following this the variable is automatically updated within vTaskDelayUntil().
**xTimeIncrement**|The cycle time period. The task will be unblocked at time (*pxPreviousWakeTime + xTimeIncrement). Calling vTaskDelayUntil with the same xTimeIncrement parameter value will cause the task to execute with a fixed interval period.

## Difference Between vTaskDelay and vTaskDelayUntil

vTaskDelay|vTaskDelayUntil
--- | ---
In vTaskDelay you say how long after calling vTaskDelay you want to be woken.|In vTaskDelayUntil you say the time at which you want to be woken.
The parameter in vTaskDelay is the delay period in the number of ticks from now.|The parameter in vTaskDelayUntil is the absolute time in ticks at which you want to be woken calculated as an increment from the time you were last woken.







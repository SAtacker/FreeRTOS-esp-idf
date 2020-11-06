# xQueueCreate
QueueHandle_t xQueueCreate( UBaseType_t uxQueueLength,UBaseType_t uxItemSize );
* Creates a new queue and returns a handle by which the queue can be referenced.
* Each queue requires RAM that is used to hold the queue state, and to hold the items that are contained in the queue (the queue storage area). 
* If a queue is created using xQueueCreate() then the required RAM is automatically allocated from the FreeRTOS heap. If a queue is created using xQueueCreateStatic() then the RAM is provided by the application writer, which results in a greater number of parameters, but allows the RAM to be statically allocated at compile time

Parameters|Description
--- | ---
**uxQueueLength**|Handle to the task being suspended. Passing a NULL handle will cause the calling task to be suspended.
**uxItemSize**|The size, in bytes, required to hold each item in the queue.Items are queued by copy, not by reference, so this is the number of bytes that will be copied for each queued item. Each item in the queue must be the same size.

* **RETURN:-** If the queue is created successfully then a handle to the created queue is returned. If the memory required to create the queue could not be allocated then NULL is returned.

# xQueueSend
BaseType_t xQueueSend(QueueHandle_t xQueue,const void * pvItemToQueue,TickType_t xTicksToWait)
* Post an item on a queue. The item is queued by copy, not by reference. 
* This function must not be called from an interrupt service routine. See xQueueSendFromISR() for an alternative which may be used in an ISR.

Parameters|Description
--- | ---
**xQueue**|The handle to the queue on which the item is to be posted.
**pvItemToQueue**|A pointer to the item that is to be placed on the queue. The size of the items the queue will hold was defined when the queue was created, so this many bytes will be copied from pvItemToQueue into the queue storage area.
**xTicksToWait**|The maximum amount of time the task should block waiting for space to become available on the queue, should it already be full. The call will return immediately if the queue is full and xTicksToWait is set to 0. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.

* **RETURN:-** pdTRUE if the item was successfully posted, otherwise errQUEUE_FULL

# xQueueReceive
BaseType_t xQueueReceive(QueueHandle_t xQueue,void *pvBuffer,TickType_t xTicksToWait)
* Receive an item from a queue. The item is received by copy so a buffer of adequate size must be provided.
* The number of bytes copied into the buffer was defined when the queue was created.
* This function must not be used in an interrupt service routine. See xQueueReceiveFromISR for an alternative that can.

Parameters|Description
--- | ---
**xQueue**|The handle to the queue on which the item is to be received.
**pvBuffer**|Pointer to the buffer into which the received item will be copied.
**xTicksToWait**|The maximum amount of time the task should block waiting for an item to receive should the queue be empty at the time of the call. Setting xTicksToWait to 0 will cause the function to return immediately if the queue is empty. The time is defined in tick periods so the constant portTICK_PERIOD_MS should be used to convert to real time if this is required.

* **RETURN:-** pdTRUE if an item was successfully received from the queue, otherwise pdFALSE.








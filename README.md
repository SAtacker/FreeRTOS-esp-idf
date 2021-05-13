# FreeRTOS-esp-idf
Learning FreeRTOS in ESP-IDF

# Table Of Contents
- [FreeRTOS-esp-idf](#freertos-esp-idf)
- [Table Of Contents](#table-of-contents)
  - [What Is An RTOS](#what-is-an-rtos)
  - [Why Use An RTOS](#why-use-an-rtos)
  - [What should be considered when choosing an RTOS](#what-should-be-considered-when-choosing-an-rtos)
  - [How does the RTOS affect the development of the design](#how-does-the-rtos-affect-the-development-of-the-design)
  - [Scheduling Algorithm](#scheduling-algorithm)
    - [Preemptive Scheduling](#preemptive-scheduling)
    - [Non Preemptive Scheduling](#non-preemptive-scheduling)
  - [Difference between RTOS and GPOS](#difference-between-rtos-and-gpos)
  - [Introduction to FreeRTOS](#introduction-to-freertos)
  - [General Overview](#general-overview)
    - [Tasks](#tasks)
    - [Scheduling](#scheduling)
    - [FreeRTOS Prioritized Preemptive Scheduling with Time Slicing](#freertos-prioritized-preemptive-scheduling-with-time-slicing)
    - [Context Switching](#context-switching)
  - [What Is Stack Memory](#what-is-stack-memory)
  - [Tech Stack Size](#tech-stack-size)
  - [Controlling Stacks](#controlling-stacks)
  - [Some More](#some-more)
    - [Benchmarks](#benchmarks)
  * [FreeRTOS for ESP32](#freertos-for-esp32)
  * [Creating And Deleting Tasks](#creating-and-deleting-tasks)
    * [xTaskCreate](#xtaskcreate)
    * [vTaskDelete](#vtaskdelete)
  * [Delays](#delays)
  * [Suspending And Resuming Task](#suspending-and-resuming-task) 
  * [FreeRTOS InterTask Communication](#freertos-intertask-communication)
    * [Queue Communication](#queue-communication)
    * [Semaphores](#semaphores)
      * [Mutex](#mutex)
      * [Binary Semaphore](#binary-semaphore)
      * [Counting Semaphore](#counting-semaphore)
- [Resources](#resources)



## What Is An RTOS

* A Real Time Operating System, commonly known as an RTOS, is a software component that rapidly switches between tasks, giving the impression that multiple programs are being executed at the same time on a single processing core.

![](https://scienceprog.com/wp-content/uploads/2011/07/freertos_multitasking.gif)

* In actual fact the processing core can only execute one program at any one time, and what the RTOS is actually doing is rapidly switching between individual programming threads (or Tasks) to give the impression that multiple programs are executing simultaneously.

* An RTOS is designed to provide a predictable execution pattern and is employed when processing must conform to the time constraints of a time-bound system (i.e., processing is completed at a certain frequency or the system as a whole will fail).

* Because an RTOS is designed to respond to events quickly and perform under heavy loads, it can be slower at big tasks when compared to another OS.

## Why Use An RTOS

There are well-established techniques for writing good embedded software without the use of an RTOS. In some cases, these techniques may provide the most appropriate solution; however as the solution becomes more complex, the benefits of an RTOS become more apparent. These include:

* **Priority Based Scheduling** : The ability to separate critical processing from non-critical is a powerful tool.

* **Abstracting Timing Information** : The RTOS is responsible for timing and provides API functions. This allows for cleaner (and smaller) application code.

* **Maintainability/Extensibility** : Abstracting timing dependencies and task based design results in fewer interdependencies between modules. This makes for easier maintenance.

* **Modularity** : The task based API naturally encourages modular development as a task will typically have a clearly defined role.

* **Promotes Team Development** : The task-based system allows separate designers/teams to work independently on their parts of the project.

* **Easier Testing** : Modular task based development allows for modular task based testing.

* **Code Reuse** : Another benefit of modularity is that similar applications on similar platforms will inevitably lead to the development of a library of standard tasks.

* **Improved Efficiency**: An RTOS can be entirely event driven; no processing time is wasted polling for events that have not occurred.

* **Idle Processing** : Background or idle processing is performed in the idle task. This ensures that things such as CPU load measurement, background CRC checking etc will not affect the main processing.

## What should be considered when choosing an RTOS

* **Responsiveness** : The RTOS scheduling algorithm, interrupt latency and context switch times will significantly define the responsiveness and determinism of the system. The most important consideration is what type of response is desired – Is a hard real time response required? This means that there are precisely defined deadlines that, if not met, will cause the system to fail. Alternatively, would a non-deterministic, soft real time response be appropriate? In which case there are no guarantees as to when each task will complete.

* **Available system resources** : Micro kernels use minimum system resources and provide limited but essential task scheduling functionality. Micro kernels generally deliver a hard real time response, and are used extensively with embedded microprocessors with limited RAM/ROM capacity, but can also be appropriate for larger embedded processor systems.

Alternatively, a full featured OS like Linux or WinCE could be used. These provide a feature rich operating system environment, normally supplied with drivers, GUI’s and middleware components. Full featured OS’s are generally less responsive, require more memory and more processing power than micro kernels, and are mainly used on powerful embedded processors where system resources are plentiful.

* **Open source or professionally licensed** : There are widely used, free open source RTOS’s available, distributed under GPL or modified GPL licenses. However, these licenses may contain copy left restrictions and offer little protection. Professionally licensed RTOS products remove the copy left restrictions, offer full IP infringement indemnification and warranties. In addition, you have a single company providing support and taking responsibility for the quality of your product.

* **Quality** : What emphasis does the RTOS supplier place on quality within their organisation? Quality is more than just a coding standard. Are the correct procedures in place to guarantee the quality of future products and support? Well-managed companies that take quality seriously tend to be ISO 9001 certified.

* **Safety Certification** : Pre-certified and certifiable RTOS’s are available for applications that require certification to international design standards such as DO-178C and IEC 61508. These RTOS’s provide key safety features, and the design evidence required by certification bodies to confirm that the process used to develop the RTOS meets the relevant design standard.

* **Licensing** : It’s not only the RTOS functionality and features that you’ll need to consider, but the licensing model that will work best for your project budget and the company’s “return on investment”.

* **RTOS Vendor** : The company behind the RTOS is just as important as selecting the correct RTOS itself. Ideally you want to build a relationship with a supplier that can support not only your current product, but also your products of the future. To do this you need to select a proactive supplier with a good reputation, working with leading silicon manufacturers to ensure they can support the newest processors and tools.

Trust, quality of product, and quality of support is everything.

## How does the RTOS affect the development of the design
The choice of RTOS can greatly affect the development of the design. By selecting an appropriate RTOS the developer gains:

* A Task based design that enhances modularity, simplifies testing and encourages code reuse
* An environment that makes it easier for engineering teams to develop together
* Abstraction of timing behaviour from functional behaviour, which should result in smaller code size and more efficient use of available resources.


Peripheral support, memory usage and real-time capability are key features that govern the suitability of the RTOS. Using the wrong RTOS, particularly one that does not provide sufficient real time capability, will severely compromise the design and viability of the final product.

The RTOS needs to be of high quality and easy to use. Developing embedded projects is difficult and time consuming – the developer does not want to be struggling with RTOS related problems as well. The RTOS must be a trusted component that the developer can rely on, supported by in-depth training and good, responsive support.

## Scheduling Algorithm

* All operating systems use schedulers to allocate CPU time to tasks or threads. Because only one process can run at a given time on the CPU in case of a single core processor
* A task can be in one of these four possible states such as running, ready, blocked, suspended. Only tasks that are in ready state can be picked by a scheduler depending on the scheduling policy.
* Scheduling is the process of deciding which task should be executed at any point in time based on a predefined algorithm. The logic for the scheduling is implemented in a functional unit called the scheduler. 
* There are many scheduling algorithms that can be used for scheduling task execution on a CPU. They can be classified into two main types: preemptive scheduling algorithms and non-preemptive scheduling algorithms.

### Preemptive Scheduling

* Preemptive scheduling allows the interruption of a currently running task, so another one with more “urgent” status can be run. The interrupted task is involuntarily moved by the scheduler from running state to ready state. This dynamic switching between tasks that this algorithm employs is, in fact, a form of multitasking. It requires assigning a priority level for each task. A running task can be interrupted if a task with a higher priority enters the queue.

* As an example let’s have three tasks called Task 1, Task 2 and Task 3. Task 1 has the lowest priority and Task 3 has the highest priority. Their arrival times and execute times are listed in the table below.

| Task Name | Arrival Time(μs) | Execute Time(μs) |
| :---: | :----: | :----: |
| Task 1 | 10 | 50 |
| Task 2 | 40 | 50 |
| Task 3 | 60 | 40 |

* In above table we can see that Task 1 is the first to start executing, as it is the first one to arrive (at t = 10 μs ). Task 2 arrives at t = 40μs and since it has a higher priority, the scheduler interrupts the execution of Task 1 and puts Task 2 into running state. Task 3 which has the highest priority arrives at t = 60 μs. At this moment Task 2 is interrupted and Task 3 is put into running state. As it is the highest priority task it runs until it completes at t = 100 μs. Then Task 2 resumes its operation as the current highest priority task. Task 1 is the last to complete is operation.

![](https://open4tech.com/wp-content/uploads/2019/11/preemptive_scheduling.jpg)

* The main advantage of a preemptive scheduler is that it provides an excellent mechanism where the importance of every task may be precisely defined. On the other hand, it has the disadvantage that a high priority task may starve the CPU such that lower priority tasks can never have the chance to run.This can usually happen if there are programming errors such that the high priority task runs continuously without having to wait for any system resources and never stops

* Most RTOS uses Preemptive scheduling.

### Non Preemptive Scheduling
* In non-preemptive scheduling, the scheduler has more restricted control over the tasks. It can only start a task and then it has to wait for the task to finish or for the task to voluntarily return the control. A running task can’t be stopped by the scheduler.
* If we take the three tasks specified in the table from the previous chapter and schedule them using a non-preemptive algorithm we get the behavior shown in below figure.Once started, each task completes its operation and then the next one starts.

![](https://open4tech.com/wp-content/uploads/2019/10/non_preemptive_scheduling.jpg)



## Difference between RTOS and GPOS

* The basic difference of using a GPOS or an RTOS lies in the nature of the system – i.e whether the system is “time critical” or not! A system can be of a single purpose or multiple purpose. Example of a “time critical system” is – Automated Teller Machines (ATM). Here an ATM card user is supposed to get his money from the teller machine within 4 or 5 seconds from the moment he press the confirmation button. The card user will not wait 5 minutes at the ATM after he pressed the confirm button. So an ATM is a time critical system. Where as a personal computer (PC) is not a time critical system. The purpose of a PC is multiple. A user can run many applications at the same time. After pressing the SAVE button of a finished document, there is no particular time limit that the doc should be saved within 5 seconds. It may take several minutes (in some cases) depending upon the number of tasks and processes running in parallel.

| Characteristics | Real Time Operating System (RTOS) | General Purpose Operating System (GPOS) |
| :---: | :----: | :----: |
| Time Critical |An RTOS differs in that it typically provides a hard real time response, providing a fast, highly deterministic reaction to external events | OS’s typically provide a non-deterministic, soft real time response, where there are no guarantees as to when each task will complete, but they will try to stay responsive to the user. |
| Task Scheduling | RTOS uses pre-emptive task scheduling method which is based on priority levels. Here a high priority process gets executed over the low priority ones. | In the case of a GPOS – task scheduling is not based on  “priority” always! GPOS is programmed to handle scheduling in such a way that it manages to achieve high throughput |
| Hardware and Economical Factors | An RTOS is usually designed for a low end, stand alone device like an ATM, Vending machines, Kiosks etc. RTOS is light weight and small in size compared to a GPOS | A GPOS is made for high end, general purpose systems like a personal computer, a work station, a server system etc |
| Latency Issues | An RTOS has no such issues because all the process and threads in it has got bounded latencies – which means – a process/thread will get executed within a specified time limit | GPOS is unbounded dispatch latency, which most GPOS falls into. The more number of threads to schedule, latencies will get added up |
| Preemptible Kernel | The kernel of an RTOS is preemptible | A GPOS kernel is not preemptible |
| Examples | FreeRTOS,Embox etc.. | MacOS, Ubuntu etc.. |

* If kernel is not preemptible, then a request/call from kernel will override all other process and threads. For example:- a request from a driver or some other system service comes in, it is treated as a kernel call which will be served immediately overriding all other process and threads. In an RTOS the kernel is kept very simple and only very important service requests are kept within the kernel call. All other service requests are treated as external processes and threads. All such service requests from kernel are associated with a bounded latency in an RTOS. This ensures highly predictable and quick response from an RTOS.

## Introduction to FreeRTOS
- Kernel (Wikipedia Def): It is the "portion of the operating system code that is always resident in memory", and facilitates interactions between hardware and software components. 
- FreeRTOS is Open Source (MIT + Commercial license) RTOS kernel for embedded devices. It has been ported
  over to >35 uC platforms. 
- Good Documentation , Small Memory Footprint , Modular Libraries and support
  for 40+ Architectures , etc. are some more features of FreeRTOS.
- Since 2017 Amazon has contributed in many updates to the original kernel apart
  from AWS freeRTOS

The structure of the FreeRTOS/Source directory is shown below.
```
FreeRTOS
    |
    +-Source        The core FreeRTOS kernel files
        |
        +-include   The core FreeRTOS kernel header files
        |
        +-Portable  Processor specific code.
            |
            +-Compiler x    All the ports supported for compiler x
            +-Compiler y    All the ports supported for compiler y
            +-MemMang       The sample heap implementations
```

Features Overview :
- Tasks
- Queues, Mutexes, Semaphores
- Direct To Task Notifications
- Stream and Message Buffers
- Software Timers
- Event Groups or Flags
- Static vs Dynamic Memory
- Heap Management
- Stack Overflow Protection
- Co-Routines (Deprecated)
- Compile Time configurable
- Additional Libraries
   
## General Overview

### Tasks

Each executing program is a task (or thread) under control of the operating
system and hence if it can execute multiple tasks then it is said to be
multi-tasking. However it is not concurrent.

* A task is a sequential piece of code - it does not know when it is going to get suspended (swapped out or switched out) or resumed (swapped in or switched in) by the kernel and does not even know when this has happened. 

* Consider the example of a task being suspended immediately before executing an instruction that sums the values contained within two processor registers. While the task is suspended other tasks will execute and may modify the processor register values. Upon resumption the task will not know that the processor registers have been altered - if it used the modified values the summation would result in an incorrect value.

### Scheduling

* The scheduler is the part of the kernel responsible for deciding which task
  should be executing at any particular time. The kernel can suspend and later
  resume a task many times during the task lifetime. 

![Scheduling](https://www.freertos.org/fr-content-src/uploads/2018/07/RTExample.gif)

* The RTOS created an Idle task which will execute only when there are no other tasks able to do so. The RTOS idle task is always in a state where it is able to execute.
* When sleeping, an RTOS task will specify a time after which it requires 'waking'. When blocking, an RTOS task can specify a maximum time it wishes to wait.
* Tick - The tick count variable is incremented with strict timing accuracy
  allowing it to measure time to a resolution of chosen timer interrupt
  frequency.
* The Kernel keeps checking if its time to unblock or wake a task.
  
### FreeRTOS Prioritized Preemptive Scheduling with Time Slicing
FreeRTOS kernel supports two types of scheduling policy: 

* **Time Slicing Scheduling Policy** : This is also known as a round-robin algorithm. In this algorithm, all equal priority tasks get CPU in equal portions of CPU time. 
* **Fixed Priority Preemptive Scheduling** : This scheduling algorithm selects tasks according to their priority. In other words, a high priority task always gets the CPU before a low priority task. A low priority task gets to execute only when there is no high priority task in the ready state. 

FreeRTOS uses the combination of above two Scheduling Policy , so the scheduling policy is **FreeRTOS Prioritized Preemptive Scheduling with Time Slicing**

* In this case, a scheduler can not change the priority of scheduled tasks. But tasks can change their own priority by using FreeRTOS priority changing API
* Because this scheduling algorithm also uses Preemptive scheduling, therefore, a high priority task can immediately preempt a low priority running task. Whenever low priority task gets preempted by a high priority task, a low priority task enters the ready state and allows a high priority task to enter the running state.
* The last part of this scheduling algorithm is a time-slicing feature. In this case, all equal priority tasks get shared CPU processing time. Time slicing is achieved by using FreeRTOS tick interrupts. 



![](https://microcontrollerslab.com/wp-content/uploads/2020/06/FreeRTOS-Preemptive-scheduling-algorithm-example.jpg)

This picture shows the timing diagram about the execution sequence of high, medium and low priority tasks.



**Note** 

* The idle task is created automatically when the RTOS scheduler is started to ensure there is always at least one task that is able to run. It is created at the lowest possible priority to ensure it does not use any CPU time if there are higher priority application tasks in the ready state.
* *Periodic Tasks* : In periodic task, jobs are released at regular intervals. A periodic task is one which repeats itself after a fixed time interval
* *Continuous Task* : A continuous processing task is a task that never enters the Blocked state
* *Event Task* : The task scheduled to be invoked at occurence of particular event. 




![](https://microcontrollerslab.com/wp-content/uploads/2020/06/FreeRTOS-Preemptive-time-slicing-scheduling-algorithm-example.jpg)

* This diagram shows the execution sequence of tasks according to time-slicing policy.
### Context Switching

* As a task executes it utilizes the processor / microcontroller registers and accesses RAM and ROM just as any other program. These resources together (the processor registers, stack, etc.) comprise the task execution context.

![Img](https://www.freertos.org/fr-content-src/uploads/2018/07/ExeContext.gif)

* The error that we stumbled upon during task execution (that the summation gave
  wrong result because the registers were manipulated by some other task) needed
  some "context".
* It is essential that upon resumption a task has a context identical to that
  immediately prior to its suspension. FreeRTOS does so by saving the context of
  a task as it is suspended and restored prior to its execution.
* The process of saving the context of a task being suspended and restoring the context of a task being resumed is called context switching.

![PremptiveContext](https://www.freertos.org/fr-content-src/uploads/2018/07/TickISR.gif)
- Referring to the numbers in the diagram above:
 - At (1) the RTOS idle task is executing.
 - At (2) the RTOS tick occurs, and control transfers to the tick ISR (3).
- The RTOS tick ISR makes vControlTask ready to run, and as vControlTask has a
  higher priority than the RTOS idle task, switches the context to that of
  vControlTask.
- As the execution context is now that of vControlTask, exiting the ISR (4)
  returns control to vControlTask, which starts executing (5).
- A context switch occurring in this way is said to be Preemptive, as the
  interrupted task is preempted without suspending itself voluntarily.

* Read more about [Saving Task Context](https://www.freertos.org/implementation/a00016.html)
   
A FreeRTOS application will start up and execute just like a non-RTOS
application until vTaskStartScheduler() is called. vTaskStartScheduler() is
normally called from the application's main() function. The RTOS only controls
the execution sequencing after vTaskStartScheduler() has been called.

## What Is Stack Memory

## Tech Stack Size

## Controlling Stacks

## Simple Task

## Controlling Task

## Some More

### Benchmarks
According to [this](http://blob.tomerweller.com/esp32-first-steps) ring
benchmark the esp32 arduino core is 35% slower than esp-idf's FreeRTOS.


# FreeRTOS for ESP32

* Many manufacturers produce SoC with freeRTOS support as it is most *peer-reviewed* rtos. Expressif included [freeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html) in its latest version ESP – IDF.
* The Espressif Internet Development Framework (ESP-IDF) uses FreeRTOS to make better use of the two high speed processors and manage the numerous built-in peripherals.
* It is done by creating tasks,let's look at creating task,

## Creating And Deleting Tasks
* We have discussed about the FreeRTOS task, In ESP-IDF too we have FreeRTOS api to create as well as delete tasks.
* We must also know that there is always an idle task running when there are no task scheduled to prevent RTOS from crashing.

### xTaskCreate

* ```c 
    static BaseType_t xTaskCreate(TaskFunction_t  pvTaskCode, 
                                  const char      *constpcName, 
                                  const uint32_t  usStackDepth, 
                                  void            *constpvParameters, 
                                  UBaseType_t     uxPriority, 
                                  TaskHandle_t    *constpvCreatedTask)
  ```
* Description :- xTaskCreate() can only be used to create a task that has unrestricted access to the entire microcontroller memory map.

Parameters | Description
--- | --- 
**pvTaskCode** | Pointer to the task entry function (just the name of the function that implements the task)
**pcName** | A descriptive name for the task. This is mainly used to facilitate debugging, but can also be used to obtain a task handle.
**usStackDepth**|The number of words (not bytes!) to allocate for use as the task’s stack. For example, if the stack is 16-bits wide and usStackDepth is 100, then 200 bytes will be allocated for use as the task’s stack.
**pvParameters**|A value that will passed into the created task as the task’s parameter.It can be set to be NULL if there is no parameters.
**uxPriority**|The priority at which the created task will execute.This should be between 1-10 for general use.
**pxCreatedTask**|Used to pass a handle to the created task out of the xTaskCreate() function. pxCreatedTask is optional and can be set to NULL.

* **Example** :- This example will create two tasks with equal priorities. In this example It is also demonstrated how to pass paramters to the task.

```c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void * params)
{
  while (true)
  {
    printf("reading temperature from %s\n", (char *) params);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void task2(void * params) 
{
  while (true)
  {
    printf("reading humidity from %s\n", (char *) params);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void app_main(void)
{
   const char* task1_paramter = "task 1";
   const char* task2_paramter = "task 2"; 
   xTaskCreate(&task1, "temperature reading", 2048, (void*) task1_paramter, 2, NULL);
   xTaskCreate(&task2, "humidity reading", 2048, (void*)task2_paramter, 2, NULL);
}

```
### vTaskDelete

* ```c
  void vTaskDelete( TaskHandle_t xTask )
  ```

* **Description** :- Remove a task from the RTOS kernels management. The task being deleted will be removed from all ready, blocked, suspended and event lists.

NOTE: The idle task is responsible for freeing the RTOS kernel allocated memory from tasks that have been deleted. It is therefore important that the idle task is not starved of microcontroller processing time if your application makes any calls to vTaskDelete (). Memory allocated by the task code is not automatically freed, and should be freed before the task is deleted.

Parameters | Description
--- | --- 
**xTask** | The handle of the task to be deleted. Passing NULL will cause the calling task to be deleted.

* Example :- This example is similar to the previous example , but in this we will delete one task using Task Handler , other task by simply passing NULL in vTaskDelete api.
 ```c
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

TaskHandle_t task2_handler=NULL;

void task1(void *params)
{

    for (int i = 0; i < 5; i++)
    {
        printf("reading temperature from %s\n", (char *)params);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task2(void *params)
{
    for (int i = 0; i < 5; i++)
    {
        printf("reading humidity from %s\n", (char *)params);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    if(task2_handler!=NULL){
        vTaskDelete(task2_handler);
    }
    
}

void app_main(void)
{
    const char *task1_paramter = "task 1";
    const char *task2_paramter = "task 2";
    xTaskCreate(&task1, "temperature reading", 2048, (void *)task1_paramter, 2, NULL);
    xTaskCreate(&task2, "humidity reading", 2048, (void *)task2_paramter, 2, &task2_handler);
}
 
 ```

# Resources
* [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
* [ESP IDF FreeRTOS Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html)
* [FreeRTOS Features specific to ESP IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_additions.html)



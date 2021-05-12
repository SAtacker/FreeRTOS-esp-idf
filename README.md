# FreeRTOS-esp-idf
Learning FreeRTOS in ESP-IDF

# Table Of Contents
* [What Is An RTOS](#what-is-an-rtos)
  * [Why Use An RTOS](#why-use-an-rtos)
  * [What should be considered when choosing an RTOS](#what-should-be-considered-when-choosing-an-rtos)
  * [How does the RTOS affect the development of the design](#how-does-rtos-affect-the-development-of-the-design)
  * [Scheduling Algorithm](#scheduling-algorithm) 
  * [Difference between RTOS and GPOS](#difference-between-rtos-and-gpos)
* [Introduction To FreeRTOS](#introduction-to-freertos)
  * [The Main Function](#the-main-function)
  * [What Is Stack Memory](#what-is-stack-memory)
  * [Tech Stack Size](#tech-stack-size)
  * [Controlling Stacks](#controlling-stacks)
  * [Simple Task](#simple-task)
  * [Controlling Task](#controlling-task)
* [FreeRTOS for ESP32](#freertos-for-esp32)
  * [Creating And Deleting Tasks](#creating-and-deleting-tasks)
  * [Delays](#delays)
  * [Suspending And Resuming Task](#suspending-and-resuming-task) 
  * [FreeRTOS InterTask Communication](#freertos-intertask-communication)
    * [Queue Communication](#queue-communication)
    * [Semaphores](#semaphores)
      * [Mutex](#mutex)
      * [Binary Semaphore](#binary-semaphore)
      * [Counting Semaphore](#counting-semaphore)
* [Resources](#resources)  



## What Is An RTOS

* A Real Time Operating System, commonly known as an RTOS, is a software component that rapidly switches between tasks, giving the impression that multiple programs are being executed at the same time on a single processing core.

![](https://scienceprog.com/wp-content/uploads/2011/07/freertos_multitasking.gif)

* In actual fact the processing core can only execute one program at any one time, and what the RTOS is actually doing is rapidly switching between individual programming threads (or Tasks) to give the impression that multiple programs are executing simultaneously.

* An RTOS is designed to provide a predictable execution pattern and is employed when processing must conform to the time constraints of a time-bound system (i.e., processing is completed at a certain frequency or the system as a whole will fail).

* Because an RTOS is designed to respond to events quickly and perform under heavy loads, it can be slower at big tasks when compared to another OS.

## Scheduling Algorithm

### Difference between RTOS and GPOS

* The basic difference of using a GPOS or an RTOS lies in the nature of the system – i.e whether the system is “time critical” or not! A system can be of a single purpose or multiple purpose. Example of a “time critical system” is – Automated Teller Machines (ATM). Here an ATM card user is supposed to get his money from the teller machine within 4 or 5 seconds from the moment he press the confirmation button. The card user will not wait 5 minutes at the ATM after he pressed the confirm button. So an ATM is a time critical system. Where as a personal computer (PC) is not a time critical system. The purpose of a PC is multiple. A user can run many applications at the same time. After pressing the SAVE button of a finished document, there is no particular time limit that the doc should be saved within 5 seconds. It may take several minutes (in some cases) depending upon the number of tasks and processes running in parallel.

| Characteristics | Real Time Operating System (RTOS) | General Purpose Operating System (GPOS) |
| :-----: | :-: | :-: |
| Time Critical |An RTOS differs in that it typically provides a hard real time response, providing a fast, highly deterministic reaction to external events | OS’s typically provide a non-deterministic, soft real time response, where there are no guarantees as to when each task will complete, but they will try to stay responsive to the user. |
| Task Scheduling | RTOS uses pre-emptive task scheduling method which is based on priority levels. Here a high priority process gets executed over the low priority ones. | In the case of a GPOS – task scheduling is not based on  “priority” always! GPOS is programmed to handle scheduling in such a way that it manages to achieve high throughput |
| Hardware and Economical Factors | An RTOS is usually designed for a low end, stand alone device like an ATM, Vending machines, Kiosks etc. RTOS is light weight and small in size compared to a GPOS | A GPOS is made for high end, general purpose systems like a personal computer, a work station, a server system etc |
| Latency Issues | An RTOS has no such issues because all the process and threads in it has got bounded latencies – which means – a process/thread will get executed within a specified time limit | GPOS is unbounded dispatch latency, which most GPOS falls into. The more number of threads to schedule, latencies will get added up |
| Preemptible Kernel | The kernel of an RTOS is preemptible | A GPOS kernel is not preemptible |
| Examples | FreeRTOS,Embox etc.. | MacOS, Ubuntu etc.. |

* If kernel is not preemptible, then a request/call from kernel will override all other process and threads. For example:- a request from a driver or some other system service comes in, it is treated as a kernel call which will be served immediately overriding all other process and threads. In an RTOS the kernel is kept very simple and only very important service requests are kept within the kernel call. All other service requests are treated as external processes and threads. All such service requests from kernel are associated with a bounded latency in an RTOS. This ensures highly predictable and quick response from an RTOS.

# Resources
* [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
* [ESP IDF FreeRTOS Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html)



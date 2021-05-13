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
    - [Difference between RTOS and GPOS](#difference-between-rtos-and-gpos)
  - [Introduction to FreeRTOS](#introduction-to-freertos)
  - [General Overview](#general-overview)
    - [Tasks](#tasks)
    - [Scheduling](#scheduling)
    - [Context Switching](#context-switching)
  - [What Is Stack Memory](#what-is-stack-memory)
  - [Tech Stack Size](#tech-stack-size)
  - [Controlling Stacks](#controlling-stacks)
  - [Simple Task](#simple-task)
  - [Controlling Task](#controlling-task)
  - [Some More](#some-more)
    - [Benchmarks](#benchmarks)
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

# Resources
* [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
* [ESP IDF FreeRTOS Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html)



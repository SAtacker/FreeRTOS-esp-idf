# FreeRTOS-esp-idf
Learning FreeRTOS in ESP-IDF

# Table Of Contents
* [What Is An RTOS](#what-is-an-rtos)
  * [Why Use An RTOS](#why-use-an-rtos)
  * [What should be considered when choosing an RTOS](#what-should-be-considered-when-choosing-an-rtos)
  * [How does the RTOS affect the development of the design](#how-does-the-rtos-affect-the-development-of-the-design)
  * [Scheduling Algorithm](#scheduling-algorithm) 
    * [Preemptive Scheduling](#preemptive-scheduling)
    * [Non Preemptive Scheduling](#non-preemptive-scheduling)
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

# Resources
* [FreeRTOS Documentation](https://www.freertos.org/Documentation/RTOS_book.html)
* [ESP IDF FreeRTOS Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html)



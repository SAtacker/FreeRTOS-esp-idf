## Deadlock Example
* FreeRTOS does not provide any solution to solve the problem of deadlock. 
* It can be only solved while designing real-time embedded systems. 
* We must design tasks such that the deadlock does not occur. 
* One other possibility is to not use the indefinite waiting time for the tasks to acquire the mutex. 
* Instead use a minimum possible blocked time for the task that will be waiting to take mutex. 
* If a task is not able to take mutex within that time, it should release other resources also. 
* In small real-time embedded systems, deadlock is not a big problem. 
* Because an application designer can easily trace deadlock while designing an application and can remove it before deploying an application in the market. 

## Task

* Find the solution to deadlock
  * By your method
  * Try using mutex instead of semaphore
  * Try changing the wait times
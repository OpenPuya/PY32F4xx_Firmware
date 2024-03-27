================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了FreeRTOS队列集的相关API函数应用，实现队列的入队和出队，信号量释放和获
取。通过打印log，观察出队/入队和释放/获取实现过程。

Function descriptions:
This example demonstrates the application of FreeRTOS queue related API functions 
to implement queue entry and exit, semaphore release and acquisition. By printing 
log, observe the implementation process of queue/queue and release/get.

================================================================================
测试环境：
测试用板：PY32F403_STK
MDK版本：5.28
IAR版本：9.20
GCC版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F403_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10

================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 通过串口调试助手打印的log信息，观察任务执行过程。
   Task1: 向队列发送一个值，发送成功，打印“queue send success!”信息。释放一个信号
          量，释放成功打印“semaphore release success!”信息。
   Task2: 从队列集中获取任务句柄，任务句柄为队列句柄，打印队列中存放的数值。任务
          句柄是信号量句柄，打印“Take semaphore succuss!”信息。

Example execution steps:
1. Compile and download the program to the MCU and run it;
2. You can use the log information printed by the serial debugging assistant to 
observe the task execution process.
   Task1: Send a value to the queue. If the value is successfully sent, print 
          "queue send success!". Message. release a semaphore and print "semaphore
          release success!" Message.
   Task2: Obtains the task handle from the queue set. The task handle is the queue
          handle and prints the value stored in the queue. The task handle is a 
          semaphore handle that prints "Take semaphore succuss!" Message.

================================================================================
注意事项：
此样例使用到了串口打印功能，相关配置请参考下面的步骤。
1. 编译并下载程序到MCU；
2. 通过USB转TTL模块连接PC与STK板，STK板与USB转TTL模块的连线方式如下：
   STK板        USB转TTL模块
   PA02(TX) --> RX
   PA03(RX) --> TX
   GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为115200；
4. 按STK板Reset按键，即可打印log数据。

Example execution steps:
This example uses the serial port printing function. For details about the 
configuration, see the following steps.
1. Compile and download the program to the MCU;
2. Connect the PC and STK board with a USB to TTL module. The connection between 
   the STK board and the USB to TTL module is as follows:
   STK board        USB to TTL module
   PA02(TX) --> RX
   PA03(RX) --> TX
   GND      --> GND
3. Open a serial debugging assistant on the PC and connect to the appropriate COM 
   port with the baud rate set to 115200;
4. Press the Reset button on the STK board to print log data.

Notes:

================================================================================

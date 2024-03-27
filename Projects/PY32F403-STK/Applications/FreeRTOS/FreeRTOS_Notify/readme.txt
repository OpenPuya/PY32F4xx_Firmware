================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了FreeRTOS任务通知的相关API函数应用，实现模拟信号量、模拟事件标志组、
模拟消息邮箱功能。通过串口log，观察任务通知模拟的实现过程。

Function descriptions:
This example demonstrates the application of API functions related to FreeRTOS 
task notification, and realizes the functions of simulated semaphore, simulated
event flag group, and simulated message mailbox. log in the serial port to 
observe the task notification simulation process.

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
   任务执行顺序为：Task3->Task2->Task1
   Task1: 任务通知向任务2释放一个信号量。任务通知向任务2事件标志组值的指定bit位写
          1，任务通知采用不覆写的方式，向任务2写值。
   Task2: 任务2获取信号量，获取成功，打印信号量的值。任务2获取任务通知存放的值，
          获取成功后，打印该值。

Example execution steps:
1. Compile and download the program to the MCU and run it;
2. You can use the log information printed by the serial debugging assistant to 
observe the task execution process.
   Task1: The task notification releases a semaphore to task 2. The task 
          notification writes 1 to the specified bit of the task 2 event flag 
          group value. The task notification writes the value to Task 2 without 
          overwriting.
   Task2: Task 2 Obtain the semaphore, obtain the semaphore successfully, and 
          print the semaphore value. Task 2 Obtain the value saved in the task 
          notification and print the value.

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

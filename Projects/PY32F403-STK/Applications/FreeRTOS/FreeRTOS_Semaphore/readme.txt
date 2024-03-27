================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了FreeRTOS信号量的相关API函数，实现二值信号量、计数型信号量和互斥信号
量三种信号量实验，通过串口log，观察三种信号量的实现过程。

Function descriptions:
This example demonstrates the related API functions of FreeRTOS semaphore, 
realizes the experiment of two semaphore, counting semaphore and mutual exclusion
semaphore, and observes the implementation process of the three semaphore through
serial port log.

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
   Task1: 释放二值/计数型信号量。获取和释放互斥信号量，打印释放/获取成功或失败信
          息。打印低优先级任务正在运行信息。
   Task2: 获取二值信号量，打印获取成功信息。获取计数型信号量，打印信号量值。打印
          中等优先级任务正在运行信息。
   Task3: 获取和释放互斥信号量，打印获取/释放成功或失败信息。打印高优先级任务正
          在运行信息。
   打印低/中/高优先级任务正在运行任务是为了验证互斥信号量优先级继承功能。

Example execution steps:
1. Compile and download the program to the MCU and run it;
2. You can use the log information printed by the serial debugging assistant to 
observe the task execution process.
   Task1: Give binary/count semaphore. Give and Take mutually exclusive semaphore,
          print Give/Take success or failure message. Displays information about 
          the running of a low-priority task.
   Task2: Take a binary semaphore and print a success message. Take a counting 
          semaphore and print the semaphore value. The running information of a 
          medium-priority task is displayed.
   Task3: Take and Give mutually exclusive semaphore, print obtain/release success
          or failure message. Print high priority job. Information in operation.
   Print Low/medium/High priority tasks The task is running to verify the mutex 
   priority inheritance function.

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

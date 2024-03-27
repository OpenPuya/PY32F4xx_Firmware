================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了FreeRTOS队列的相关API函数应用，实现队列的入队和出队。通过串口log，观
察任务出队和入队实现过程。

Function descriptions:
This example demonstrates the application of FreeRTOS queue related API functions
to implement queue entry and exit.By printing log, observe the implementation 
process of queuing and joining the queue.

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
   Task1: 向队列KeyQueue发送一个值，发送失败，打印“KeyQueue Full, data send fail!”
          信息。向队列BigDataQueue发送一个数组首地址，发送失败，打印“BIGDATAQueue 
          Full, data send fail!” 信息。
   Task2: 从队列KeyQueue接收一个值，接收成功，打印该值信息。
   Task3: 从队列BigDataQueue接收一组值，接收成功，打印该组值信息。

Example execution steps:
1. Compile and download the program to the MCU and run it;
2. You can use the log information printed by the serial debugging assistant to 
observe the task execution process.
   Task1: Failed to send a value to the KeyQueue. KeyQueue Full, data send fail!
          Message. If an array first address fails to be sent to BigDataQueue, 
          BIGDATAQueue Full, data send fail! Message.
   Task2: A value is received from the KeyQueue. If the value is received 
          successfully, the value information is printed.
   Task3: A set of values is received from the BigDataQueue. If the data is 
          received successfully, the set of values is printed.

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

================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例通过中断方式，演示了SD卡擦除、写、读功能。

Function descriptions:
This sample demonstrates SD card erase, write, read function by interrupt mode.
================================================================================
测试环境：
测试用板：PY32F403_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F403_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 插入SD卡，MCU侧SD卡引脚如下：
  PD2:  CMD
  PC8:  D0
  PC9:  D1
  PC10: D2
  PC11: D3
  PC12: SCK
2. 编译并下载程序；
3. 按复位按键，运行程序，程序对SD执行擦除、写、读操作；
4. 观察现象，如果写入和读取数据一致LED常亮，否则LED处于熄灭状态。

Example execution steps:
1. Insert SD card, MCU side SD card pins are as follows: 
  PD2:  CMD
  PC8:  D0
  PC9:  D1
  PC10: D2
  PC11: D3
  PC12: SCK
2.Compile and download programs; 
3. Press the reset button to run the program, which erases, writes and reads SD. 
4.  Observe the phenomenon, if the writing and reading data are consistent, the
LED is always on, otherwise the LED is off. 
================================================================================
注意事项：
本样例，选用的是“金士顿16GB”SD卡。

Notes:
This example uses a Kingston 16GB SD card. 
================================================================================
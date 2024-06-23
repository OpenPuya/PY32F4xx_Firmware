================================================================================
                                样例使用说明
                                Sample Description
================================================================================
功能描述：
此样例演示了GPIO外部中断功能，PA0引脚上的每一个下降沿都会产生中断，中断函数中
LED灯会翻转一次。

Function descriptions:
This example demonstrates the GPIO external interrupt function, where each
falling edge on the key (PA0) pin generates an interrupt, and the LED light
in the interrupt function toggle once.
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
1. 编译下载程序到MCU，并运行；
2. PA0上每一个下降沿，观察到LED翻转一次；

Example execution steps:
1.Compile and download the program to MCU and run it;
2.The LED was observed to flip once on each falling edge of PA0;
================================================================================
注意事项：

Notes:

================================================================================
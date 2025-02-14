================================================================================
                                样例使用说明
                              Sample Description
================================================================================
功能描述：
本样例主要演示如何配置SYSCLK(系统时钟), HCLK(AHB时钟), PCLK1(APB1时钟)、
PCLK2(APB2时钟)，并通过MCO输出系统时钟的8分频9MHz。

Function descriptions:
This example mainly demonstrates how to configure SYSCLK (system clock),
HCLK (AHB clock), PCLK1 (APB1 clock), PCLK2 (APB2 clock), and output the
8-division 9MHz system clock through MCO.
================================================================================
测试环境：
测试用板：PY32F403_STK
MDK版本： 5.28
IAR版本： 9.20
GCC 版本：GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F403_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 通过逻辑分析仪或示波器可观测到端口PA8输出频率为9MHz的波形；

Example execution steps:
1. compile and download the program to MCU and run it
2. The waveform of port PA8 with output frequency of 9MHz can be observed by 
logic analyzer or oscilloscope
================================================================================
注意事项：

Notes:

================================================================================
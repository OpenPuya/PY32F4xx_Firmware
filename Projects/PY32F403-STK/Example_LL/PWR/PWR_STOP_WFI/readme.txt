================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在sleep模式下，使用GPIO事件唤醒。

Function descriptions:
This sample demonstrates using GPIO event to wake up the MCU from sleep mode.
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
2. LED灯亮，按下按键，LED灯灭，进入sleep模式；
3. 在PA06上产生一个下降沿，程序退出sleep模式；
4. LED以200ms的间隔进行翻转。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The LED lights up. Press the button, and the LED turns off, entering 
sleep mode.
3.Generate a falling edge on PA06 to wake up the MCU from sleep mode.
4.The LED toggles at an interval of 200ms.
================================================================================
注意事项：

Notes:

================================================================================
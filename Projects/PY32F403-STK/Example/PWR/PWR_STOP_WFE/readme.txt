================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了stop模式下，通过GPIO事件唤醒功能。

Function descriptions:
This sample demonstrates the GPIO event wake-up feature in stop mode.

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
2. LED灯亮，按下按键，LED灯灭，进入stop模式；
3. 在PA06上产生一个下降沿，程序退出stop模式；
4. LED以500ms的间隔进行翻转。

Example execution steps:
1. Compile and download the program to the MCU and run it;
2. The LED will be on initially. Press the button, and the LED will turn off, 
   entering stop mode;
3. Generate a falling edge on PA06, and the program will exit stop mode;
4. The LED will toggle at intervals of 500ms.

================================================================================
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。

Notes:
1.To demonstrate this sample function, it is necessary to disconnect the SWD
cable and power it back on, as by default, the emulator will reset the
DBGMCU_CR.DBG_STOP position.
================================================================================

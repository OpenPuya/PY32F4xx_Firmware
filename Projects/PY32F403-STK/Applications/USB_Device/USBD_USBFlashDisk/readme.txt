================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了USB U盘功能
USB U盘主要是借助 USB MSC 类实现，将MCU的flash划分成两部分，0x08000000~0x08007FFF
作为用户代码区，0x08008000~0x8060000模拟成一个352Kbytes的U盘

Function descriptions:
This sample demonstrates the USB Udisk functionality.
USB Udisk is mainly implemented by USB MSC class, the MCU flash is divided into 
two region, 0x08000000~0x08007FFF as the user code area, 0x08008000~0x8060000 
simulated into a 352Kbytes USB flash drive
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
1. 下载并运行程序；
2. 通过usb连接线，一端连接STK板，另一端连接PC电脑；
3. PC端显示出一个352Kbytes的U盘，可以在U盘中存储数据

Example execution steps:
1. Download and run the program;
2. Connect the STK board to the PC computer using the USB cable;
3. A 352Kbytes USB Udisk is displayed on the PC. Data can be stored on the 
USB Udisk.

================================================================================
注意事项：
1. 第一次使用时PC端会弹出格式化U盘，请按提示格式化U盘即可。
2. 此样例使用的是384Kbytes flash的MCU，如果要应用到其它尺寸的flash，需要修改代码
3. 此样例中MCU的flash，只预留了32Kbytes给用户程序，如果用户程序超过32KBytes，需
要修改代码

1. When you use the USB flash drive for the first time, format the USB Udisk as
prompted. 
2. This example uses the MCU of 384Kbytes flash. If you want to apply other 
sizes of flash, you need to modify the code. 
3. In this example, the MCU flash reserves only 32Kbytes for the user program. 
If the user program exceeds 32KBytes, the code needs to be modified
================================================================================
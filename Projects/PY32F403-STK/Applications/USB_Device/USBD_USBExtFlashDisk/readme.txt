================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了USB U盘功能
USB U盘主要是借助 USB MSC 类实现，将PY25Q128模拟成128M的U盘

Function descriptions:
This sample demonstrates the USB Udisk functionality.
USB Udisk is mainly implemented by USB MSC class, which simulates the PY25Q128
as a 128MB USB flash drive.
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
3. PC端显示出一个128Mbytes的U盘，可以在U盘中存储数据

Example execution steps:
1. Download and run the program;
2. Connect the STK board to the PC computer using the USB cable;
3. A 128Mbytes USB Udisk is displayed on the PC. Data can be stored on the 
USB Udisk.

================================================================================
注意事项：
1. 第一次使用时PC端会弹出格式化U盘，请按提示格式化U盘即可。
2. 此样例使用的是128Mbytes flash的MCU
3. 和PY25Q128连接如下
PB12   -->  CS
PB13   -->  SCLK
PB14   -->  SO
PB15   -->  SI
PB10   -->  WP
PB11   -->  RESET
GND    -->  GND

1. When you use the USB flash drive for the first time, format the USB Udisk as
prompted. 
2. This example uses the MCU of 384Kbytes flash. If you want to apply other 
sizes of flash, you need to modify the code. 
3. Connect to PY25Q128 as follows:
PB12   -->  CS
PB13   -->  SCLK
PB14   -->  SO
PB15   -->  SI
PB10   -->  WP
PB11   -->  RESET
GND    -->  GND
================================================================================
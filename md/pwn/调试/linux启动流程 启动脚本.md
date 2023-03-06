---
title: linux启动流程 启动脚本
updated: 2022-08-28T14:33:10.0000000+08:00
created: 2022-05-10T11:16:18.0000000+08:00
---

# Linux 的启动流程
![image1](../../resources/image1-30.png)

BIOS硬件自检

BIOS程序首先检查，计算机硬件能否满足运行的基本条件，这叫做"硬件自检"（Power-On Self-Test），缩写为POST。

如果硬件出现问题，主板会发出不同含义的蜂鸣，启动中止。如果没有问题，屏幕就会显示出CPU、内存、硬盘等信息。

BIOS选择有启动程序的存储设备

读取主引导记录（Master boot record，缩写为MBR）找到操作系统的分区

[主引导记录 - 维基百科，自由的百科全书 (wikipedia.org)](https://zh.wikipedia.org/wiki/%E4%B8%BB%E5%BC%95%E5%AF%BC%E8%AE%B0%E5%BD%95)

读取该设备的第一个扇区，也就是读取最前面的512个字节。如果这512个字节的最后两个字节是0x55和0xAA，表明这个设备可以用于启动；如果不是，表明设备不能用于启动，控制权于是被转交给"启动顺序"中的下一个设备。这最前面的512个字节，就叫做"主引导记录"（Master boot record，缩写为MBR）。

主引导记录的结构

分区表

硬盘启动

![image2](../../resources/image2-15.png)

操作系统开始运行了，根文件系统也装载了

读入/boot目录下的内核文件

启动初始化进程 /sbin/init ：确定运行级别，运行启动程序

init进程读取文件 /etc/inittab ，第一行就是默认的级别

运行/etc/rc\${level}.d 目录下的启动程序脚本

（这些脚本其实都软连接到 /etc/init.d 目录下）

用户登录

login shell
# inittab文件

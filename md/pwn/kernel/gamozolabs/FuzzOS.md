---
title: FuzzOS
updated: 2023-01-16T15:27:46.0000000+08:00
created: 2023-01-16T15:10:03.0000000+08:00
---

启动流程
开机

reset（硬件启动）（实模式？）（设置初始ip地址为0xfffffff0)

可以访问这个网站查看初始状态

X86 architecture initial state <https://sandpile.org/>

Bios (地址在0xfffffff0)

如果是传统的bios启动，就load第一扇区(512字节）到地址0x7c00处并跳到那运行（实模式）

可以在作者的chocolate milk 里看PXE boot

如果是UEFI固件，则可以直接运行PE格式的操作系统，不用写任何汇编，没有大小限制（512B）

UEFI是一个标准，固件厂商安装这个提供api，操作系统可以直接用这个访问固件


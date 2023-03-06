---
title: buildroot
updated: 2022-06-09T10:51:13.0000000+08:00
created: 2022-04-18T14:21:36.0000000+08:00
---

[Buildroot](https://buildroot.org/)是Linux平台上一个构建嵌入式Linux系统的框架。
整个Buildroot是由Makefile(\*.mk)脚本和Kconfig(Config.in)配置文件构成的，因此可以像配置Linux内核一样执行make menuconfig进行配置，编译出一个完整的、可以直接烧写到机器上运行的Linux系统文件(包含bootloader、kernel、rootfs以及rootfs中的各种库和应用程序)。
[精通嵌入式Linux 第三章：Buildroot – LotLab](https://www.lotlab.org/2020/04/08/mastering-embedded-linux-part-3-buildroot/)

Buildroot配置
Buildroot使用
[通过buildroot+qemu搭建ARM-Linux虚拟开发环境 - ArnoldLu - 博客园 (cnblogs.com)](https://www.cnblogs.com/arnoldlu/p/9689585.html)

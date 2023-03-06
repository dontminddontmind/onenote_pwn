---
title: 'ldd3环境 '
updated: 2022-09-25T15:27:11.0000000+08:00
created: 2022-09-24T17:13:45.0000000+08:00
---

2.6.10环境
[ldd3( Linux Device Driver 3e ) (1)— 實驗環境建置以及編譯模組 \| by 吳建興 \| Medium](https://fdgkhdkgh.medium.com/ldd3-linux-device-driver-3e-%E5%AF%A6%E9%A9%97%E7%92%B0%E5%A2%83%E5%BB%BA%E7%BD%AE%E4%BB%A5%E5%8F%8A%E7%B7%A8%E8%AD%AF%E6%A8%A1%E7%B5%84-437c937a71f4)

内核源码 <https://mirrors.edge.kernel.org/pub/linux/kernel/v2.6/linux-2.6.10.tar.gz>

ubuntu 5.04 的内核是2.6.10

[使用Qemu运行Ubuntu文件系统（1） - 摩斯电码 - 博客园 (cnblogs.com)](https://www.cnblogs.com/pengdonglin137/p/9540670.html)

工具

o Gnu C 2.95.3 \# gcc --version  
o Gnu make 3.79.1 \# make --version  
o binutils 2.12 \# ld -v  
o util-linux 2.10o \# fdformat --version  
o module-init-tools 0.9.10 \# depmod -V  
o e2fsprogs 1.29 \# tune2fs  
o jfsutils 1.1.3 \# fsck.jfs -V  
o reiserfsprogs 3.6.3 \# reiserfsck -V 2\>&1\|grep reiserfsprogs  
o xfsprogs 2.6.0 \# xfs_db -V  
o pcmcia-cs 3.1.21 \# cardmgr -V  
o quota-tools 3.09 \# quota -V  
o PPP 2.4.0 \# pppd --version  
o isdn4k-utils 3.1pre1 \# isdnctrl 2\>&1\|grep version  
o nfs-utils 1.0.5 \# showmount --version  
o procps 3.2.0 \# ps --version  
o oprofile 0.5.3 \# oprofiled --version

*来自 \<<https://elixir.bootlin.com/linux/v2.6.10/source/Documentation/Changes>\>*

qemu运行
最新环境也能运行
<https://github.com/martinezjavier/ldd3>

<https://github.com/duxing2007/ldd3-examples-3.x>


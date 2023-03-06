---
title: linux安装ida pro
updated: 2021-09-04T11:21:39.0000000+08:00
created: 2021-09-04T11:19:58.0000000+08:00
---

0x1 更新源
dpkg --add-architecture i386
apt-get install libglib2.0-0:i386
apt-getinstalllibfreetype6-dev
apt-getinstalllibc6:i386
apt-getinstalllibfreetype6:i386
apt-getinstalllibsm-dev
apt-getinstalllibsm-dev:i386
apt-getinstalllibxrender1:i386
apt-getinstalllibfontconfig:i386
apt-getinstalllibxext6:i386
0x12 下载IDA Pro for Linux，解压。

如果这一步出现，缺少xxx.SO.0
比如缺少libgthread-2.0.so.0就输入，然后安装就好
dpkg -S libgthread-2.0.so.0

*来自 \<<https://www.52pojie.cn/forum.php?mod=viewthread&tid=542682&highlight=ida%2Bpro%2Blinux>\>*


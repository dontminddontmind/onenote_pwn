---
title: qemu调试 monitor
updated: 2022-08-24T20:20:58.0000000+08:00
created: 2022-06-17T10:22:17.0000000+08:00
---

- qemu有一个“监视器”，允许您查询模拟机器的状态。您可以通过键入\<Ctrl\>+a c（c表示控制台）来获得它。一个特别有用的monitor命令是info mem，用于打印页表。您可能需要使用cpu命令来选择info mem查看哪一个核心，或者可以使用make CPUS=1 qemu启动qemu，以使其只有一个核心。

*来自 \<<http://xv6.dgs.zone/labs/requirements/summary.html>\>*


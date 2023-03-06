---
title: MIT6.828
updated: 2022-10-21T15:26:15.0000000+08:00
created: 2022-06-13T11:49:54.0000000+08:00
---

[MIT6.828-神级OS课程-要是早遇到，我还会是这种 five 系列 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/74028717)

课程网址：[6.828: Operating System Engineering](https://link.zhihu.com/?target=https%3A//pdos.csail.mit.edu/6.828/2018/schedule.html)，一直跟着其 schedule 走就可以啦。

xv6 讲义：[a simple, Unix-like teaching operating system](https://link.zhihu.com/?target=https%3A//pdos.csail.mit.edu/6.828/2018/xv6/book-rev11.pdf)，讲义中会将每个部分的实现讲得十分详细，在代码编写时遇到不太清晰的概念时，可以多参考讲义。

我的实现环境：
- 虚拟机（VMware Workstation 和 VirtualBox 均可）
- Ubuntu16.04
- qemu，最好使用 MIT 给的 patch 版本（Lab6 用到 pacth 版本的qemu 较多）。安装方法也可参考[Tools Used in 6.828](https://link.zhihu.com/?target=https%3A//pdos.csail.mit.edu/6.828/2018/tools.html)链接
- 工具链[Tools Used in 6.828](https://link.zhihu.com/?target=https%3A//pdos.csail.mit.edu/6.828/2018/tools.html)
Homework 实现：完整实现代码。[Github_SmallPond/MIT6.828_OS](https://link.zhihu.com/?target=https%3A//github.com/SmallPond/MIT6.828_OS/tree/master/xv6-public)
- [MIT6.828_Homework_Shell_MIT_6.828](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/90544379)
- [MIT6.828_HW2_Boot_xv6_MIT6.828](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/90665444)
- [MIT6.828_HW3_XV6 System calls](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/91345372)
- [MIT6.828_HW4_xv6 lazy page allocation](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/91346550)
- [MIT6.828_HW5_xv6 CPU alarm](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/92838818)
- [MIT6.828_HW6_Threads and Locking](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/92838852)
- [MIT6.828_HW7_xv6 locking](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/93200120)
- [MIT6.828_HW8_User-level threads](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/94600772)
- [MIT6.828_HW9_barriers](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/94968225)
- [MIT6.828_HW10_Bigger file for xv6](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/95009224)
- [MIT6.828_HW11_xv6 log](https://link.zhihu.com/?target=https%3A//blog.csdn.net/Small_Pond/article/details/95210975)

JOS是828课程的主要实验部分，以下是我实验过程中记下的笔记，包含我的实现思路以及代码。 不过有些重复的细节，我就没有记录，可以参考我的完整实现代码。[Github_SmallPond/MIT6.828_OS](https://link.zhihu.com/?target=https%3A//github.com/SmallPond/MIT6.828_OS)
- Lab1 启动PC
- [LAB_1\_Part1_PC Bootstrap](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/3/)
- [LAB_1\_Part2_The Boot Loader](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/3/)
- [LAB1_Part3_The Kernel](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/4/)
- Lab2 内存管理
- [LAB2_Part1_Physical Page Management](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/5/)
- [LAB2_Part2_Virtual Memory](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/6/)
- [LAB2_Part3_Kernel Address Space(内核地址空间)](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/7/)
- Lab3 用户级环境（用户进程）
- [LAB3_User-Level Environments_PartA_User Environments and Exception Handling](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/8/)
- [LAB3_User-Level Environments_PartB Page Faults, Breakpoints Exceptions, and System Calls](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/9/)
- Lab4 抢占式多任务
- [LAB4_Preemptive Multitasking_PartA Multiprocessor Support and Cooperative Multitasking](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/10/)
- [LAB4_Preemptive Multitasking_PartB Copy-on-Write Fork](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/11/)
- [LAB4_Preemptive Multitasking_PartC Preemptive Multitasking and IPC](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/12/)
- Lab5 文件系统, Spawn and Shell
- [Lab5_File system, Spawn and Shell](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/13/)
- Lab6 网卡驱动
- [Lab6_Network Driver](https://link.zhihu.com/?target=https%3A//www.dingmos.com/index.php/archives/14/)

4\. 参考文献
- [MIT 6.828 JOS 操作系统学习笔记/fatsheep9146](https://link.zhihu.com/?target=https%3A//www.cnblogs.com/fatsheep9146/category/769143.html)，刚入门时参考，包括环境搭建。博文写得十分详细，可惜貌似只写到了 Lab2。
- [clpsz/mit-jos-2014](https://link.zhihu.com/?target=https%3A//github.com/clpsz/mit-jos-2014)，此大神放出了自己到 Lab4 的代码，其文档提及了一些细节，很有帮助。
- [Unknown Unknown](https://link.zhihu.com/?target=https%3A//buweilv.github.io/categories/OS/)，过程较详细（相当于对官方文档做了一遍翻译），英语不好可以参考这边，但我还是建议以官方文档为主，毕竟英语还是要学好呀。这位大神做到了LAB5，但不包括HW。
- [bysui的博客](https://link.zhihu.com/?target=https%3A//blog.csdn.net/bysui/article/category/6232831), 这位大神完成了全部的实验，但是我在后面才发现这么好的资源！

*来自 \<<https://zhuanlan.zhihu.com/p/74028717>\>*

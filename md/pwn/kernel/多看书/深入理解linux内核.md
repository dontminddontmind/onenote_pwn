---
title: 深入理解linux内核
updated: 2022-10-13T20:05:56.0000000+08:00
created: 2022-10-13T16:33:35.0000000+08:00
---

# 2 内存寻址
linux的分段

linux的GDT

在单处理器系统中只有一个GDT，而在多处理器系统中，系统中的每个CPU都有一个GDT。所有gdt都存储在cpu_gdt_表数组中，而gdt的地址和大小(在初始化gdtr寄存器时使用)存储在cpu_gdt_descr数组中。如果您查看源代码索引，可以看到这些符号定义在文件arch/i386/kernel/head.S中。

本书中的每个宏、函数和其他符号都列在源代码索引中，因此您可以快速地在源代码中找到它们。

gtd的布局示意图如图2-6所示。每个GDT包括18个段描述符和14个空的、未使用的或保留的条目。有意插入未使用的条目，以便通常一起访问的段描述符被保存在硬件缓存的同一32字节行中(参见本章后面的“硬件缓存”一节)。


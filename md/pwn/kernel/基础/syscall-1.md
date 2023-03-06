---
title: syscall
updated: 2022-08-27T17:56:59.0000000+08:00
created: 2022-07-31T22:13:46.0000000+08:00
---

strace追钟syscall
radare2 -d ./file \#调试

## SYSCALL—Fast System Call
[Intel® 64 and IA-32 Architectures Software Developer's Manual (jaist.ac.jp)](http://www.jaist.ac.jp/iscenter-new/mpc/altix/altixdata/opt/intel/vtune/doc/IA_32_Instructions_2B.pdf) p362

SYSCALL saves the RIP of the instruction following SYSCALL to RCX and loads a new RIP from the IA32_LSTAR (64-bit mode).
从IA32_LSTAR （一种MSR模型特定寄存器）加载RIP

## WRMSR ——写入MSR寄存器
在booting时使用该指令，需要权限ring0

## syscall调用过程（write为例）
cpu启动时设置好IA32_LSTAR；进入用户态；用户调用write；返回地址放入rcx中

![image1](../../../resources/image1-39.png)

syscall里比较系统调用号eax，跳转到write函数

![image2](../../../resources/image2-18.png)

read和write会用到下面两个函数，将任意内存拷贝到用户空间

![image3](../../../resources/image3-9.png)

copy_to_user的代码

![image4](../../../resources/image4-7.png)

switch不同的size选择不同的方法

![image5](../../../resources/image5-6.png)

![image6](../../../resources/image6-5.png)

美化一下

![image7](../../../resources/image7-2.png)

1：把addr mov到 x ，%2指第2个参数(\_\_m(addr))

ASM_STAC和ASM_CLAC设置和清理ac寄存器

section fixup 和extable 是硬件异常处理（搜搜exception tables的文档

这里不会将虚拟地址转成物理地址啥的，

而是1执行时会发生访问虚拟地址的中断错误，然后MMU执行剩下的东西

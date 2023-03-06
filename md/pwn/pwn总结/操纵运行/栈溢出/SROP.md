---
title: SROP
updated: 2022-05-25T15:19:01.0000000+08:00
created: 2022-04-05T16:51:54.0000000+08:00
---

[SROP 小记 « 平凡路上 (ray-cp.github.io)](https://ray-cp.github.io/archivers/srop-analysis)
## 条件
可以通过栈溢出来控制栈的内容

需要知道相应的地址

"/bin/sh"

Signal Frame

syscall

sigreturn

需要有够大的空间来塞下整个 sigal frame
# 原理
![image1](../../../../resources/image1-9.png)

图中的软中断会将进程的上下文信息保存到栈中。srop就是篡改这个信息。

可以不用任何gadget实现rop！
## Signal Frame
![image2](../../../../resources/image2-5.png)

## ucontext_t结构体定义
## sigcontext结构体（x86）
## sigcontext结构体定义（x64）
# 利用
rt_sigreturn 系统调用号 32位：173（0xad) 64位：15（0xf）
## get_shell
或者rip指向system、rdi指向binsh也行

![image3](../../../../resources/image3-3.png)
## rop链（控制栈指针）
![image4](../../../../resources/image4-2.png)
# 实现（pwntools）
## srop+mprotect+shellcode：构造srop链，用mprotect函数将栈改为可执行，在栈中写入shellcode并执行
[RCTF2019 pwn syscall_interface writeup (eonew.cn)](http://blog.eonew.cn/2019-05-30.RCTF2019%20pwn%20syscall_interface%20writeup.html)

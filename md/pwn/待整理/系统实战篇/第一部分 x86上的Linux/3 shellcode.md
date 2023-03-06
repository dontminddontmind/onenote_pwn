---
title: 3 shellcode
updated: 2021-10-22T22:12:19.0000000+08:00
created: 2021-06-09T17:03:08.0000000+08:00
---

# 系统调用
系统调用的执行方式分为调用libc包装库和软中断两种

例子 exit(0) 的汇编

例子 exit()的shellcode

系统调用追踪器（strace）
# 删除空值
shellcode里有'\0'，字符串会中止

方法一 使用其他指令替代，（如让mov 0,%eax 变成 xor %eax,%eax ）例子
# 例子 派生shell的shellcode
步骤

一 通过创建新进程派生shell

![image1](../../../../resources/image1-49.png)

![image2](../../../../resources/image2-26.png)

二 反汇编

三 删除空值

分析execve

分析main

剩下自己来

四 使用相对地址

![image3](../../../../resources/image3-15.png)

![image4](../../../../resources/image4-12.png)

![image5](../../../../resources/image5-9.png)

五反汇编得到

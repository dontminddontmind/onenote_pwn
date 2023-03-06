---
title: alarm
updated: 2022-04-18T21:45:18.0000000+08:00
created: 2021-10-22T22:49:03.0000000+08:00
---

signal(14, (\_\_sighandler_t)timeout_func);
alarm(0x3Cu);

[(45条消息) alarm(0)函数的作用_dongzhongshu的博客-CSDN博客_alarm(0)](https://blog.csdn.net/dongzhongshu/article/details/6270261)
当在调用alarm()前已经设置了一个闹钟，那么我们可以调用alarm(0)来取消此闹钟，并返回剩余时间。

# 说明
# 绕过
## 调试绕过
可以直接绕过这个计时器来动态分析：  
call sub_5662B8B5改为nop  
或者：在call地址后的首句push ebp改为retn  
或者：类似方法去除程序对alarm/signal的调用  
或者：直接改变alarm的参数（加长时间）  
或者：调试到alarm时set新的ip跳过call alarm

*来自 \<<https://bbs.pediy.com/thread-228226.htm>\>*

## 运行绕过？


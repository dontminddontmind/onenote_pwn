---
title: ptrace
updated: 2021-11-01T14:15:02.0000000+08:00
created: 2021-11-01T14:14:19.0000000+08:00
---

ptrace是一个系统调用，tracer进程可以使用ptrace监控和修改tracee进程的运行状态，如内存、寄存器的值等。
long ptrace(enum \_\_ptrace_request request, pid_t pid,void \*addr, void \*data);
The ptrace() system call provides a means by which one process (the “tracer”) may observe and control the execution of another process (the “tracee”), and examine and change the tracee’s memory and registers.
使用ptrace可以让某一进程处于受控状态，所以可以用作实现沙箱，如我们可以利用ptrace来监控tracee使用哪些系统调用，并组织tracee使用某些危险的系统调用等。

*来自 \<<https://atum.li/2017/04/25/linuxsandbox/#linux%E4%B8%AD%E7%9A%84%E6%B2%99%E7%AE%B1%E6%8A%80%E6%9C%AF>\>*


---
title: 创建进程 fork clone popen execve
updated: 2022-08-27T13:19:21.0000000+08:00
created: 2021-11-03T19:55:15.0000000+08:00
---

# fork
它不需要参数并返回一个整数值

**负值**：创建子进程失败。

**零**：返回到新创建的子进程。

**正值**：返回父进程或调用者。该值包含新创建的子进程的进程ID\[1\]。

*来自 \<<https://baike.baidu.com/item/fork/7143171>\>*

# clone
## clone系统调用 
## clone函数
## flag
## 和fork的区别

# popen
然后利用popen函数去执行命令，

pp = popen(buf, "w");

if (pp == NULL)

exit(0);

pclose(pp);

popen原理如下：

The popen() function opens a process by creating a pipe, forking, and invoking the shell. Since a pipe is by definition unidirectional, the typeargument may specify only reading or writing, not both; the resulting stream is correspondingly read-only or write-only.

The command argument is a pointer to a null-terminated string containing a shell command line. This command is passed to /bin/sh using the -c flag; interpretation, if any, is performed by the shell.

可以找到popen的源码：

\_IO_execl("/bin/sh","sh","-c",command,(char\*)0);

可见popen会先fork一个进程，然后执行\`/bin/sh -c “command”

一共生成两个进程！

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2019/10/15/sandbox/>\>*
**
# ptree查看进程关系

➜ \~ pstree -p 35612  
test(35612)───test(35613)───sh(35614)───sleep(35615)

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2019/10/15/sandbox/>\>*

# 进程间关系
不过注意在修改题目代码的时候一样要注意不要让子进程或者父进程退出。概念上，父进程退出子进程还没退出时，子进程会变成孤儿进程。实际上父进程一旦退出，终端就立刻变成可以输入的状态，子进程的打印数据就可能会打印到终端输入的地方，看起来很奇怪，这里其实涉及到tty的概念，下次再说。然后在概念上，父进程还没退出，子进程退出，子进程会变成僵尸进程，实际上就无法看到子进程的一些信息了，比如fd等等，并且会在ps命令的结果里用方括号括起来。所以在研究进程线程间关系时要控制好进程与线程的存活，或者使用gdb进程调试。

没懂
*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2019/10/15/sandbox/>\>*


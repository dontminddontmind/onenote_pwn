---
title: 'chroot '
updated: 2021-11-05T19:05:16.0000000+08:00
created: 2021-11-01T14:13:36.0000000+08:00
---

# 
# 概念 chroot jail
通常来说，提到chroot一般有两个含义，chroot(1)是/usr/bin/chroot, chroot(2)是glibc中的一个函数。
chroot(1)
chroot - run command or interactive shell with special root directory
chroot \[OPTION\] NEWROOT \[COMMAND \[ARG\]…\]
chroot(2)
chroot - change root directory
int chroot(const char \*path);
chroot的主要功能就是改变根目录，如运行chroot “/home/atum/newroot/” 会启动一个新的shell，且目录”/home/atum/newroot/”成为该shell下的新的根目录”/”。
chroot沙箱可以将进程对文件的访问限制在一个指定的目录中，但是由于chroot不是一个安全的feature，所以该沙箱可能会被逃逸出来。
[chroot 命令小记](https://juejin.im/post/5ad6118651882555894a5314)

# 逃逸
逃逸叫 chroot jailbreak，或者chroot breakout，可以自行google搜索相关内容
找到一些chroot jailbreak思路如下：
- [CTF中的sandbox](https://darkwing.moe/2019/08/01/CTF%E4%B8%AD%E7%9A%84sandbox/)
- [Chw00t: How to break out from various chroot solutions](https://deepsec.net/docs/Slides/2015/Chw00t_How_To_Break%20Out_from_Various_Chroot_Solutions_-_Bucsay_Balazs.pdf)
- [Prison Break (chroot)](https://warsang.ovh/prison-break-chroot/)
- [脱离chroot的枷锁](http://maskray.me/blog/2011-08-16-break-out-of-chroot)
学长整理的Chroot Breakout
1.  内核模块/攻击内核
2.  不具备root权限：通过ptrace到一个chroot以外的进程
3.  具备root权限：核心是CWD在ROOT以外，即可摆脱chroot
classic攻击:  
mkdir(d); chroot(d); cd ../../../; chroot(.)
通过fd: mkdir(d); n=open(.); chroot(d); chdir("/"); fchdir(n); cd ../../../../; chroot(.)
mkdir(d); chroot(d); chdir("/"); mkdir(dd); chroot(dd); cd ../../../../../../; chroot(.)
UDS(Unix Domain Socket)可以在父子进程建立socket，并且可以传输fd。于是父进程打开一个fd，子进程mkdir d; chroot d;接收父进程发来的fd，fchdir(fd); cd ../../../../../../../; chroot(.)造成breakout。
如果有足够权限，挂载/proc文件系统。  
mount("proc", slashdir, 0x100, "proc", NULL, NULL, optbuf, 0x400)，不需要proc绝对路径  
cd /proc/1/root，chroot(.)

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2019/10/15/sandbox/>\>*
刚才已经知道，并且通过调试确认子进程是可以用3，4，5三个文件描述符的
那如何利用呢？在室友的提示下，知道了一个openat函数，看名字也是知道大概是在某个可以指定的目录下打开吧，在man手册中查看这个函数：
int openat(int dirfd,const char \* pathname,int flags);
看函数原型就知道了，第一个参数是一个目录的文件描述符，所以非常简单的想到构造如下payload，即可绕过chroot的限制获得flag：
openat(3,"../../../../../flag",0)

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2019/10/15/sandbox/>\>*

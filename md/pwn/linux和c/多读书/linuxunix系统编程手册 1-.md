---
title: linux/unix系统编程手册 1-
updated: 2022-12-10T20:07:27.0000000+08:00
created: 2022-10-06T16:27:37.0000000+08:00
---

[hsf1002/linux-note: 《Linux/Unix系统编程手册》笔记 (github.com)](https://github.com/hsf1002/linux-note)
# 基础
# 4 通用文件I/O模型
## open
## open系统调用flags值
## open函数的错误
# 5 深入探究文件I/O
fcntl

F_DUPFD

F_DUPFD_CLOEXEC

因为无法通过 open() 来获取管道和套接字的文件描述符，所以要启用非阻塞标志，就必须使用 5.3 节所述 fcntl()的 F_SETFL 命令

文件描述符和打开文件之间的关系

复制文件描述符

close-on-exec标志

在文件特定偏移量处的 I/O：pread()和 pwrite()

分散输入和集中输出（Scatter-Gather I/O）：readv() 和 writev() 、preadv()和 pwritev()

截断文件：truncate()和 ftruncate()系统调用

大文件I/O：LFS

/dev/fd目录

创建临时文件：mkstemp()和tmpfile() unlink()
# 6 进程
环境变量

执行非局部跳转：setjmp()和longjmp()
# 7 内存分配
在堆上分配内存

调整program break：brk()和sbrk()

在堆上分配内存：malloc()和 free()

malloc调试的工具和库

控制和监测malloc函数包

calloc()和realloc()

分配对齐的内存：memalign()和 posix_memalign()

在栈帧上分配内存：alloca()
# 8 用户和组
密码文件：/etc/passwd

shadow 密码文件：/etc/shadow

组文件：/etc/group

获取用户和组的信息

从密码文件获取记录：getpwnam()和getpwuid()

从组文件获取记录：getgrnam()和 getgrgid()

程序示例

扫描密码文件和组文件中的所有记录：setpwent()、getpwent()和 endpwent()

从 shadow 密码文件中获取记录：getspnam()和 getspent()

密码加密和用户认证
# 9 进程凭证
# 10 时间
# 11 系统限制和选项
# 12 系统和进程信息
/proc文件系统 可以用man proc查看

/proc/PID目录

/proc目录下的系统信息

访问/proc文件

系统标识：uname()
# 13 文件I/O缓冲
文件 I/O 的内核缓冲：缓冲区高速缓存

stdio库的缓冲

设置一个 stdio 流的缓冲模式：setvbuf

刷新 stdio 缓冲区：fflush

控制文件I/O的内核缓冲（写入磁盘）

同步 I/O 数据完整性和同步 I/O 文件完整性（没看懂）

用于控制文件 I/O 内核缓冲的系统调用：fsync()，fdatasync()，sync()

open的flag（使所有写入同步）： O_SYNC（类似fsync）、O_DSYNC（fdatasync） 和 O_RSYNC（与前面两个flag一起使用，与读操作结合）

I/O缓冲小结

就 I/O 模式向内核提出建议

绕过缓冲区高速缓存：直接 I/O

混合使用库函数和系统调用进行文件 I/O
# 14 系统编程概念
设备专用文件（设备文件）mknod

磁盘和分区 ：fdisk -l列出分区、内存交换区

文件系统：创建mkfs

FUSE（用户空间文件系统）

ext2 文件系统

文件系统结构

i节点：ls -li命令可看i号

虚拟文件系统（VFS）：兼容不同文件系统

日志文件系统

单根目录层级和挂载点：mount device directory（不带参数可看挂载的文件系统）

文件系统的挂载和卸载：

/proc/mounts、/etc/mtab 和/etc/fstab

挂载文件系统：mount()

卸载文件系统：umount()和 umount2()

高级挂载特性

在多个挂载点挂载文件系统

多次挂载同一挂载点

基于每次挂载的挂载标志

绑定挂载

递归绑定挂载

虚拟内存文件系统：tmpfs

获得与文件系统有关的信息：statvfs()和fstatvfs()
# 15 文件属性


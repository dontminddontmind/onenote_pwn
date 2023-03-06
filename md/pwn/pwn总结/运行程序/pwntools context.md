---
title: pwntools context
updated: 2022-04-18T15:30:55.0000000+08:00
created: 2021-09-08T11:50:38.0000000+08:00
---

context.log_level = 'debug'

context
context(arch = 'amd64' , os = 'linux' , log_level = 'debug' )

context是pwntools用来设置环境的功能。在很多时候，由于二进制文件的情况不同，我们可能需要进行一些环境设置才能够正常运行exp，比如有一些需要进行汇编，但是32的汇编和64的汇编不同，如果不设置context会导致一些问题。

一般来说我们设置context只需要简单的一句话:

context(os='linux', arch='amd64', log_level='debug')

这句话的意思是：

1\. os设置系统为linux系统，在完成ctf题目的时候，大多数pwn题目的系统都是linux

2\. arch设置架构为amd64，可以简单的认为设置为64位的模式，对应的32位模式是’i386’

3\. log_level设置日志输出的等级为debug，这句话在调试的时候一般会设置，这样pwntools会将完整的io过程都打印下来，使得调试更加方便，可以避免在完成CTF题目时出现一些和IO相关的错误。

*来自 \<<https://www.cnblogs.com/liuyimin/p/7379985.html>\>*

可以使用context来指定cpu类型以及操作系统

\>\>\> context.arch = 'i386'

\>\>\> context.os = 'linux'

\>\>\> context.endian = 'little'

\>\>\> context.word_size = 32

注意：Any arguments/properties that can be set on context

\>\>\> asm("mov eax, SYS_select", arch = 'i386', os = 'freebsd')

'\xb8\]\x00\x00\x00'

\>\>\> asm("mov eax, SYS_select", arch = 'amd64', os = 'linux')

'\xb8\x17\x00\x00\x00'

\>\>\> asm("mov rax, SYS_select", arch = 'amd64', os = 'linux')

'H\xc7\xc0\x17\x00\x00\x00'

\>\>\> asm("mov r0, \#SYS_select", arch = 'arm', os = 'linux', bits=32)

'R\x00\xa0\xe3'

<https://blog.csdn.net/gyhgx/article/details/53439417>


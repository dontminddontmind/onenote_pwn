---
title: '&house_of_spirit'
updated: 2022-03-22T14:58:09.0000000+08:00
created: 2022-02-25T16:56:29.0000000+08:00
---

伪造块
条件
可以写入很大一块内容

可以控制传给free的参数为目标地址
实现
随便malloc一下sets up内存？

伪造fake_chunk

0，size …… 0，next_chunksize（2\*SIZE_SZ, av-\>system_mem）

free(fake_chunk+header)

malloc
利用
把伪块放在目标地（如栈），即可泄露信息，改写内容
例子
[\[原创\]2014 hack.lu oreo-Pwn-看雪论坛-安全社区\|安全招聘\|bbs.pediy.com](https://bbs.pediy.com/thread-247214.htm)

[fastbin House Of Spirit](https://ctf-wiki.github.io/ctf-wiki/pwn/linux/glibc-heap/fastbin_attack-zh/)

[tcache-house-of-spirit](https://ctf-wiki.github.io/ctf-wiki/pwn/linux/glibc-heap/tcache_attack-zh/#tcache-house-of-spirit)

*\<<https://xuanxuanblingbling.github.io/ctf/pwn/2020/03/13/tcache/>\>*


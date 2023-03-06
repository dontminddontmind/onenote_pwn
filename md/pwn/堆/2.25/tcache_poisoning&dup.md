---
title: '*tcache_poisoning&dup'
updated: 2022-07-16T15:10:20.0000000+08:00
created: 2022-03-24T19:17:27.0000000+08:00
---

篡改tcache的next指针，让目标地址进入tcache队列，从而malloc时可以读取
tcache不像fastbin，不用伪造块size！
[(54条消息) glibc2.31下的新double free手法/字节跳动pwn题gun题解_一只狗20000402的博客-CSDN博客](https://blog.csdn.net/chennbnbnb/article/details/109284780)
条件
tcache doublefree

实现 \>2.32
实现 2.31会遍历tcache检查doublefree
malloc 7次+a+b

free 7次 装满tcache ，剩下的进入bin

free(a) free(b) free(a)

malloc 7次 取空tcache

malloc(a) 此时伪造next指针=addr，tcache会把bin中剩下的块装入tcache中

malloc(b) malloc(b)

malloc(addr)
实现 2.27 啥也不检查
a = malloc(0x20);

free(a);

free(a);

malloc(0x20,addr)

malloc(0x20)

malloc(0x20,data)

[和媳妇一起学Pwn 之 Tcache Tear \| Clang裁缝店 (xuanxuanblingbling.github.io)](https://xuanxuanblingbling.github.io/ctf/pwn/2020/03/13/tcache/)


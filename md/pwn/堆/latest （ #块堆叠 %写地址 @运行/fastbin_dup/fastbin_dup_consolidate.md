---
title: fastbin_dup_consolidate
updated: 2022-03-14T15:18:49.0000000+08:00
created: 2022-02-25T17:05:43.0000000+08:00
---

条件
fastbin

largebin

double free

（可能要知道保存堆块的指针的地址）
实现
【TCACHE】？

malloc(a);malloc(b);

free(a)

malloc(large_chunk)

触发consolidate，fastbin清空全部进入unsortedbin再到smallbin

free(a)

利用1
malloc得到a，#fastbin

改写a \#可能跟unlink一样，要实现bk-\>fd=me

再malloc得到a \#smallbin

利用2 结合unlink （malloc有数量限制 ）
[\[原创\] 2016 HITCON CTF SleepyHolder-Pwn-看雪论坛-安全社区\|安全招聘\|bbs.pediy.com](https://bbs.pediy.com/thread-226197.htm)

[SleepyHolder - HITCON CTF 2016 - Exploiting Life (maheshhari.github.io)](https://maheshhari.github.io/blog/sleepyholder/)

malloc得到a \#fastbin

a中写入伪造的块头，伪造的fd和bk，伪造的prevsize

free(b) \# 因为doublefree、fastbin...此时b的prev_inuse是0！触发合并unlink！

之后的利用见unlink


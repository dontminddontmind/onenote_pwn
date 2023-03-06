---
title: 利用nextsize（latest）
updated: 2022-03-22T14:45:01.0000000+08:00
created: 2022-03-20T19:41:54.0000000+08:00
---

无需知道具体堆地址，利用largechunk的nextsize指针伪造fd和bk，过程和unlink同，不同的是无法改写指针，但是可以直接访问unsortedchunk
# 条件
无需知道具体地址！知道heap_base，便于对齐chunk

两个相邻的largebin

可以溢出至少一个NULL字节，（每次都会结尾补充\0）

malloc不会清空块内容

# 实现
堆布局：布置 0x0000\| 中p 小v \[p\] 小a \[p\] 大b \[p\] 四个largechunk（\[p\]防合并）

free到Largebin：free a、b、prev ;malloc超大块，从而nextsize链表按大小排序

在prev中伪造块：malloc(prev) 伪造size 和 nextchunk-\>prevsize

可以跳跃着写入内容

只能连续的写：那么需要把块拆分。以防覆盖掉fd和bk。

prev写入p64(0)+size，free(prev)。

malloc(0x20)。#切割的prev块，保存了size，fd，bk。

malloc(prevsize-0x40),写入prevsize。

绕过unlink 的检查：malloc(b) b-\>fd=fake; malloc(a) free a、v 进入unsorted 从而a-\>bk=v ; a-\>bk = fake

prev溢出改写victim的prev_inuse=0（注意size是被控制好低一字节刚好为0的）

free(victim);

后向合并，unlink会检查:

fake-\>size ==victim-\>prevsize

fake-\>fd-\>bk==fake&& fake-\>bk-\>fd ==fake

断链 fd-\>bk = bk;bk-\>fd = fd

a-\>bk = b; b-\>fd=a;

进入unsortedbin
# 利用
prev没有free，可以直接读写unsortedbin中的fake_chunk
# 

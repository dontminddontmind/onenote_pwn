---
title: 利用unsorted的fd和bk
updated: 2022-07-16T19:53:23.0000000+08:00
created: 2022-03-19T13:23:37.0000000+08:00
---

前面是利用largechunk的nextsize指针伪造fd和bk，这个是利用一个unsorted块的fd和bk，原理和前面相似
# 条件
无需知道具体地址！知道heap_base，便于对齐chunk

两个相邻的fastchunk也行

可以溢出至少一个NULL字节

# 实现
# 布置堆： \[unsorted\]\[各种各样的chunk，可以是free了的fast\] \[prev\] \[victim\]\[barrier\]
溢出改写unsorted的size？

溢出改写victim的prevsize，free(victim)，从而合并成一整个块

# 实例 : plaidctf 2015 plaiddb 

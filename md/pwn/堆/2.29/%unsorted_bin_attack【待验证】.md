---
title: '%unsorted_bin_attack【待验证】'
updated: 2022-03-22T18:30:34.0000000+08:00
created: 2022-03-22T16:28:28.0000000+08:00
---

篡改unsorted chunk的bk为目的地址，利用脱链，把unsortedbin地址写入目标中
条件
可以改写free块的bk指针

知道目的地址

2.29之后会检查：

unsortedbin的队尾-\>bk-\>fd=队尾，于是要伪造fd指针
实现
堆布局： victim barrier

free(victim)

篡改 victim-\>bk=var_addr-0x10

malloc(victim)

取出块: bin头-\>bk = victim-\>bk ; victim-\>bk-\>fd=bin头

var=bin头地址
利用
可以用于泄露unsortedbin地址，也可以用于伪造地址，或者 篡改global_max_fast为大数
例子
[UnsortedBin Attack · 语雀 (yuque.com)](https://www.yuque.com/hxfqg9/bin/tubv6q#1Ibdq)

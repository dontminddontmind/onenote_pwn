---
title: '&unsorted_bin_into_stack【待验证】'
updated: 2022-03-24T17:14:48.0000000+08:00
created: 2022-03-22T15:59:06.0000000+08:00
---

让unsorted_bin中插入伪造块
条件
非fast非tcache

知道伪造块地址

可以改写free块的size和bk指针

2.29之后会检查：

unsorted块的next的prevsize

unsortedbin的队尾-\>bk-\>fd=队尾，于是要伪造fd指针
实现2.23
堆布局： victim barrier

free(victim)

伪造块：fake = ( 0 ，size ，0，&fake)

fake插入unsortedbin：；

victim-\>size=和fake不同，为了第一个得到fake，否则先取出队尾也就是victim

victim-\>bk=fake

malloc即可得到fake
实现2.27
没看懂！！！

[WarGames (ret2.systems)](https://wargames.ret2.systems/level/how2heap_unsorted_bin_attack_2.27)

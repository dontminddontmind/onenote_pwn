---
title: '%large_bin_attack【待验证】'
updated: 2022-03-24T17:14:28.0000000+08:00
created: 2022-03-22T17:06:19.0000000+08:00
---

篡改largechunk的指针为目标地址，利用脱链，把largechunk地址写入目标中

条件
largebin（ malloc(\>=0x410)

知道一个目标地址

可以改写free的large块的bk_nextsize指针
实现
堆布局: p1 \[\] p2 \[\] （p1\>p2 ，p1p2的大小都要在一个bin中)

p1进入largebin：free(p1) malloc(p3\>p1\>p2)

p2进入unsorted：free(p2)

改写p1-\>bk_nextsize=var_addr-0x20

malloc(p3)

由于p3\>p1\>p2

p2从unsortedbin进入largebin：

比较最小的块（队尾bin-\>bk）:

// p2小于p1，所以直接入nextsize队尾

p2-\>fd_nextsize=bin-\>fd（队头）

p2-\>bk_nextsize=bin-\>fd-\>bk_nextsize（原nextsize队尾）【被篡改成var_addr-0x20】

bin-\>fd-\>bk_nextsize=p2-\>bk_nextsize-\>fd_nextsize=p2

【var=p2】

从大到小遍历nextsize（从队头bin-\>fd开始，不停fd_nextsize）:

如果p2等于p1：插入点变成p1-\>fd，不设置nextsize了

如果p2大于p1：2.29之后 对插入点p1加了检查：

p1-\>bk_nextsize-\>fd_nextsize==p1

p1-\>bk-\>fd==p1

会报错

遍历largebin：没有检查

最终var的值等于p2的地址
实现 \<2.29
没看懂！！！！

[WarGames (ret2.systems)](https://wargames.ret2.systems/level/how2heap_large_bin_attack_2.27)

例子
[largebin attack · 语雀 (yuque.com)](https://www.yuque.com/hxfqg9/bin/mdrz9g#Eqi6H)

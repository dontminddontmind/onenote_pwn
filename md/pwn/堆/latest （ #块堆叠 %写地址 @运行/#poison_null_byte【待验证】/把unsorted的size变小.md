---
title: 把unsorted的size变小
updated: 2022-07-16T20:07:40.0000000+08:00
created: 2022-03-17T17:55:50.0000000+08:00
---

溢出一个NULL，改变大小
1.  让一个unsorted块size变少（低位变0）
2.  malloc两个块，把缩小后的unsorted块割成两个。
3.  free第一个块和没缩小时unsorted块邻接的下一个。合并成一个大块，涵盖unsorted块分割出的第二个块。
4.  让指针中保存的地址减少，从而读写到不该读写的内容
# 条件
溢出一字节

非fastbin非tcache
# 实现
堆布局 a(0x100) b(0x200) c(0x100) barrier(0x100) //不包含头部大小

\*(size_t\*)(b+0x1f0) = 0x200 //b是不包含头部的

2.29以后会在取出unsortedbin时检查 next-\>prevsize==size。

我们等会会把b块free进unsortedbin里，然后又减小了b的size。

那么b的next也前移了，我们就要伪造next的prevsize

free(b)

a 溢出NULL字节，覆盖b的size的低位，让b的size减少

b1=malloc(0x100) b2=malloc(0x80)

分割缩小的b块给b1、b2 。刚好分完。

a溢出改写b1的size，让b1=b，因为2.29+检查presize==prev-\>size？

free(b1) free(c)

free(c)的时候，他会unlink原始的b块，并合并。

而此时b1在b的位置，还有fd和bk指向unsortedbin，成功绕过检查。

d = malloc(0x300)

d包含着b2
# 利用
d可以读写b2
# 实例: Asis CTF 2016 b00ks （空字节改变指针中的地址）


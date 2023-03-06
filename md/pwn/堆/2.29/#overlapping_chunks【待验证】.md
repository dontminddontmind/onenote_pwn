---
title: '#overlapping_chunks【待验证】'
updated: 2022-03-22T14:59:01.0000000+08:00
created: 2022-02-25T17:07:17.0000000+08:00
---

条件
可以溢出改写下一块的size
实现1 改写free的unsortedchunk的size (\<2.29)
条件：

2.29之前 malloc(unsorted) 不会检查next的prevsize和prev_inuse

堆布置：a b c barrier

free(b)

a溢出，改写b的size=b+c+1

d=malloc(b+c) 从而d和c堆叠
实现2 改写inuse中的chunk的size
条件：（虽然说\<2.29，但感觉都可以）

fast块：好像所有版本的fast都不会检查next的prevsize和prev_inuse？

unsorted块：

free时会检查下一块的prev_inuse，但是显然c让后面inuse了

free到unsorted时会自己写入next-\>prevsize

堆布局： a b c barrier

a溢出，改写b的size=b+c+1

free(b)

d=malloc(b+c)

例子
[Chunk Extend and Overlapping - CTF Wiki (ctf-wiki.org)](https://ctf-wiki.org/pwn/linux/user-mode/heap/ptmalloc2/chunk-extend-overlapping/#2015-hacklu-bookstore)

[Hack.lu 2015 bookstore writeup · Online tukan sanctuary](http://tukan.farm/2016/02/25/hacklu-2015-bookstore-writeup/)

[write-ups-2016/nuitduhack-quals-2016/exploit-me/night-deamonic-heap-400 at master · ctfs/write-ups-2016 (github.com)](https://github.com/ctfs/write-ups-2016/tree/master/nuitduhack-quals-2016/exploit-me/night-deamonic-heap-400)

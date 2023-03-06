---
title: mmap(latest) 【没看懂】
updated: 2022-03-24T14:14:35.0000000+08:00
created: 2022-03-22T14:36:48.0000000+08:00
---

[how2heap/mmap_overlapping_chunks.c at master · shellphish/how2heap (github.com)](https://github.com/shellphish/how2heap/blob/master/glibc_2.31/mmap_overlapping_chunks.c)
[how2heap_zh · 语雀 (yuque.com)](https://www.yuque.com/hxfqg9/bin/ape5up#jNP2I)
条件
mmap

可以改写mmap的chunk的size
实现
布置内存布局，先malloc一个小的，初始化堆，再连续malloc(0x100000)三次

int\* ptr1 = malloc(0x10);

printf("这种技术依然是 overlapping 但是针对的是比较大的 (通过 mmap 申请的)\n");

printf("分配大的 chunk 是比较特殊的，因为他们分配在单独的内存中，而不是普通的堆中\n");

printf("分配三个大小为 0x100000 的 chunk \n\n");

long long\* top_ptr = malloc(0x100000);

printf("第一个 mmap 块位于 Libc 上方： %p\n",top_ptr);

long long\* mmap_chunk_2 = malloc(0x100000);

printf("第二个 mmap 块位于 Libc 下方： %p\n", mmap_chunk_2);

long long\* mmap_chunk_3 = malloc(0x100000);

printf("第三个 mmap 块低于第二个 mmap 块: %p\n", mmap_chunk_3);

内存布局

running program

heap

....

3rd mmap chunk 0x7ffff780b010

2nd mmap chunk 0x7ffff790c010

LibC

....

ld

1st mmap chunk 0x7ffff7ed7010

改写3rd的size=sizeof2+sizeof3-IS_MAPPED(2) ==

0x202002？？？

mmap_chunk_3\[-1\] = (0xFFFFFFFFFD & mmap_chunk_3\[-1\]) + (0xFFFFFFFFFD & mmap_chunk_2\[-1\]) \| 2;

malloc(0x300000 )

之后看不懂了

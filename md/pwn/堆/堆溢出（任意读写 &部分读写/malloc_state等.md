---
title: malloc_state等
updated: 2022-03-24T18:43:16.0000000+08:00
created: 2022-03-24T18:15:52.0000000+08:00
---

malloc_state怎么初始化创建删除？
## static void \*sysmalloc (INTERNAL_SIZE_T, mstate)
当前堆的 top chunk 尺寸不足以满足申请分配的大小的时候，会调用sysmalloc，原来的 top chunk 会被释放并被置入 unsorted bin 中，通过这一点可以在没有 free 函数情况下获取到 unsorted bins。

*来自 \<<https://ctf-wiki.org/pwn/linux/user-mode/heap/ptmalloc2/house-of-orange/>\>*

sysmalloc 中对于堆有 mmap 和 brk 两种分配方式，

如果是brk，原有的 top chunk 会被置于 unsorted bin 中。

如果想让堆以 brk 的形式拓展，

首先，malloc 的尺寸不能大于mmp\_.mmap_threshold （ mmap 分配阈值，默认为 128K）

还有满足 top chunk size 的 check

我们总结一下伪造的 top chunk size 的要求
1.  伪造的 size 必须要对齐到内存页（一般内存页的大小是 4kb）
2.  size 要大于 MINSIZE(0x10)
3.  size 要小于之后申请的 chunk size + MINSIZE(0x10)
4.  size 的 prev inuse 位必须为 1

## static int systrim (size_t, mstate)
static void malloc_init_state (mstate av)

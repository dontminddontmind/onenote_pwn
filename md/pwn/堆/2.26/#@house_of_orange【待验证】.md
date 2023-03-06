---
title: '#@house_of_orange【待验证】'
updated: 2022-04-09T15:04:34.0000000+08:00
created: 2022-03-24T17:15:04.0000000+08:00
---

溢出篡改topchunk的size，当 top chunk 尺寸不足以满足申请分配的大小的时候，会调用sysmalloc，原来的 top chunk 会被释放并被置入 unsorted bin 中，通过这一点可以在没有 free 函数情况下获取到 unsorted bins。
条件
可以溢出篡改块size

可以读出topsize
实现
malloc一个块

溢出篡改topchunk的size
1.  伪造的 size 必须要对齐到内存页（一般内存页的大小是 4kb= 0x1000）（原topsize - 0x1000k）
2.  size 要大于 MINSIZE(0x10)
3.  size 要小于之后申请的 chunk size + MINSIZE(0x10)
4.  size 的 prev inuse 位必须为 1
再malloc

大小不能大于mmp\_.mmap_threshold （ mmap 分配阈值，默认为 128K）

不能小于topchunk的size

得到的块位于新扩展的堆区，原top进入unsortedbin

使用unsorted_bin_attack将unsortedbin的地址写入IO_list_all

溢出篡改原top块的bk指针为 io_list_all - 0x10

让原top块进入IO_list_all链，也就是把_chain指针指向原top

溢出串改原top块

在prevsize的位置写入'/bin/sh\x00'

在size的位置写入0x61

因为0x60属于smallbin\[4\]，与unsortedbin的偏移等于 \_chain 与 io_list_all 的偏移

在原top块中伪造好_IO_FILE结构，以绕过检查

// fp-\>\_mode = 0、\_IO_write_base 小于 \_IO_write_ptr

\_IO_FILE \*fp = (\_IO_FILE \*) top;

fp-\>\_mode = 0;

fp-\>\_IO_write_base = (char \*) 2;

fp-\>\_IO_write_ptr = (char \*) 3;

劫持vtable，将vtable\[3\]也就是 \_IO_OVERFLOW 改为 system

size_t \*jump_table = &top\[12\];

jump_table\[3\] = (size_t) &winner;

\*(size_t \*) ((size_t) fp + sizeof(\_IO_FILE)) = (size_t) jump_table;

malloc(10) 触发unsorted_bin_attack，同时原top入smallbin\[4\]

退出程序，触发_IO_OVERFLOW

例子
[House of Orange · 语雀 (yuque.com)](https://www.yuque.com/hxfqg9/bin/ct0mzz)

[Hitcon 2016 houseoforange](https://github.com/ctfs/write-ups-2016/tree/master/hitcon-ctf-2016/pwn/house-of-orange-500)

补丁没看懂！
[sourceware.org Git - glibc.git/blobdiff - stdlib/abort.c](https://sourceware.org/git/?p=glibc.git;a=blobdiff;f=stdlib/abort.c;h=117a507ff88d862445551f2c07abb6e45a716b75;hp=19882f3e3dc1ab830431506329c94dcf1d7cc252;hb=91e7cf982d0104f0e71770f5ae8e3faf352dea9f;hpb=0c25125780083cbba22ed627756548efe282d1a0)


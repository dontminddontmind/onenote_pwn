---
title: '*unsafe_unlink'
updated: 2022-03-22T14:55:40.0000000+08:00
created: 2022-02-25T14:58:29.0000000+08:00
---

利用unlink，伪造fd和bk为目标指针，从而改写目标指针
# 条件
两个 非fastbin 非tcache的 相邻的 chunk

chunk_overflow chunk_victim

知道保存chunk_overflow地址的指针的地址

void \*p = malloc(chunk_overflow)

知道 &p

chunk_overflow 可以溢出至少1字节，或者任何方式让PREV_INUSE=0

# 实现
在chunk_overflow里伪造fake_chunk

伪造 chunk_size ，躲避检查：size=next-\>prevsize【 2.23无】

伪造fd和bk，躲避检查：(P-\>fd-\>bk != P \|\| P-\>bk-\>fd != P) == False

chunk_overflow\[2\] /\* fake_chunk -\>fd \*/=

(uint64_t) &p-(sizeof(uint64_t)\*3);

chunk_overflow\[3\] /\* fake_chunk -\>bk \*/ =

(uint64_t) &p-(sizeof(uint64_t)\*2);

溢出覆盖chunk_victim的header

篡改prev_size

覆盖prev_inuse = 0

free(chunk_victim)

触发unlink(chunk_overflow) fd-\>bk = bk;bk-\>fd = fd;

约等于

p=(uint64_t) &p-(sizeof(uint64_t)\*2);

p= (uint64_t) &p-(sizeof(uint64_t)\*3);

合并两个chunk，进入unsortedbin队列
# 利用
因为改写了p，此时p指向 &p-3\*8 的位置

所以改写 p\[3\] ，就可以让p指向任何地方

再读写p\[0\]就是任意地址读写了


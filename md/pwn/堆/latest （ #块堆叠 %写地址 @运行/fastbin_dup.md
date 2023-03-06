---
title: '*fastbin_dup'
updated: 2022-03-22T14:55:34.0000000+08:00
created: 2022-02-25T17:05:06.0000000+08:00
---

让fastbin列表里混入想要改写的地址
条件
fastbin

double free
实现
【TCACHE】装满tcache，malloc7次

【TCACHE】如果用calloc可以避免从tcache取，之后就都不用麻烦了

malloc(a);malloc(b);malloc(c);

【TCACHE】free7次

free(a); free(b); free(a);

利用
【TCACHE】malloc7次，取完tcache

malloc得a 【TCACHE】注意！此时会把a装入tcache队列！之后的b也同理！

乘机改写a的fd为地址 p-headersize

（注意p前面的chunksize必须等于fastbin的size）（是chunksize！不是prevsize！）

可以在栈上伪造chunk

可以根据地址设置fastbin的size：

"0x0040????"为0x40；"0x007f..."为0x70即"0x7f 0x00 0x00 ..."

malloc得b

malloc又得a

再malloc得p

可以读写p了

【TCACHE】tcache的指针不是指向块头，而是块内容！但是咱们改写的fd指向的是快头！为了躲过fastbin的检查！所以！写入p的内容前部要多写0x10，也就是header的长度！
例子
[Write Some Paper (大小姐教我入门堆) \| Clang裁缝店 (xuanxuanblingbling.github.io)](https://xuanxuanblingbling.github.io/ctf/pwn/2020/02/02/paper/)

<https://www.gulshansingh.com/posts/9447-ctf-2015-search-engine-writeup/>

[(45条消息) 9447 CTF 2015: Search Engine分析(未完待续)\_Anciety的博客-CSDN博客](https://blog.csdn.net/qq_29343201/article/details/54747641)


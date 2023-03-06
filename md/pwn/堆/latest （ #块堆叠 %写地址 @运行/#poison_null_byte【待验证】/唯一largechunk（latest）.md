---
title: 唯一largechunk（latest）
updated: 2022-03-22T14:45:09.0000000+08:00
created: 2022-03-20T19:36:18.0000000+08:00
---

当largebin队列中只有一个大小时，nextsize指向自己。
不像上一个有另外两个largechunk可以利用，这种情况要利用tcache或fastbin或smallbin，绕过unlink
# 条件
同上
# 实现
堆布局：0x0000\| a(0xff0) barrier(0x10)

让a进入largebin：free(a) malloc(0x2000)

堆布局：a( fake(0x20) fd(0x20) ....... overflow(0x20) beflow ) barrier ...

伪造fake (0,size,&(fd-\>fd)-0x18)

分配一堆块

fd-\>bk=fake：因为前面已经让fd-\>bk位于fd块的fd指针处，让fd进入fastbin，malloc(fd)让fd指向自己

bk-\>fd=fake：fake中bk指向a，我们要让fake进入fastbin，再malloc(fake)让fd指向自己。

占满tcache，之后的块才能进入fastbin

取出tcache，然后才能取出目标快

溢出overflow改写prevsize

free(beflow)

# 实例 : Balsn_CTF_2019-PlainText
[Balsn CTF 2019 pwn PlainText - glibc-2.29 off by one pypass (eonew.cn)](http://blog.eonew.cn/2019-10-08.Balsn%20CTF%202019%20pwn%20PlainText%20-%20glibc-2.29%20off%20by%20one%20pypass.html)

[堆中的 Off-By-One - CTF Wiki (ctf-wiki.org)](https://ctf-wiki.org/pwn/linux/user-mode/heap/ptmalloc2/off-by-one/#3-balsn_ctf_2019-plaintext)


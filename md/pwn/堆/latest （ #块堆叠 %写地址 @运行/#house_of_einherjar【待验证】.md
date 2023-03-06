---
title: '#house_of_einherjar【待验证】'
updated: 2022-03-24T20:49:14.0000000+08:00
created: 2022-03-22T19:58:19.0000000+08:00
---

和unlink差不多，不同的是伪造fakechunk的fd和bk都指向自己
条件
知道堆地址

可以溢出改变prev_inuse
实现 \>2.31 2.32中tcache新增了防御措施，tcache_attack中的目标地址低4位需要等于0
确定对齐了的目标地址

intptr_t stack_var\[0x10\];

intptr_t \*target = NULL;

// choose a properly aligned target address

for(int i=0; i\<0x10; i++) {

if(((long)&stack_var\[i\] & 0xf) == 0) {

target = &stack_var\[i\];

break;

}

}

改写tcache的next指针

d\[0x30 / 8\] = (long)target ^ ((long)&d\[0x30/8\] \>\> 12);

2.32之前是

d\[0x30 / 8\] = (long) stack_var;

这样麻烦是为了绕过

\#define PROTECT_PTR(pos, ptr) \\

((\_\_typeof (ptr)) ((((size_t) pos) \>\> 12) ^ ((size_t) ptr)))

\#define REVEAL_PTR(ptr) PROTECT_PTR (&ptr, ptr)

实现 2.31 只能实现块堆叠（？），想要读写任意地址还要再结合tcache_attack
堆布局：a b c（非fast）barrier

在a里伪造fake_chunk：( 0, size, fake, fake)

b溢出改写c的prev_size和prev_inuse：

prev_size = c_addr - &fake

prev_inuse=0

fake-\>size=c-\>prev_size

TCACHE：malloc7次又free7次 与c同样大小的块，装满tcache

free(c)

d=malloc 得到a+b+c

malloc(pad=b) free(pad)

这一步是为了把tcache的count数量加一

把b装入tcache队列：free(b) b会指向pad

在d里串改b的next指针为任意地址

malloc(b)

malloc得到任意地址

实现 \<2.29 直接把fake_chunk造在栈上
堆布局：a b barrier

在栈上布置fake_chunk：( prevsize=size, size, &fake, &fake, &fake, &fake )

这个prevsize=size感觉没啥用

a溢出改写b的prev_size和prev_inuse：

prev_size = b_addr - &fake

如果等于负数怎么办？？？

prev_inuse=0

fake_chunk-\>size = b-\>prev_size

free(b)

unlink时检查：

size==next-\>prevsize 通过

p-\>fd-\>bk==p&&p-\>bk-\>fd==p 通过

断链：fd-\>bk = bk;bk-\>fd = fd;

fd和bk都等于fake，于是保持原样。

d = malloc(随便)=fake

真的可以吗？遍历unsortedbin时会检查块大小是否合理哦！
例子
[House Of Einherjar · 语雀 (yuque.com)](https://www.yuque.com/hxfqg9/bin/hwrtn9#HMNXm)


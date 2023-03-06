---
title: '*house_of_force【待验证】'
updated: 2022-03-24T14:14:43.0000000+08:00
created: 2022-03-22T14:43:06.0000000+08:00
---

[House Of Force · 语雀 (yuque.com)](https://www.yuque.com/hxfqg9/bin/gwcg1c)
让topchunk无限大，这样就能malloc到内存中的任意地址
条件
知道目标地址，top块地址

可以溢出改写topchunk的size

2.29之后会检查topchunk的size不能过大
实现
溢出改写topchunk的size=-1

malloc（目标地址-top地址-两个header的size）

如果得到负数会怎样？？？

再次 malloc 读写目标地址

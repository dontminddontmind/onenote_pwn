---
title: /bin/sh 字符串
updated: 2022-05-08T12:51:47.0000000+08:00
created: 2022-03-04T11:18:36.0000000+08:00
---

不一定/bin/sh 用sh 或\$0 都行
可以用分隔符 'not_useful' +';sh'
对/bin/sh找交叉引用可以找到system函数

找libc里的/bin/sh 字符串
ida

gdb

libcSearcher
bin_sh_addr = libcbase + obj.dump("str_bin_sh")
strings
strings -a -t x libc.so.6 \| grep "/bin/sh" \#返回的是16进制
ROPgadget
ROPgadget --binary libc.so --string '/bin/sh'

process search

from pwn import \*

p = process("./mypwn")

binsh = p.search("/bin/sh").next()

\# python3

next(p.search(b"/bin/sh"))

elf search

from pwn import \*

libc = ELF("./libc.so")

binsh = libc.search("/bin/sh").next()

\# 这个地址不是真实地址，使用时还需要加上偏移

\# 即一般情况下进行下面的处理后，才能正常使用

binsh_addr = binsh + libc_base# 泄露的libc基地址

[(26条消息) pwn题查找字符串方法记录_SkYe's Blog-CSDN博客](https://blog.csdn.net/weixin_43921239/article/details/105318835)
写入/bin/sh
记得加上\0结尾哦！

往bss段写入/bin/sh

知道栈地址，写入栈

往堆块中写入

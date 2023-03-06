---
title: 泄露libc地址
updated: 2022-07-16T14:53:55.0000000+08:00
created: 2022-03-04T13:25:03.0000000+08:00
---

# 泄露函数地址
## GOT（栈溢出）
puts(got) \| print(got)

write(1,got,size)

裁剪收到的比特流，转换成地址

addr = u64( p.recv()\[:6\] .ljust(8,'\x00') )

**注意：不要选择有 wapper 的函数，这样会使得函数的基地址计算不正确。**

*来自 \<<https://ctf-wiki.org/pwn/linux/user-mode/summary/get-address/>\>*
## [ret2dl-resolve](onenote:#ret2dl_resolve&section-id={07362C18-CD90-49F6-AFC3-41634DDD6CB9}&page-id={DD1F2488-2FEA-404A-9A67-5FC3DB402B86}&end&base-path=https://d.docs.live.net/8d1582069e7b0b95/文档/pwn/pwn总结.one)
## /proc/self/maps
我们可以考虑通过读取程序的/proc/self/maps来获取与程序相关的基地址。
## unsortedbin泄露libc
unsortedbin 偏移(十进制）

2.23 (main_arena+88)

2.31 \<main_arena+96\>

块free后进入unsortedbin

[和媳妇一起学Pwn 之 hacknote \| Clang裁缝店 (xuanxuanblingbling.github.io)](https://xuanxuanblingbling.github.io/ctf/pwn/2020/02/03/hacknote/)

tcache 块free后进入unsortedbin
1.  每个tcache链上默认最多包含7个块，再次free这个大小的堆块将会进入其他bin中，例如[tcache_attack/libc-leak](https://ctf-wiki.github.io/ctf-wiki/pwn/linux/glibc-heap/tcache_attack-zh/#libc-leak)
2.  默认情况下，tcache中的单链表个数是64个，64位下可容纳的最大内存块大小是1032（0x408），故只要申请一个size大于0x408的堆块，然后free即可

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2020/03/13/tcache/>\>*
malloc后泄露没被清空的unsortedbin的fd

如果没法读free的块！在malloc时unlink会把fd和bk置0！

可以在free的时候把unsortedbin合并到top块

就不会清空fd指针

再malloc切割top块即可泄露原来的fd指针
## 将函数指针（hook，got）改为puts_plt泄露got地址
free(a) : 将free_got改为puts_plt，将a=puts_got
## mmap
当malloc的大小超过限制时（\>=0x21000)，就会用mmap，mmap分配的地址紧邻libc
# 组合技泄露libc
## doublefree+篡改free_got为puts
利用doublefree得到指向puts_got的堆块

编辑该堆块修改free_got=puts_got

free(puts_got) = puts(puts_got)

# 计算libc基址
搜索main_arena

pwn学习--LibcSearcher
*来自 \<<https://blog.csdn.net/qq_44108455/article/details/105458234>\>*
虽然LibcSearcher不能搜索main_arena，但是它减0x10就是\_\_malloc_hook

有libc文件
libc = ELF('libc.so.6')
libcbase = funcgotaddr - libc.sym\['func'\]
binsh_addr = next(libc.search('/bin/sh'))
libcSearcher

from LibcSearcher import \*

obj = LibcSearcher("gets",gets_real_addr)

libcbase = gets_real_addr – obj.dump("fgets")

system_addr = libcbase + obj.dump("system") \#system 偏移

bin_sh_addr = libcbase + obj.dump("str_bin_sh") \#/bin/sh 偏移

这是啥

DynELF

在线网站

[libc database search (blukat.me)](https://libc.blukat.me/) 低12位不变

<http://libcdb.com/>

看节区表手算偏移

readelf -S libc.so

*来自 \<<https://v1ckydxp.github.io/2019/05/01/pwnable-tw-dubblesort-writeup/>\>*
如果有完全一样的环境，也可以看vmmap手算

下载libc [Index of /ubuntu/pool/main/g/glibc](http://old-releases.ubuntu.com/ubuntu/pool/main/g/glibc/)

**一些用于泄露libc版本的工具**

*来自 \<<https://www.jianshu.com/p/8d2552b8e1a2>\>*


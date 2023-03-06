---
title: _IO_FILE
updated: 2022-04-23T13:03:09.0000000+08:00
created: 2022-03-25T13:46:06.0000000+08:00
---

# 基础
## fopen和open区别
| ****    | **文件描述符（低级IO）** | **文件流/文件指针（高级IO）**   |
|----------|--------------------------|---------------------------------|
| 头文件   |                         | stdio.h                         |
| 标准     | POSIX                    | ANSI C                          |
| 层次     | 系统调用                 | libc                            |
| 数据类型 | int                      | FILE \*                         |
| 函数     | open/close/read/write    | fopen/fclose/fread/fwrite/fseek |
## 
**\_IO_FILE**就是FILE结构体，\_IO的意思是其所在是libc的IO库中

**IO_FILE_plus** 比IO_FILE多了vtable（一个指针指向函数指针表）

**全局变量_IO_list_all** 链接了所有文件（IO_FILE_plus）的链表，有err\>out\>in

- [IO FILE之fopen详解](https://ray-cp.github.io/archivers/IO_FILE_fopen_analysis)
- [IO FILE之fread详解](https://ray-cp.github.io/archivers/IO_FILE_fread_analysis)
- [IO FILE之fwrite详解](https://ray-cp.github.io/archivers/IO_FILE_fwrite_analysis)
- [IO_FILE之fclose详解](https://ray-cp.github.io/archivers/IO_FILE_fclose_analysis)

## 利用
- [FILE Structure Description](https://ctf-wiki.github.io/ctf-wiki/pwn/linux/io_file/introduction-zh/)
- [\_IO_FILE利用思路总结](https://b0ldfrev.gitbook.io/note/pwn/iofile-li-yong-si-lu-zong-jie)
- [\_IO_FILE部分源码分析及利用](http://dittozzz.top/2019/04/24/IO-FILE%E9%83%A8%E5%88%86%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90%E5%8F%8A%E5%88%A9%E7%94%A8/)
- [IO file结构在pwn中的妙用](https://xz.aliyun.com/t/6567)
- [IO FILE 学习笔记](https://veritas501.space/2017/12/13/IO%20FILE%20%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/)
- [IO_FILE利用的一些总结 - 简书 (jianshu.com)](https://www.jianshu.com/p/a6354fa4dbdf)

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2020/04/03/file/>\>*
# 源代码
## \_IO_FILE
### 头文件定义 libio.h
### 运行时内容 大小：64位0xe0=224 32位0x98
## vtable
### 全局变量 \_IO_file_jumps
### 所有vtable
## \_IO_FILE \* \_IO_new_fopen(const char \*filename, const char \*mode)
## size_t \_IO_fread (void \*buf, size_t size, size_t count, FILE \*fp)
## size_t \_IO_fwrite (const void \*buf, size_t size, size_t count, FILE \*fp)
## int \_IO_new_fclose (FILE \*fp)
## printf/puts \_IO_new_file_xsputn和_IO_new_file_overflow
printf的调用栈

write

\_IO_new_file_write

new_do_write+51

\_\_GI\_\_IO_do_write

\_\_GI\_\_IO_file_xsputn

vfprintf

printf

main

\_\_libc_start_main

## scanf/gets 都用了_IO_new_file_underflow实现read
# pwntools filepointer
[pwnlib.filepointer — FILE\* structure exploitation — pwntools 4.7.0 documentation](https://docs.pwntools.com/en/stable/filepointer.html)

fileStr = FileStructure(null=0xdeadbeef)

\# \_lock = null = A pointer to NULL value in memory

fileStr.vtable = 0xcafebabe

payload = bytes(fileStr)

prinf(fileStr) \# 展示结构体

\#orange专用

payload = fileStr.orange(io_list_all=0xfacef00d, vtable=0xcafebabe)

payload = fileStr.struntil("\_IO_buf_end")

\# 直到 \_IO_buf_end （包括 \_IO_buf_end） 的string

update_var(8)

\#改变fileStr大小，8是64位，4是32位

\#还有read write不知道干嘛的

payload = fileStr.read(addr=0xcafebabe, size=100)

32位还会报错！ AttributeError("bits must be \> 0 (%r)" % bits)

[Filepointer fix \#2040 - Github Lab](https://githublab.com/repository/issues/Gallopsled/pwntools/2040)
# 2.23之前 劫持vtable
条件：可以改写io_file，或者可以伪造io_file。需要泄露目标执行地址。
## \_IO_flush_all_lockp
## [house_of_orange](onenote:堆.one#house_of_orange【待验证】&section-id={8D36F45D-B980-4938-8C48-86B1AB424189}&page-id={F41BDDEA-EF53-4B47-93D3-6D7440F78A08}&end&base-path=https://d.docs.live.net/8d1582069e7b0b95/文档/pwn)

# 2.24之后
## vtable_check
### 调用vtable函数= (IO_validate_vtable(fp+vtable_offset)-\>func)(fp,arg)
### [IO_validate_vtable](https://code.woboq.org/userspace/glibc/libio/libioP.h.html#IO_validate_vtable) (const struct [\_IO_jump_t](https://code.woboq.org/userspace/glibc/libio/libioP.h.html#_IO_jump_t) \*vtable) 判断是否在vtable数组中
### [\_IO_vtable_check](https://code.woboq.org/userspace/glibc/libio/vtables.c.html#_IO_vtable_check) (void) 判断是否为外部的合法vtable（重构或是动态链接库中的vtable）
## 绕过vtable_check
### 绕过_IO_vtable_check （vtable不在默认数组中）
### 【绕过IO_validate_vtable】
### 使用内部的vtable ：\_IO_str_jumps或_IO_wstr_jumps【2.28之后不行】
### 篡改缓冲区指针来进行任意内存读写
目标写的地址是write_start，写结束地址为write_end；读的目标地址为read_start，读的结束地址为read_end

*来自 \<<https://ray-cp.github.io/archivers/IO_FILE_arbitrary_read_write>\>*

## 例题
\_IO_str_jumps [IO FILE 之vtable劫持以及绕过 « 平凡路上 (ray-cp.github.io)](https://ray-cp.github.io/archivers/IO_FILE_vtable_check_and_bypass)

hctf 2017的babyprintf

ASIS2018的fifty-dollars

### 
# 2.34
[第七届“湖湘杯” House \_OF \_Emma \| 设计思路与解析 - 安全客，安全资讯平台 (anquanke.com)](https://www.anquanke.com/post/id/260614)

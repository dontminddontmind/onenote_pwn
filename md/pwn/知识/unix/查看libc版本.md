---
title: 查看libc版本
updated: 2022-03-27T20:08:54.0000000+08:00
created: 2021-09-21T15:53:07.0000000+08:00
---

[(45条消息) 多个gcc/glibc版本的共存及指定gcc版本的编译_mo4776的博客-CSDN博客_gcc编译指定glibc版本](https://blog.csdn.net/mo4776/article/details/119837501)
查看glibc版本
ldd --version

ldd是隶属于glibc，它的版本就是glibc的版本

getconf GNU_LIBC_VERSION

pthread也是一个非常重要的库，它被包含在glibc中，可以通过

getconf GNU_LIBPTHREAD_VERSION查看它的版本，是与glibc的版本是一致的

strings libc.so \| grep "GLIBC"

查找glibc库的位置
通过ldd

linux 上几乎所有的程序都依赖于glibc，所以可以直接通过 ldd 某个程序 \| grep "libc.so"的方式查看

通过gcc

gcc -print-file-name=libc.so可以获得libc.so的位置，这也是该gcc依赖的libc.so的位置
查看glibc API的版本
- strings /lib64/libc.so.6 \| grep GLIBC

# ubuntu的libc版本
下面是可以查看 ubuntu版本的 glibc版本的地址：

<https://launchpad.net/glibc/+packages>

在上面找到后：
| ubuntu 16.04 | 2.23-0ubuntu11.3 |
|--------------|------------------|
| ubuntu 17.04 | glibc2.24        |
| ubuntu 17.10 | glibc2.26        |
| ubuntu 18.04 | 2.27-3ubuntu1.4  |
| ubuntu 20.04 | 2.31-0ubuntu9.2  |

然后就是拉去对应版本的docker，布置pwn环境了。然后可以直接使用 Dockerfile 来创建，可以参考 <https://www.lyyl.online/2020/08/06/docker-pwn-%E7%8E%AF%E5%A2%83%E6%90%AD%E5%BB%BA/>

这里面的 dockerfile 还是很全面，可以直接使用。

*来自 \<<https://a1ex.online/2020/09/24/Docker%E4%B8%8BPWN%E7%8E%AF%E5%A2%83%E6%90%AD%E5%BB%BA/>\>*

# diff对比
diff ./libc-18292bd12d37bfaf58e8dded9db7f1f5da1192cb.so /lib/x86_64-linux-gnu/libc-2.27.so

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2020/03/13/tcache/>\>*


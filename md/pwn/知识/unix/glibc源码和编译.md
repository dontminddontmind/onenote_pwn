---
title: glibc源码和编译
updated: 2022-04-12T17:26:48.0000000+08:00
created: 2021-08-24T21:13:55.0000000+08:00
---

# 下载源码
Checkout the latest glibc in development:

看看最新开发的 glibc:

git clone <https://sourceware.org/git/glibc.git>

cd glibc

git checkout master

Releases are available by source branch checkout (gitweb) and tarball via ftp.

发行版可以通过源代码分支签出(gitweb)和 tarball 通过 ftp 获得。

Checkout the latest glibc 2.34 stable release:

检查最新的 glibc 2.34 stable 版本:

git clone <https://sourceware.org/git/glibc.git>

cd glibc

git checkout release/2.34/master

Release tarballs are available via anonymous ftp at <http://ftp.gnu.org/gnu/glibc/> and its mirrors.

发行版 tarballs 可以通过匿名 ftp 在 [http://ftp.gnu.org/gnu/glibc/和它的镜像服务器上获得](http://ftp.gnu.org/gnu/glibc/和它的镜像服务器上获得)。

[The GNU C Library](https://www.gnu.org/software/libc/)

glibc源码下载地址

<http://ftp.gnu.org/pub/gnu/glibc/>

<http://www.gnu.org/software/libc/libc.html>

<http://mirrors.nju.edu.cn/gnu/libc/>

<http://ftp.ntu.edu.tw/gnu/glibc/>

<http://mirrors.syringanetworks.net/gnu/libc/>

<http://alpha.gnu.org/gnu/glibc/>

在线源码阅读

<https://code.woboq.org/userspace/glibc/>

<https://elixir.bootlin.com/glibc/glibc-2.31/source>

第二个链接也可以在线阅读Linux内核源码。

————————————————

版权声明：本文为CSDN博主「、moddemod」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。

原文链接：https://blog.csdn.net/weixin_43833642/article/details/104681190

[libc.pdf (gnu.org)](https://www.gnu.org/software/libc/manual/pdf/libc.pdf)

[Woboq Code Browser - Explore C++ code on the web](https://code.woboq.org/)

下载源码
# 编译
[1.5.8 glibc malloc - CTF-All-In-One (gitbook.io)](https://firmianay.gitbook.io/ctf-all-in-one/1_basic/1.5_reverse_basic/1.5.8_glibc_malloc)

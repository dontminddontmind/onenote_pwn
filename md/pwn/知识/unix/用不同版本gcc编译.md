---
title: 用不同版本gcc编译
updated: 2022-04-15T15:07:05.0000000+08:00
created: 2022-02-25T11:31:19.0000000+08:00
---

\# 编译32位
apt install gcc-multilib

gcc hello.c -m32

[(45条消息) 多个gcc/glibc版本的共存及指定gcc版本的编译_mo4776的博客-CSDN博客_gcc编译指定glibc版本](https://blog.csdn.net/mo4776/article/details/119837501)

# apt-get直接安装
sudo apt-get install gcc-4.4 gcc-4.4-multilib
# 自己编译

# 版本切换
\# 配置

sudo update-alternatives —install /usr/bin/gcc gcc /usr/bin/gcc-4.4 40

sudo update-alternatives —install /usr/bin/gcc gcc /usr/bin/gcc-5 50

\# 切换

sudo update-alternatives —config gcc

*来自 \<<https://www.anquanke.com/post/id/176492>\>*


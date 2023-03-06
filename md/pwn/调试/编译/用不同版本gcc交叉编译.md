---
title: 用不同版本gcc交叉编译
updated: 2023-02-21T16:25:06.0000000+08:00
created: 2022-05-14T15:17:38.0000000+08:00
---

# GCC安装
完整库列表：[【Pwn 笔记】跨平台架构的环境配置与调试 \| binLep's Blog](https://binlep.github.io/2020/03/20/%E3%80%90Pwn%20%E7%AC%94%E8%AE%B0%E3%80%91%E8%B7%A8%E5%B9%B3%E5%8F%B0%E6%9E%B6%E6%9E%84%E7%9A%84%E7%8E%AF%E5%A2%83%E9%85%8D%E7%BD%AE%E4%B8%8E%E8%B0%83%E8%AF%95/)

apt-cache search "gcc" \| grep -E "arm\|mips"

sudo apt install gcc-4.8 g++-4.8

sudo apt-get install gcc-mipsel-linux-gnu g++-mipsel-linux-gnu \\

gcc-mips-linux-gnu g++-mips-linux-gnu \\

gcc-mips64el-linux-gnuabi64 g++-mips64el-linux-gnuabi64 \\

gcc-mips64-linux-gnuabi64 g++-mips64-linux-gnuabi64 \\

gcc-arm-linux-gnueabi g++-arm-linux-gnueabi libc6-dbg-armel-cross \\

gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf libc6-dbg-armhf-cross \\

gcc-aarch64-linux-gnu g++-aarch64-linux-gnu libc6-dbg-arm64-cross \\

gcc-hppa-linux-gnu g++-hppa-linux-gnu libc6-dbg-hppa-cross \\

gcc-hppa64-linux-gnu \\

gcc-m68k-linux-gnu g++-m68k-linux-gnu libc6-dbg-m68k-cross \\

gcc-powerpc-linux-gnu g++-powerpc-linux-gnu libc6-dbg-powerpc-cross \\

gcc-powerpc64-linux-gnu g++-powerpc64-linux-gnu libc6-dbg-ppc64-cross \\

gcc-powerpc64le-linux-gnu g++-powerpc64le-linux-gnu libc6-dbg-ppc64el-cross \\

gcc-s390x-linux-gnu g++-s390x-linux-gnu libc6-dbg-s390x-cross \\

gcc-sh4-linux-gnu g++-sh4-linux-gnu libc6-dbg-sh4-cross \\

gcc-sparc64-linux-gnu g++-sparc64-linux-gnu libc6-dbg-sparc64-cross \\

gcc-alpha-linux-gnu g++-alpha-linux-gnu libc6.1-dbg-alpha-cross \\

gcc-x86-64-linux-gnux32 g++-x86-64-linux-gnux32 libc6-dbg-x32-cross \\

gcc-i686-linux-gnu gcc-i686-linux-gnu libc6-dbg-i386-cross \\

gcc-riscv64-linux-gnu g++-riscv64-linux-gnu libc6-dbg-riscv64-cross \\

binutils-ia64-linux-gnu \\

binutils-mipsisa32r6el-linux-gnu \\

binutils-mipsisa32r6-linux-gnu

这几个找不到

libc6-dbg-mips-cross libc6-dbg-mipsel-cross libc6-dbg-mips64el-cross libc6-dbg-mips64-cross

gcc-powerpc-linux-gnuspe g++-powerpc-linux-gnuspe libc6-dbg-powerpcspe-cross \\

GCC 的命名规则为：**arch \[-vendor\] \[-os\] \[-(gnu)eabi\]-gcc**

比如arm-linux-gnueabi-gcc，arm-none-eabi-gcc，aarch64-linux-gnu-gcc
- 带 \[\] 的是可选部分。
- arch： 芯片架构，比如 32 位的 Arm 架构对应的 arch 为 arm，64 位的 Arm 架构对应的 arch 为 aarch64。
- vendor ：工具链提供商，大部分工具链名字里面都没有包含这部分。
- os ：编译出来的可执行文件(目标文件)针对的操作系统，比如 Linux。

可以apt安装

这篇文章在linaro官网下载 <http://releases.linaro.org/components/toolchain/binaries/>

*来自 \<<https://segmentfault.com/a/1190000020955640>\>*

# 搜索已安装版本
ls /usr/bin/gcc\*
# 编译
### make参数
make ARCH=arm imx_v7_defconfig  
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

*来自 \<<https://segmentfault.com/a/1190000020955640>\>*
### 修改Makefile
CC = arm-linux-gcc  
CPP = arm-linux-gcc -E

*来自 \<<https://blog.csdn.net/zhangxuechao_/article/details/82821739>\>*


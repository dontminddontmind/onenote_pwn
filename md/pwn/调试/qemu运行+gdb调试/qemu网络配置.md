---
title: qemu网络配置
updated: 2022-06-10T11:12:24.0000000+08:00
created: 2022-04-16T16:22:56.0000000+08:00
---

[Documentation/Networking - QEMU](https://wiki.qemu.org/Documentation/Networking) 官网
[QEMU 网络配置一把梭 \| CataLpa's Home (wzt.ac.cn)](https://wzt.ac.cn/2021/05/28/QEMU-networking/) 写清楚了原因
[(48条消息) qemu虚拟机与外部网络的通信_li_Jiejun的博客-CSDN博客](https://blog.csdn.net/u014022631/article/details/53411557) 能用，也写得很清楚
## 编写网络配置文件教程
[网络配置文件，/etc/network/interfaces \|《笨办法学 Linux 中文版》\| Server 运维论坛 (learnku.com)](https://learnku.com/docs/linux-the-hard-way/ex25/6228)

[Linux 下使用 netplan 配置多网卡 - 宇宙よりも遠い場所 (kirainmoe.com)](https://kirainmoe.com/blog/post/configure-multi-nic-on-linux-using-netplan/)

# 默认网络配置，主机无法访问虚拟机？
# 网桥TAP 不写脚本
## 不写脚本简短版
[mips-pwn环境搭建 \| e3pem's Blog](https://e3pem.github.io/2019/08/23/mips-pwn/mips-pwn%E7%8E%AF%E5%A2%83%E6%90%AD%E5%BB%BA/)

创建网桥：

sudo brctl addbr br0

sudo ifconfig br0 192.168.122.1/24 up

创建tap接口，名字为tap0，并添加到网桥:

sudo tunctl -t tap0

sudo ifconfig tap0 192.168.122.11/24 up

sudo brctl addif br0 tap0

sudo qemu-system-mips -M malta \\

-kernel vmlinux-3.2.0-4-4kc-malta \\

-hda debian_wheezy_mips_standard.qcow2 \\

-append "root=/dev/sda1 console=tty0" \\

-netdev tap,id=tapnet,ifname=tap0,script=no -device rtl8139,netdev=tapnet \\

-nographic

或者

-net nic \\

-net tap,ifname=tap0,script=no,downscript=no

输入root/root进入虚拟机，设置ip：

ifconfig eth0 192.168.122.12 netmask 255.255.255.0 up

## 写入/etc/network/interfaces 在启动时自动配置
## ubuntu20不支持/etc/network/interfaces 用netplan
## 写/etc/qemu-ifup
mips系统网络的配置
# 


---
title: '启动脚本 /init | /etc/init.d/rcS '
updated: 2022-08-27T13:17:55.0000000+08:00
created: 2022-08-27T12:59:49.0000000+08:00
---

# 启动脚本编写
## busybox的rcS启动脚本

### 版本一
mkdir dev proc sys

sudo cp -a /dev/{null, console, tty, tty1, tty2, tty3, tty4} dev/

rm linuxrc

vim init

chmod a+x init

其中init文件的内容如下：

\#!/bin/busybox sh

mount -t proc none /proc \#-t指type 前面是source后面是directory

mount -t sysfs none /sys

### 版本二
首先，在busy-box的根目录下建立_install文件夹，作为文件系统
<table>
<colgroup>
<col style="width: 19%" />
<col style="width: 80%" />
</colgroup>
<thead>
<tr class="header">
<th><p>1</p>
<p>2</p></th>
<th><p>cd _install</p>
<p>mkdir -pv {bin,sbin,etc,proc,sys,usr/{bin,sbin}}</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>
在_install中的etc文件中增加inittab文件，

-------------------This is Content---------------------------

::sysinit:/etc/init.d/rcS

::askfirst:/bin/ash

::ctrlaltdel:/sbin/reboot

::shutdown:/sbin/swapoff -a

::shutdown:/bin/umount -a -r

::restart:/sbin/init

增加etc/init.d/rcS文件

\#!/bin/sh

mount -t proc none /proc

mount -t sys none /sys

/bin/mount -n -t sysfs none /sys

/bin/mount -t ramfs none /dev

/sbin/mdev

chmod+x./etc/init.d/rcS

配置dev目录

mkdir dev

sudo mknod dev/ttyAMA0 c 204 64

sudo mknod dev/null c 1 3

sudo mknod dev/console c 5 1

[西湖论剑 2020 IoT闯关赛 赛后整理 \| Clang裁缝店 (xuanxuanblingbling.github.io)](https://xuanxuanblingbling.github.io/iot/2020/11/17/iot/)

\#!/bin/sh

mount proc /proc -t proc

set -- \$(cat /proc/cmdline) \#读取启动参数

umount /proc

for x in "\$@"; do

case "\$x" in

overlayfsdev=\*) \#找到overlayfsdev对应的值，即：/dev/mtdblock5

OVERLAYFSDEV="\${x#overlayfsdev=}"

mtd erase /dev/mtd5

mount -n -t jffs2 \${OVERLAYFSDEV} -o rw,noatime /overlay

mkdir -p /overlay/rom/lower /overlay/rom/upper /overlay/rom/work

mount -n -t overlay overlayfs:/overlay/rom -o rw,noatime,lowerdir=/,upperdir=/overlay/rom/upper,workdir=/overlay/rom/work /tmp

mount --rbind /dev /tmp/dev/

mount --rbind /overlay /tmp/overlay/

mount --rbind / /tmp/overlay/rom/lower

\#绕过登录

echo 'root:\$1\$NqxdI63c\$nzvMkcJxzktGW6Tsgw3jb0:1::::::' \> /tmp/etc/shadow

exec chroot /tmp /sbin/init

;;

esac

done

exec /sbin/init

总之就是把根目录扔到/tmp目录下然后在chroot进去然后init

- [深入理解overlayfs（一）：初识](https://blog.csdn.net/luckyapple1028/article/details/77916194)
- [深入理解overlayfs（二）：使用与原理分析](https://blog.csdn.net/luckyapple1028/article/details/78075358)
- [用mtd 查看系统分区、备份恢复固件和刷新固件](http://blog.chinaunix.net/uid-28790518-id-5082378.html)
- [MTD应用学习：mtd和mtdblock的区别](https://blog.csdn.net/strugglelg/article/details/19202327)

[Linux /etc/shadow（影子文件）内容解析（超详细） (biancheng.net)](http://c.biancheng.net/view/840.html)

用于存储用户的密码

同 /etc/passwd 文件一样，文件中每行代表一个用户，同样使用 ":" 作为分隔符，不同之处在于，每行用户信息被划分为 9 个字段。每个字段的含义如下：

用户名：加密密码（SHA512 散列加密算法）：最后一次修改时间：最小修改时间间隔：密码有效期：密码需要变更前的警告天数：密码过期后的宽限时间：账号失效时间：保留字段

这段的密码是root

echo 'root:\$1\$NqxdI63c\$nzvMkcJxzktGW6Tsgw3jb0:1::::::' \> /tmp/etc/shadow
### 加载驱动
\#!/bin/sh

echo "INIT SCRIPT"

mkdir /tmp

mount -t proc none /proc

mount -t sysfs none /sys

mount -t devtmpfs none /dev

mount -t debugfs none /sys/kernel/debug

mount -t tmpfs none /tmp

insmod /ko_test.ko

echo -e "Boot took \$(cut -d' ' -f1 /proc/uptime) seconds"

setsid /bin/cttyhack setuidgid 1000 /bin/sh

poweroff -f

[Qemu 模拟环境 - CTF Wiki (ctf-wiki.org)](https://ctf-wiki.org/pwn/linux/kernel-mode/environment/qemu-emulate/)

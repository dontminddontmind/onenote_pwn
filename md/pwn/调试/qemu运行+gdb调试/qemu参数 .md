---
title: 'qemu参数 '
updated: 2022-11-08T12:39:43.0000000+08:00
created: 2022-08-24T23:54:16.0000000+08:00
---

addr2line查地址？
riscv64-unknown-elf-addr2line -e kernel/kernel

\$ addr2line -ekernel/kernel  
0x0000000080002de2  
0x0000000080002f4a  
0x0000000080002bfc  
Ctrl-D

​ 你应该看到类似下面的输出：

kernel/sysproc.c:74  
kernel/syscall.c:224  
kernel/trap.c:85

*来自 \<<http://xv6.dgs.zone/labs/requirements/lab4.html>\>*

# append指令（启动参数）
[emulation - what does -append field work in QEMU - Raspberry Pi Stack Exchange](https://raspberrypi.stackexchange.com/questions/9496/what-does-append-field-work-in-qemu)

The append line adds extra options to the kernel command line in UNIX derivatives. You can add many extra options such as
- root device (/dev/sda2 in your example)
- initrd file
- debugging options such as 'quiet'
- hdd emaulation (ide-scsi)
- boot type (single, rescue etc.)
- VGA mode
You can find which options you can pass to append line in QEMU kernel options manual :[page is now archived](https://web.archive.org/web/20131210001407/http:/xecdesign.com/working-with-qemu/)

| console=ttyS0      | 将输出重定向到console，将会显示在标准输出stdio。 |
|--------------------|--------------------------------------------------|
| root=/dev/ram      | 定位文件系统                                     |
| rdinit=/sbin/init  | 定位初始化进程？                                 |
| earlyprintk=serial |                                                 |
| nokaslr            | 关闭随机偏移                                     |
| quiet              |                                                 |
| oops=panic         |                                                 |
| panic=1            |                                                 |

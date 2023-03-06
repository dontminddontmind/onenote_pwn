---
title: 无法泄露libc
updated: 2022-05-25T16:50:40.0000000+08:00
created: 2022-05-24T19:01:29.0000000+08:00
---

# 篡改got表函数的低字节
让库函数移动到syscall等有用的gadget
1.  整数溢出，bss段上的数组\[负数到got\]
2.  栈溢出 \_\_libc_csu_init (pop rbx,rbp) + add \[rbp-0x3d\], ebx + rbp=got


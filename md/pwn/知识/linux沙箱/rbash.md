---
title: rbash
updated: 2021-11-03T20:04:40.0000000+08:00
created: 2021-11-03T20:04:35.0000000+08:00
---

# restricted bash
rbash的主要作用是限制了部分bash命令，其作用之一就是使得bash只能执行当前目录下的可执行文件，且不允许改变当前工作目录。
If bash is started with the name rbash, or the -r option is supplied at invocation, the shell becomes restricted. A restricted shell is used to set up an environment more controlled than the standard shell.
atum@ubuntu:\~\$ rbash  
atum@ubuntu:\~\$ cd PWN  
rbash: cd: restricted  
atum@ubuntu:\~\$ ./PWN/rp++  
rbash: ./PWN/rp++: restricted: cannot specify \`/' in command names  
atum@ubuntu:\~\$ export PATH=\$PATH:/home/atum/PWN  
rbash: PATH: readonly variable
rbash的绕过方法也有很多，通常跟chroot配合使用

*来自 \<<https://atum.li/2017/04/25/linuxsandbox/#linux%E4%B8%AD%E7%9A%84%E6%B2%99%E7%AE%B1%E6%8A%80%E6%9C%AF>\>*

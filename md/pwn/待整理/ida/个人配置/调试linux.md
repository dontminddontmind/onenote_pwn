---
title: 调试linux
updated: 2021-09-28T21:58:19.0000000+08:00
created: 2021-08-17T11:08:12.0000000+08:00
---

windows下使用IDA远程调试linux(ubuntu)下编译的程序
在IDA菜单中，选择“Debugger-\>Process options”，打开要调试的程序设置选项，在Application和Input file两项中输入ubuntu中要调试的程序，在Directory中输入要调试的程序所在的目录，在Hostname中输入linux机器的IP地址，端口保持默认即可，其它的输入项不用管，确定。如下图所示：
![image1](../../../../resources/image1-76.png)

*来自 \<<https://blog.csdn.net/lacoucou/article/details/71079552>\>*

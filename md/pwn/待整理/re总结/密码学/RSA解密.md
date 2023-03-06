---
title: RSA解密
updated: 2021-08-17T15:59:22.0000000+08:00
created: 2021-08-09T14:52:47.0000000+08:00
---

将n质因数分解
RSA因数分解工具yafu下载地址及使用方法介绍

*来自 \<<https://blog.csdn.net/dchua123/article/details/105444230>\>*

.\yafu-x64.exe "factor(6)"

接下来对它进行大整数的因数分解，这里借助 yafu 工具。

\>yafu-x64.exe  
factor(103461035900816914121390101299049044413950405173712170434161686539878160984549)

fac: factoring 103461035900816914121390101299049044413950405173712170434161686539878160984549  
fac: using pretesting plan: normal  
fac: no tune info: using qs/gnfs crossover of 95 digits

starting SIQS on c78: 103461035900816914121390101299049044413950405173712170434161686539878160984549

==== sieving in progress (1 thread): 36224 relations needed ======== Press ctrl-c to abort and save state ====SIQS elapsed time = 1.8809 seconds.  
Total factoring time = 1.9647 seconds

\*\***\*factors found\***\*\*

P39 = 366669102002966856876605669837014229419  
P39 = 282164587459512124844245113950593348271

ans = 1

*来自 \<<https://adworld.xctf.org.cn/task/writeup?type=reverse&id=5583&number=4&grade=1&page=2>\>*

已知p,q解密
基于python3在windows下安装gmpy2

*来自 \<<https://blog.csdn.net/qq_43302174/article/details/102933164>\>*

[Python 3.1.1 string to hex](https://stackoverflow.com/questions/2340319/python-3-1-1-string-to-hex)

*来自 \<<https://stackoverflow.com/questions/2340319/python-3-1-1-string-to-hex>\>*

接下来就可以求出私钥 d，并通过私钥 d，求出明文 m，再将其转化成 ASCII 即可得到 flag

import gmpy2

p = 366669102002966856876605669837014229419  
q = 282164587459512124844245113950593348271  
N = 103461035900816914121390101299049044413950405173712170434161686539878160984549  
c = 0xad939ff59f6e70bcbfad406f2494993757eee98b91bc244184a377520d06fc35  
e = 65537

d = gmpy2.invert(e,(p-1)\*(q-1))  
m = gmpy2.powmod(c,d,p\*q)

print hex(m)\[2:\].decode('hex')

print(binascii.unhexlify(hex(m)\[2:\].encode('utf8'))

得到flag：suctf{Pwn\_@\_hundred_years}

*来自 \<<https://adworld.xctf.org.cn/task/writeup?type=reverse&id=5583&number=4&grade=1&page=2>\>*

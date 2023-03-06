---
title: Base58
updated: 2021-09-25T13:48:03.0000000+08:00
created: 2021-08-25T10:34:42.0000000+08:00
---

**Base58**

*来自 \<<https://www.jianshu.com/p/d8af38e091be>\>*

1、将字符串的每个字节换算成ASCII(0-255) (字符串实际上就是256进制的数字组合)：
- 源字符串为：ABD
- 换算后： 65 66 68
2、将256进制的数字转换成10进制数字：
- 256进制数：65 66 68
- 转成10进制：(65 \* 256 + 66) \* 256 + 68 = 4276804
3、将10进制数字转换成58进制数字：
- 10进制数：4276804
- 58进制数： 21 53 20 0
4、将58进制数字的每一位按照表格转换成对应的字符：
- 58进制数：21 53 20 0
- 码表：123456789abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ
- 转换后的字符：nVm1
BASE_58 编解码原理及代码实现

解码没看懂

*来自 \<<https://blog.csdn.net/u013517122/article/details/83793296>\>*

[未命名1.cpp](../../../../resources/未命名1.cpp)

import base58 as bs

bs.b58decode('D9cS9N9iHjMLTdA8YSMRMp')

*来自 \<<https://adworld.xctf.org.cn/task/writeup?type=reverse&id=5476&number=4&grade=1&page=3>\>*

Base58算法加密解密（Python实现）

*来自 \<<https://blog.csdn.net/qin9800/article/details/105081894>\>*

[1.py](../../../../resources/1.py)


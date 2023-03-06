---
title: Python 进制转换
updated: 2021-06-01T17:32:28.0000000+08:00
created: 2021-04-16T10:24:59.0000000+08:00
---

IDA界面的底部有一个可以执行Python语句的文本框。这个功能可以让IDA使用者很方便的在各种进制之间切换：
![image1](../../../../resources/image1-78.png)
如果输入**0x45**会被解析成十六进制数，因为前缀有**0x**。按**Enter(回车)**就可以将十六进制转换为十进制。
![image2](../../../../resources/image2-48.png)
十六进制数**0x45**的转换结果如下图：
![image3](../../../../resources/image3-29.png)
十六进制的**0x45**转换为十进制69。如果想将再转换回去，必须使用**hex()**函数，hex(69)结果如下图所示：
![image4](../../../../resources/image4-27.png)
要转换为二进制，可以使用**bin()**函数：
![image5](../../../../resources/image5-22.png)

![image6](../../../../resources/image6-18.png)
**hex(0x45)**转换为二进制的结果数是**1000101**，因为前缀有**0B**，说明这是一个二进制数。得到的二进制数还可以用同样的方法转换为十进制或十六进制。
![image7](../../../../resources/image7-9.png)

![image8](../../../../resources/image8-6.png)
这个功能的作用就是Python栏里中输入数字，按Enter(回车)后将结果显示为十进制，也可以使用Python函数**hex()**或**bin()**把数字分别转换成Hex(十六进制)或Binary(二进制)。

*来自 \<<https://www.cnblogs.com/17bdw/p/12286079.html>\>*
**0x02、十六进制中的正负数表示**
逆向过程中在常常会接触到十六进制，32位表示负数的十六进制数又是怎么表示的呢？
十六进制正数的补是它本身。负数的补码是它本身的值每位求反,最后再加一。在32位二进制数中，可以使用第一位来表示0（正）还是1（负）。在IDA窗口**VIEW(视图)-\>CALCULATOR(计算器)**，可以调出这个窗口。
![image9](../../../../resources/image9-5.png)

*来自 \<<https://www.cnblogs.com/17bdw/p/12286079.html>\>*

转换字符的另一种方法是使用Python的**chr()**函数：
![image10](../../../../resources/image10-4.png)

*来自 \<<https://www.cnblogs.com/17bdw/p/12286079.html>\>*

**Python ASCII码与字符相互转换**
print( c + " 的ASCII 码为", ord(c))
print( a , " 对应的字符为", chr(a))

*来自 \<<https://www.runoob.com/python3/python3-ascii-character.html>\>*

十进制 print()

---
title: TCHAR
updated: 2021-04-07T14:41:05.0000000+08:00
created: 2021-04-06T17:30:02.0000000+08:00
---

**windows开发-TCHAR之痛**
- **Use Unicode Character Set**，其定义如下：  
  typedef WCHAR TCHAR, \*PTCHAR  
  其中WCHAR的定义为：typedef wchar_t WCHAR
- **Use Multi-Byte Character Set**，其定义如下：  
  typedef char TCHAR, \*PTCHAR
已知**char**类型长度为1个字节，而**wchar_t**类型长度为2个字节；

那么可知，**TCHAR**类型在**Multi-Byte**字符集下占**1**个字节，在**Unicode**字符集下占**2**个字节。

同一个**TCAHR**类型的数组变量在不同字符集下，长度是不同的。

*来自 \<<https://www.jianshu.com/p/22c354d7f1df>\>*

LPCTSTR和LPTSTR和char \*究竟有什么区别

LPTSTR:

如果定义了UNICODE宏，那么LPTSTR=wchar_t\*否则LPTSTR=char\*

LPCTSTR:

如果定义了UNICODE宏，那么LPCTSTR=constwchar_t\*，否则LPCSTR=constchar\*

*来自 \<<https://blog.csdn.net/feixiang_song/article/details/23271247>\>*

**请问:定义TCHAR a\[10\],有没有与strcpy,strlen,strcat,等对应的函数??**

不应该用strcpy,strlen,strcat。在ce上用wcscpy，wcslen，wcscat是可以的，因为在wince上TCHAR是unicode类型的，但标准的用法是用_tcscpy，\_tcscat。

这样做是为代码的可移植性考虑。因为TCHAR是宏，\_tcscpy，\_tcscat也是宏，在不同的平台上是映射到不同的字符类型的函数上的。

*来自 \<<https://bbs.csdn.net/topics/20290266>\>*


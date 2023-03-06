---
title: DA  LOBYTE、HIBYTE、BYTE0~BYTE3 的使用
updated: 2021-09-26T13:35:45.0000000+08:00
created: 2021-08-23T09:29:33.0000000+08:00
---


2021年8月23日
9:29

**DA LOBYTE、HIBYTE、BYTE0\~BYTE3 的使用**

1.  //测试 LOBYTE、HIBYTE
2.  typedef unsigned char uint8;
3.  \#define \_BYTE uint8
4.  \#define \_WORD uint16
5.  \#define LOBYTE(w) ((BYTE)(((DWORD_PTR)(w)) & 0xff))
6.  \#define HIBYTE(w) ((BYTE)((((DWORD_PTR)(w)) \>\> 8) & 0xff))
7.  \#define BYTEn(x, n) (\*((\_BYTE\*)&(x)+n))
8.  \#define WORDn(x, n) (\*((\_WORD\*)&(x)+n))
9.  \#define BYTE0(x) BYTEn(x, 0) // byte 0 (counting from 0) 添加此宏定义
10. \#define BYTE1(x) BYTEn(x, 1) // byte 1 (counting from 0)
11. \#define BYTE2(x) BYTEn(x, 2)
12. \#define BYTE3(x) BYTEn(x, 3)
13. \#define BYTE4(x) BYTEn(x, 4)
14. typedef unsigned long DWORD_PTR;
15. 
16. unsigned int data = 0x12345678;
17. 
18. printf("%04X\n", LOBYTE(data));//0078 ，所以LOBYTE相当于就是BYTE0；
19. printf("%04X\n", HIBYTE(data));//0056 所以HIBYTE相当于就是BY

*来自 \<<https://blog.csdn.net/jian274622701/article/details/114444491>\>*

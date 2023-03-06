---
title: dll变量名理解
updated: 2021-04-08T14:31:27.0000000+08:00
created: 2021-02-22T18:34:00.0000000+08:00
---

上午

LRESULT理解
已剪辑自: <https://blog.csdn.net/heary29/article/details/43304587>
在ｗｉｎｄｏｗｓ应用程序中经常能够看到LRESULT CALLBACK WndProc（HWND,UIINT, WPARAM,LPARAM）这句话，我们来详细讲讲。
（1）首先是对于LRESULT的理解  
LRESULT是一个数据类型，  
　　MSDN： 32-bit value returned from a window procedure or callback function  
　　指的是从窗口程序或者回调函数返回的32位值  
　　在winnt.h中typedef long LONG; 在windef.h中typedef LONG LRESULT;  
　　所以LRESULT就是long,也就是长整形  
　　之所以取名类LRESULT,L=\>long 。　result表示结果,说明这个函数的返回值是某个结果。  
（2）对于CALLBACK的理解  
\[cpp\] view plaincopy  
\#define CALLBACK \_\_stdcall   

\#define WINAPI \_\_stdcall   

\#define WINAPIV \_\_cdecl   

\#define APIENTRY WINAPI   

\#define APIPRIVATE \_\_stdcal   

l#define PASCAL \_\_stdcall   

  
由此可以看出这儿的CALLBACK指的函数调用规范

Handle ,HMODULE ,HINSTANCE,HINSTANCE
  Handle 是代表系统的内核对象，如文件句柄，线程句柄，进程句柄。

  HMODULE 是代表应用程序载入的模块，win32系统下通常是被载入模块的线性地址。

  HINSTANCE 在win32下与HMODULE是相同的东西，在Win32下还存在主要是因为win16程序使用HINSTANCE来区别task。

  HWND 是窗口句柄。

  HINSTANCE等同于HINSTANCE

 在程序中获取HINSTANCE 对象  HMODULE GetModuleHandle(NULL);
 在程序中获取HWND窗口 可以使用FindWindow() 查找窗口句柄

*来自 \<<https://blog.csdn.net/liaomin416100569/article/details/52017319>\>*

[**\_In\_ 是什么意思**](https://www.cnblogs.com/LeoGodfrey/p/3644107.html)

*函数参数类型前\_In\_*
*代表什么*

在visualC++中属于SAL批注，是为了编译系统在分析代码时发现缺陷用的

表示是一个输入参数。
可以定义一个_In_的宏，这个宏什么都不做，
就是形如这样的。
\#define \_In\_
void fun(int \_In\_ x); 等同于  
void fun(int x);

但是他给出了参数x是输入的意思

类似的还有_Out\_
\#define \_Out\_

*来自 \<<https://www.cnblogs.com/LeoGodfrey/p/3644107.html>\>*


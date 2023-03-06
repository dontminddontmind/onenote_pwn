---
title: Dll加载过程
updated: 2021-04-09T17:53:56.0000000+08:00
created: 2021-04-09T17:09:29.0000000+08:00
---

# 细说windows dll加载，一个cygwin错误引发的思考
windows dll加载地址分配方法:
- 对于未使能ASLR的dll(没有使用/DYNAMICBASE编译)，windows优先使用ImageBase作为地址加载，如果该地址在进程空间中被占用，则动态申请地址重新加载，按照windows的做法，这种情况不能共用物理内存，会导致更大的内存占用
- 对于使能了ASLR的dll，windows在该dll第一次被加载时全局分配地址，分配后，为了共用物理内存，后续进程使用相同的地址加载，除非冲突情况。

*来自 \<<https://kaige86.com/post/windows-dll.html>\>*

<https://m2.allhistory.com/detail/5924164455b54278ac002f51>

![image1](../../../../resources/image1-65.png)

不过这个线程“套间”和线程有什么关系？

访问dll以外定义的全局变量，为啥要用data节的指针？？

![image2](../../../../resources/image2-38.png)

[**程序员的自我修养九Windows下的动态链接**](https://www.cnblogs.com/Tan-sir/p/7602147.html)
- [9.1 DLL简介](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0)
  - [9.1.1 进程地址空间和内存管理](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_0)
  - [9.1.2 基地址和RVA](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_1)
  - [9.1.3 DLL共享数据段](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_2)
  - [9.1.4 DLL的简单例子](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_3)
  - [9.1.5 创建DLL](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_4)
  - [9.1.6 使用DLL](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_5)
  - [9.1.7 使用模块定义文件](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_6)
  - [9.1.8 DLL显示运行时链接](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label0_7)
- [9.2 符号导出导入表](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label1)
  - [9.2.1 导出表](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label1_0)
  - [9.2.2 EXP文件](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label1_1)
  - [9.2.3 导出重定向](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label1_2)
  - [9.2.4 导入表](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label1_3)
  - [9.2.5 导入函数的调用](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label1_4)
- [9.3 DLL优化](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label2)
  - [9.3.1 重定基地址（Rebasing）](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label2_0)
  - [9.3.2 序号](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label2_1)
  - [9.3.3 导入函数绑定](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label2_2)
- [9.4 C++与动态链接](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label3)
- [9.5 DLL HELL](https://www.cnblogs.com/Tan-sir/p/7602147.html#_label4)

*来自 \<<https://www.cnblogs.com/Tan-sir/p/7602147.html>\>*


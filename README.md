# pwn学习笔记
学习两年二进制安全的笔记，纯自用，由于工作量太大，目前不打算整理成博客
### 笔记格式
onenote分享笔记真的好麻烦呀，

使用工具导出了markdown版本，但是几乎没导出成功几个页面，

又导出了onenote文件，但onenote web clipper截取的笔记全都失效了。

在线观看或许是最方便的吧，但是缩进全都被展开了，而且需要科学上网才能点开：
[onenote笔记分享链接](https://1drv.ms/u/s!ApULe54GghWNrWFFPlZIYfoEZMm3?e=0rJFQ7)

虽说如此，但试过许多笔记后还是onenote用的顺手，

笔记对我而言是类似于外存的存在，把知识整理成树状结构才能最方便快速检索，而onenote的行首缩减是使用下来最顺滑的。

![缩进](https://user-images.githubusercontent.com/39674475/223334141-f361c6a4-27d0-4cf6-ac03-2e471a28910e.gif)

## 笔记简介
### 逆向

在考完研后，也就是2021年1月，我开始学习安全，因为之前读过《深入理解计算机系统》和《C primer plus》等书，以及有嵌入式开发经验，感觉二进制安全很亲切，又听说二进制中逆向最基础，所以就找了本《逆向工程核心原理》开始看。

这本书讲的通俗易懂，由浅入深，看得很开心。

对于书籍，我做笔记的方法是一字不漏的记录下来，切分成更细的知识点，用树形结构组织起来，方便以后的反复查阅。

如果书籍被查阅的次数很多，才会重新组织书籍的笔记，按照实际使用场景和用途来细分。

而因为9月之后我转方向到pwn（二进制漏洞利用），所以逆向的笔记也永远停留在刚读完书的样子。

除了《逆向工程核心原理》，还浅看了《黑客攻防技术-系统实战篇》、《IDA Pro权威指南》等书，但笔记都没有前者做得那么详细。

re总结，则是记录自己刷逆向类ctf题的笔记，简单做了一些分类，但之后也没再看过了。

![逆向工程核心原理](https://user-images.githubusercontent.com/39674475/223420322-9f2d359c-33c3-46db-ac96-58bfebded789.png)
![IDA](https://github.com/dontminddontmind/onenote_pwn/assets/39674475/535e8a5d-9407-4be8-9151-bca752bf315c)

### pwn做题方法论

不是刻意在做笔记，而是搞安全知识点真的太多，被逼天天做笔记！

最初记笔记就像贴便签，看见知识点就随便一记，这种笔记记下来它就不见了，找的时候就抓狂。而搞安全要不停回溯一堆特别细的知识点，于是，每抓狂一次，就被迫重新整理一次笔记，不知不觉，笔记居然有了高度分化的结构。

pwn总结这个笔记就是反复查阅、反复使用，总结下来的做题方法论。

把做题分成这几个步骤：找出漏洞->运行程序->数据处理->泄露信息->任意读写->操纵运行->虚拟机逃逸

再按照这几个步骤整理知识点，就算几个月没刷题忘光了，看一眼笔记就能立马想起来。当然，这个主要还是写给自己看的，过于精简，不适合分享给别人。（不过太过精简，过几年连名词都忘了，可能真的就连自己都看不懂了）

![pwn总结](https://user-images.githubusercontent.com/39674475/223364607-3329ed8e-e66d-4a2e-b0f5-7364f604625f.png)

### 堆
堆漏洞的利用需要对malloc和free的源代码非常熟悉，只是看懂是完全不够的，经过多次整理，我把源代码拆解成笔记，方便快速查阅。

每种数据结构，都尽量用一句话简述，之后再简述数据结构的特性，所有特点都会附上源码和源码的链接在缩进中。

而所有函数则按照这个格式整理：

```
函数声明
├─源代码在线查看链接
├─代码段1，一句话简述该代码段功能
│  └─缩进直接查看该代码段的源代码
├─代码段2，数据检查（蓝色），伪造数据时要注意
│  └─源代码
└─代码段3，这段代码在不同版本的libc库中存在差别（红色），利用时要注意
   ├─源代码（版本一）
   └─源代码（版本二）
```

堆漏洞的利用方法则参考how2heap，按照libc库的版本来分类利用方法，又根据自己的学习补充了每种利用的使用条件，实现步骤和利用方法。

![堆结构体](https://user-images.githubusercontent.com/39674475/223364276-1cf7b474-395f-40c8-85d5-e700870e9aec.png)

![堆实现代码缩进](https://user-images.githubusercontent.com/39674475/223373055-7521a134-abff-4081-a333-138a80521fec.gif)

![fastbin](https://user-images.githubusercontent.com/39674475/223366595-449e65e0-68ad-4109-8754-e0d8b9fc6997.png)

### linux和c知识

ctf题中总有一堆杂七杂八的linux知识，比如各种类型的系统调用、libc库函数、文件系统等等等等。

因为受不了老是要临时学新东西，又开了个分区打算系统学一下Linux，《linux/unix系统编程手册》这本书速看了一部分，之后又跟随网上的课程进一步学习linux和shell。

并重新系统学习了c++，因为遇到过不少需要逆向分析c++的题目，而且v8引擎、jvm就是用c++写的，未来可能需要进一步学习c++库函数的源码。

![linux中main是如何执行的](https://user-images.githubusercontent.com/39674475/223422134-bac80f3c-2684-4c93-bb04-166eea916059.png)
![c++ primer plys](https://github.com/dontminddontmind/onenote_pwn/assets/39674475/ecfc7a54-c9ee-4801-9e16-78bdfa4ec923)
![image](https://github.com/dontminddontmind/onenote_pwn/assets/39674475/965079f4-5ad7-4d15-bc9b-432bd500efea)


### 调试
主要是整理各种调试和运行的方法，qemu网上有很多教程，但总觉得好多名词搞不懂，搞不懂根本的原理，就慢慢整理调研。

![image](https://user-images.githubusercontent.com/39674475/223426832-5f49a83d-cc63-4692-95e7-09b4ad5bca76.png)

### IOT
整理各种架构的指令，方便查阅，阅读网上漏洞复现的文章，整理了一些漏洞挖掘步骤

![image](https://user-images.githubusercontent.com/39674475/223427476-4d4db5e3-b338-4dd5-8503-439b11863976.png)

### kernel
一开始是看youtube上的[pwn.college](https://www.youtube.com/@pwncollege)学kernel pwn，

之后觉得知识掌握不够，又看起Linux设备驱动，整理了一些笔记，不过这本书网上流传的中文版翻译是真的烂， [O'REILLY上可以免费看英文版](https://www.oreilly.com/library/view/linux-device-drivers/0596005903/)，我主要是用双语翻译插件在线看的英文版

随后还是觉得不够踏实，又看起了MIT的操作系统课6.S081，这个课真的很不错，感觉打通了之前的很多疑惑。

youtube上有很多很有用的up主，感觉知识永远学不完：

* [gamozolabs](https://www.youtube.com/@gamozolabs)，直播写fuzz程序，kernel fuzz之类的，很有用
* [BenEater](https://www.youtube.com/@BenEater)，从零造一台计算机，很好玩， [国内有人翻译](https://space.bilibili.com/413461202/) ，他的频道可以很快乐地动手从零开始学数字电路，计算机体系结构等知识
* [LiveOverflow](https://www.youtube.com/@LiveOverflow)，pwn方向up主，讲得很通俗易懂，还很精彩

还有很多，就不举例了，看完一个就要不少时间

之后自学了部分内核源码和工作流程，了解了一些内核安全模块知识
![image](https://github.com/dontminddontmind/onenote_pwn/assets/39674475/976206af-c3f0-443c-ba66-3b25fc975c8e)
![image](https://github.com/dontminddontmind/onenote_pwn/assets/39674475/fc6ce397-ee1e-434a-8e1a-67dc4b5c36e1)

### kernel pwn
不知道大家会不会这样，在做题看那些writeup时总是有一种难以用言语描述的淡淡的迷惑......

为什么要做这些事情，他们到底是怎么想到这个解法的......

经过补习kernel和linux的基础知识之后...终于，总算，看题有种豁然开朗，一切都联系起来了的感觉...

终于找回做题的快乐了...

｡･ﾟ･(ﾉД`)ヽ(ﾟДﾟ )

（当然，高兴只有一下下，接下来还是让人绝望的无穷无尽的学习）


今后会慢慢跟着这个复现kernel的cve: [kernel-security-learning](https://github.com/bsauce/kernel-security-learning)

xuanxuan的博客真的写得很好: [xuanxuanblingbling](https://xuanxuanblingbling.github.io/)

天枢学长们的博客也写得很好



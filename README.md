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

在考完研后，也就是2021年1月，我开始接触学习安全，因为之前读过《深入理解计算机系统》和《C primer plus》等书，以及有嵌入式开发经验，感觉二进制安全很亲切，又听说二进制中逆向最基础，所以就找了本《逆向工程核心原理》开始看。

这本书讲的通俗易懂，由浅入深，看得很开心。

对于书籍，我做笔记的方法是一字不漏的记录下来，切分成更细的知识点，用树形结构组织起来，方便以后的反复查阅。

如果书籍被查阅的次数很多，才会重新组织书籍的笔记，按照实际使用场景和用途来细分。

而因为9月之后我转方向到pwn（二进制漏洞利用），所以逆向的笔记也永远停留在刚读完书的样子。

除了《逆向工程核心原理》，还浅看了《黑客攻防技术-系统实战篇》、《IDA Pro权威指南》等书，但笔记都没有前者做得那么详细。

re总结，则是记录自己刷逆向ctf题的笔记，还简单做了一些分类，但之后也没再看过了。

![逆向工程核心原理](https://user-images.githubusercontent.com/39674475/223358877-dd5cc5dd-8191-424d-b937-05608dfc4efa.png)

### pwn做题方法论

不是刻意在做笔记，而是搞安全知识点真的太多，被逼天天做笔记！

最初记笔记就像贴便签，看见知识点就随便一记，这种笔记记下来它就不见了，找的时候就要抓狂。而搞安全要不停回溯一堆特别细的知识点，于是，每抓狂一次，我就重新整理一次笔记，不知不觉，笔记居然有了高度分化的结构。

pwn总结这个笔记就是我反复查阅、反复使用，总结下来的做题方法论。

把做题分成这几个步骤：找出漏洞->运行程序->数据处理->泄露信息->任意读写->操纵运行->虚拟机逃逸

再按照这几个步骤整理知识点，就算几个月没刷题忘关了，看一眼笔记就能立马想起来。当然，这个主要还是写给自己看的，过于精简，不适合分享给别人。

（不过太过精简，过几年连名词都忘了，可能真的就连自己都看不懂了）

![pwn总结](https://user-images.githubusercontent.com/39674475/223364607-3329ed8e-e66d-4a2e-b0f5-7364f604625f.png)

### 堆
堆漏洞的利用需要对malloc和free的源代码非常熟悉，只是看懂是完全不够的，经过多次整理，我把源代码拆解成笔记，方便快速查阅。



利用方法分类则主要参考how2heap，按照libc库的版本来分类利用方法，又根据自己的学习补充了每种利用的使用条件，实现步骤和利用方法。

![堆结构体](https://user-images.githubusercontent.com/39674475/223364276-1cf7b474-395f-40c8-85d5-e700870e9aec.png)
![堆实现](https://user-images.githubusercontent.com/39674475/223366484-1dc5678c-c05c-4da3-bdd9-a160cf567cc9.png)
![fastbin](https://user-images.githubusercontent.com/39674475/223366595-449e65e0-68ad-4109-8754-e0d8b9fc6997.png)

### linux和c知识


### 调试

### IOT

### kernel





---
title: 不能F5 P创建函数 修正堆栈
updated: 2021-08-27T14:16:50.0000000+08:00
created: 2021-08-27T14:06:57.0000000+08:00
---

[\[推荐\]IDA sp-analysis failed 不能F5的 解决方案之(二)-软件逆向-看雪论坛-安全社区\|安全招聘\|bbs.pediy.com](https://bbs.pediy.com/thread-158896.htm)
代码是红色的,就是说IDA没有分析出来,为了方便分析,我们会用快捷键P(CreateFunction)来创建函数.只是我们在函数头部按P的时候总会提示

我们看到retn左边绿色的数字是28,我们通过ALT+k修正堆栈,把28retn改成0就可以了。
修正堆栈的时候一定要选择Call然后修正堆栈,下图是修正后的代码

废话我就不多说了,造成不能F5的原因在于：
.text:00401642     mov eax, offset loc_40164A
.text:00401647     jmp eax
用OD打开之后 改掉代码在保存,然后重新用IDA打开 F5就可以了,sp-analysis failed 也就消失了.

*来自 \<<https://bbs.pediy.com/thread-140002.htm>\>*

**IDAPro F5出现too big function 解决方案**

*来自 \<<https://www.jianshu.com/p/e5d422a3df23>\>*
修改配置文件IDA 7.0\cfg\hexrays.cfg
MAX_FUNCSIZE =64// Functions over 64K are not decompiled
// 修改为：
MAX_FUNCSIZE =1024// Functions over 64K are not decompiled

<http://www.hex-rays.com/products/decompiler/manual/failures.shtml>

英语好的人,可以去官方主页去找解决方案.

不好的人也,也可以去,用工具翻译。

*来自 \<<https://bbs.pediy.com/thread-140002.htm>\>*


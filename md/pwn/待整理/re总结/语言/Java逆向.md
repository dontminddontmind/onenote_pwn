---
title: Java逆向
updated: 2021-08-19T22:18:00.0000000+08:00
created: 2021-07-24T11:39:24.0000000+08:00
---

[java安装](onenote:https://d.docs.live.net/8d1582069e7b0b95/文档/no%20的笔记本/文件同步.one#java&section-id={64C36C90-E129-4609-951D-28F5A0350464}&page-id={717554D6-C3F4-414D-9010-EFF90EF11CB9}&end)

CFR 工具比jd-gui更好用。

可以反编译类的注解，jd-gui无法反编译的 ，cfr却游刃有余。

1\. 下载地址： 推荐官网： <http://www.benf.org/other/cfr/>

2\. 反编译jar包方法：

把cfr工具比如cfr-0.150.jar和要反编译的jar比如： test.jar放在一起

java -jar cfr-0.150.jar test.jar --outputdir ./

运行命令就可以把反编译后的test.jar代码保存到当前路径下

[Java反编译反混淆神器 - CFR](https://www.cnblogs.com/somefuture/p/14009915.html)
用法相当简单，这是一个可执行jar包，把要反编译的jar传为参数即可。比如我要反编译的jar是aaa-bbb.1.0.jar，所在位置是\~/lib下面，则运行
java -jar cfr-1.5.jar \~/lib/aaa-bbb.1.0.jar
就能在控制台看到输出了。
当然我们可以重定向到文件：
java -jar cfr-1.5.jar \~/lib/aaa-bbb.1.0.jar \>\> dec.txt
所有的类都是在同一个文件里，我也不知道有啥方法可以直接生成多个Java文件。
上面这样运行后并没有反混淆，里面的变量名字依然一样。我们需要多加一个参数：
--renamedupmembers true
望文生义都能知道参数的意思是把重名的变量改个名：
java -jar cfr-1.5.jar \~/lib/aaa-bbb.1.0.jar --renamedupmembers true \>\> dec.txt
所以这样就可以了。
接下来是最后一个问题：这样反编译的结果中，所有的中文都被转为unicode了，如何解决呢？可以增加一个参数：
--hideutf false

*来自 \<<https://www.cnblogs.com/somefuture/p/14009915.html>\>*

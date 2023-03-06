---
title: pwntools 注意
updated: 2022-03-07T15:42:21.0000000+08:00
created: 2022-03-04T11:45:57.0000000+08:00
---

# [python版本](onenote:https://d.docs.live.net/8d1582069e7b0b95/文档/计算机书籍/编程语言/python.one#python版本&section-id={E64F6E08-3689-4A7B-A2DD-964E981A58E1}&page-id={3E5FD191-CE4D-4086-BC9F-C20A74E9797E}&end)

兼容问题
SyntaxError: Non-ASCII character ‘\xe5’ in file figure4_5.py on line 22, but no encoding declared; see <http://www.python.org/peps/pep-0263.html> for details

这是因为程序编码有问题，只需要在你程序开始的地方加入（程序最最顶端）以下代码即可：

\#!usr/bin/python

\# -\*- coding: utf-8 -\*-

<https://blog.csdn.net/weixin_40612082/article/details/80543460>


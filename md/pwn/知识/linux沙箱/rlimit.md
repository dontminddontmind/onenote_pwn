---
title: rlimit
updated: 2021-11-05T19:07:27.0000000+08:00
created: 2021-11-01T14:24:29.0000000+08:00
---

使用
struct rlimit r;

r.rlim_max = r.rlim_cur = 0;

setrlimit(RLIMIT_CORE, &r);

这里setrlimit的作用是根据参数RLIMIT_CORE，限制内核转储文件大小为0。
说明
[linux下core dump - AlanTu - 博客园 (cnblogs.com)](https://www.cnblogs.com/alantu2018/p/8468879.html)

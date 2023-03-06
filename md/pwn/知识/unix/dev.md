---
title: /dev
updated: 2022-03-10T14:44:00.0000000+08:00
created: 2022-03-10T14:41:29.0000000+08:00
---

/dev/urandom 随机数生成
[关于 /dev/urandom 的流言终结 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/64680713)

fd = open("/dev/urandom", 0);

if ( fd \< 0 \|\| read(fd, buf, 0x10uLL) != 16 )

exit(-1);

close(fd);


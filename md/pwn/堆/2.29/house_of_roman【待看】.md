---
title: house_of_roman【待看】
updated: 2022-03-24T19:13:43.0000000+08:00
created: 2022-03-24T18:43:48.0000000+08:00
---

<https://www.yuque.com/hxfqg9/bin/ape5up#ASHJ5>
"攻击分为三个阶段: \n\n"
"1. 通过低位地址改写使 fastbin chunk 的 fd 指针指向 \_\_malloc_hook.\n"
"2. 通过 unsortedbin attack 把 main_arena 写到 malloc_hook 上.\n"
"3. 通过低位地址修改 \_\_malloc_hook 为 one_gadget.\n\n";


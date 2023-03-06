---
title: '*tcache_stashing_unlink_attack'
updated: 2022-03-25T13:39:04.0000000+08:00
created: 2022-03-24T19:49:56.0000000+08:00
---

当malloc(smallchunk)时，如果smallbin中还有剩余块，那么它们会被取出装入tcache中，这个过程不会对剩余块做检查。于是可以篡改smallchunk的bk指针。
条件

实现
<https://ctf-wiki.org/pwn/linux/user-mode/heap/ptmalloc2/tcache-attack/#tcache-stashing-unlink-attack>

<https://www.yuque.com/hxfqg9/bin/qlry85#keGjh>
| [tcache_stashing_unlink_attack.c](https://github.com/shellphish/how2heap/blob/master/glibc_2.31/tcache_stashing_unlink_attack.c) | [▶️](https://wargames.ret2.systems/level/how2heap_tcache_stashing_unlink_attack_2.34) | Exploiting the overwrite of a freed chunk on small bin freelist to trick malloc into returning an arbitrary pointer and write a large value into arbitraty address with the help of calloc. | \> 2.25 | [Hitcon 2019 one punch man](https://github.com/xmzyshypnc/xz_files/tree/master/hitcon2019_one_punch_man) |
|----------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------|----------------------------------------------------------------------------------------------------------|

*来自 \<<https://github.com/shellphish/how2heap>\>*

例题
[Hitcon 2019 one punch man](https://github.com/xmzyshypnc/xz_files/tree/master/hitcon2019_one_punch_man)


---
title: elf文件操作 找地址
updated: 2022-03-04T13:39:29.0000000+08:00
created: 2021-09-08T12:36:56.0000000+08:00
---

# 找地址
## 找函数地址
这个还是挺实用的，在进行elf文件逆向的时候，总是需要对各个符号的地址进行分析，elf模块提供了一种便捷的方法能够==迅速得到文件内函数的地址，plt位置以及got表的位置。==

\>\>\> e = ELF('/bin/cat')

\>\>\> print hex(e.address) \# 文件装载的基地址

0x400000

\>\>\> print hex(e.symbols\['write'\]) \# 函数地址

0x401680

\>\>\> print hex(e.got\['write'\]) \# GOT表的地址

0x60b070

\>\>\> print hex(e.plt\['write'\]) \# PLT的地址

0x401680

同样，也可以打开一个libc.so来解析其中system的位置:

libc.sym\['func'\]
## search next
- elf.search('flag').next() 查找字符串的地址

libc = ELF('libc.so.6')  
binsh_addr_offset = next(libc.search('/bin/sh')) -libc.symbols\['system'\]

*来自 \<<http://www.vuln.cn/6644>\>*
- next(e.search("some_characters"))找到包含some_characters（字符串，汇编代码或者某个数值）的地址.

*来自 \<<https://bbs.pediy.com/thread-247217.htm>\>*
## 找节区地址
bash.get\_**section**\_by_name('.text').header.sh_addr

*来自 \<<https://docs.pwntools.com/en/latest/elf/elf.html?highlight=elf%20section%20address#pwnlib.elf.elf.ELF.address>\>*

# 修改ELF
甚至可以修改一个ELF的代码

\>\>\> e = ELF('/bin/cat')

\>\>\> e.read(e.address+1, 3)

'ELF'

\>\>\> e.asm(e.address, 'ret')

\>\>\> e.save('/tmp/quiet-cat')

\>\>\> disasm(file('/tmp/quiet-cat','rb').read(1))

' 0: c3 ret'

下面是一些可用的函数：

- asm(address, assembly) : 在指定地址进行汇编
- bss(offset) : 返回bss段的位置，offset是偏移值
- checksec() : 对elf进行一些安全保护检查，例如NX, PIE等。
- disasm(address, n_bytes) : 在指定位置进行n_bytes个字节的反汇编
- offset_to_vaddr(offset) : 将文件中的偏移offset转换成虚拟地址VMA
- vaddr_to_offset(address) : 与上面的函数作用相反
- read(address, count) : 在address(VMA)位置读取count个字节
- write(address, data) : 在address(VMA)位置写入data
- section(name) : dump出指定section的数据
<https://blog.csdn.net/gyhgx/article/details/53439417>

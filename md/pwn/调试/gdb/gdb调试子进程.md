---
title: gdb调试子进程
updated: 2021-09-15T11:06:35.0000000+08:00
created: 2021-09-15T19:05:56.0000000+08:00
---

上午

已剪辑自: <https://blog.csdn.net/dllbl/article/details/2978388>
[follow-fork-mode](https://blog.csdn.net/dllbl/article/details/2978388)
在2.5.60版Linux内核及以后，GDB对使用fork/vfork创建子进程的程序提供了follow-fork-mode选项来支持多进程调试。
follow-fork-mode的用法为：
set follow-fork-mode \[parent\|child\]
- parent: fork之后继续调试父进程，子进程不受影响。
- child: fork之后调试子进程，父进程不受影响。
因此如果需要调试子进程，在启动gdb后：
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>(gdb) set follow-fork-mode child<br />
</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

并在子进程代码设置断点。
此外还有detach-on-fork参数，指示GDB在fork之后是否断开（detach）某个进程的调试，或者都交由GDB控制：
set detach-on-fork \[on\|off\]
- on: 断开调试follow-fork-mode指定的进程。
- off: gdb将控制父进程和子进程。follow-fork-mode指定的进程将被调试，另一个进程置于暂停（suspended）状态。
注意，最好使用GDB 6.6或以上版本，如果你使用的是GDB6.4，就只有follow-fork-mode模式。
follow-fork-mode/detach-on-fork的使用还是比较简单的，但由于其系统内核/gdb版本限制，我们只能在符合要求的 系统上才能使用。而且，由于follow-fork-mode的调试必然是从父进程开始的，对于fork多次，以至于出现孙进程或曾孙进程的系统，例如上 图3进程系统，调试起来并不方便。
[Attach子进程](https://blog.csdn.net/dllbl/article/details/2978388)
众所周知，GDB有附着（attach）到正在运行的进程的功能，即attach \<pid\>命令。因此我们可以利用该命令attach到子进程然后进行调试。
例如我们要调试某个进程RIM_Oracle_Agent.9i，首先得到该进程的pid
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 tianq]# ps -ef|grep RIM_Oracle_Agent.9i<br />
nobody 6722 6721 0 05:57 ? 00:00:00 RIM_Oracle_Agent.9i<br />
root 7541 27816 0 06:10 pts/3 00:00:00 grep -i rim_oracle_agent.9i</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

通过pstree可以看到，这是一个三进程系统，oserv是RIM_Oracle_prog的父进程，RIM_Oracle_prog又是RIM_Oracle_Agent.9i的父进程。
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 root]# pstree -H 6722<br />
</th>
</tr>
</thead>
<tbody>
</tbody>
</table>
**[通过 pstree 察看进程](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image1](../../../resources/image1-23.png)

启动GDB，attach到该进程
**[用 GDB 连接进程](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image2](../../../resources/image2-14.png)

现在就可以调试了。一个新的问题是，子进程一直在运行，attach上去后都不知道运行到哪里了。有没有办法解决呢？
一个办法是，在要调试的子进程初始代码中，比如main函数开始处，加入一段特殊代码，使子进程在某个条件成立时便循环睡眠等待，attach到进程后在该代码段后设上断点，再把成立的条件取消，使代码可以继续执行下去。
至于这段代码所采用的条件，看你的偏好了。比如我们可以检查一个指定的环境变量的值，或者检查一个特定的文件存不存在。以文件为例，其形式可以如下：
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>void debug_wait(char *tag_file)<br />
{<br />
while(1)<br />
{<br />
if (tag_file存在)<br />
睡眠一段时间;<br />
else<br />
break;<br />
}<br />
}</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

当attach到进程后，在该段代码之后设上断点，再把该文件删除就OK了。当然你也可以采用其他的条件或形式，只要这个条件可以设置/检测即可。
Attach进程方法还是很方便的，它能够应付各种各样复杂的进程系统，比如孙子/曾孙进程，比如守护进程（daemon process），唯一需要的就是加入一小段代码。
[GDB wrapper](https://blog.csdn.net/dllbl/article/details/2978388)
很多时候，父进程 fork 出子进程，子进程会紧接着调用 exec族函数来执行新的代码。对于这种情况，我们也可以使用gdb wrapper 方法。它的优点是不用添加额外代码。
其基本原理是以gdb调用待执行代码作为一个新的整体来被exec函数执行，使得待执行代码始终处于gdb的控制中，这样我们自然能够调试该子进程代码。
还是上面那个例子，RIM_Oracle_prog fork出子进程后将紧接着执行RIM_Oracle_Agent.9i的二进制代码文件。我们将该文件重命名为 RIM_Oracle_Agent.9i.binary，并新建一个名为RIM_Oracle_Agent.9i的shell脚本文件，其内容如下：
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 bin]# mv RIM_Oracle_Agent.9i RIM_Oracle_Agent.9i.binary<br />
[root@tivf09 bin]# cat RIM_Oracle_Agent.9i<br />
#!/bin/sh<br />
gdb RIM_Oracle_Agent.binary</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

当fork的子进程执行名为RIM_Oracle_Agent.9i的文件时，gdb会被首先启动，使得要调试的代码处于gdb控制之下。
新的问题来了。子进程是在gdb的控制下了，但还是不能调试：如何与gdb交互呢？我们必须以某种方式启动gdb，以便能在某个窗口/终端与gdb交互。具体来说，可以使用xterm生成这个窗口。
xterm是X window系统下的模拟终端程序。比如我们在Linux桌面环境GNOME中敲入xterm命令：
**[xterm](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image3](../../../resources/image3-8.png)

就会跳出一个终端窗口：
**[终端](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image4](../../../resources/image4-6.png)

如果你是在一台远程linux服务器上调试，那么可以使用VNC(Virtual Network Computing) viewer从本地机器连接到服务器上使用xterm。在此之前，需要在你的本地机器上安装VNC viewer，在服务器上安装并启动VNC server。大多数linux发行版都预装了vnc-server软件包，所以我们可以直接运行vncserver命令。注意，第一次运行 vncserver时会提示输入密码，用作VNC viewer从客户端连接时的密码。可以在VNC server机器上使用vncpasswd命令修改密码。
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 root]# vncserver<br />
<br />
New 'tivf09:1 (root)' desktop is tivf09:1<br />
<br />
Starting applications specified in /root/.vnc/xstartup<br />
Log file is /root/.vnc/tivf09:1.log<br />
<br />
[root@tivf09 root]#<br />
[root@tivf09 root]# ps -ef|grep -i vnc<br />
root 19609 1 0 Jun05 ? 00:08:46 Xvnc :1 -desktop tivf09:1 (root)<br />
-httpd /usr/share/vnc/classes -auth /root/.Xauthority -geometry 1024x768<br />
-depth 16 -rfbwait 30000 -rfbauth /root/.vnc/passwd -rfbport 5901 -pn<br />
root 19627 1 0 Jun05 ? 00:00:00 vncconfig -iconic<br />
root 12714 10599 0 01:23 pts/0 00:00:00 grep -i vnc<br />
[root@tivf09 root]#</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

Vncserver是一个Perl脚本，用来启动Xvnc（X VNC server）。X client应用，比如xterm，VNC viewer都是和它通信的。如上所示，我们可以使用的DISPLAY值为tivf09:1。现在就可以从本地机器使用VNC viewer连接过去：
**[VNC viewer：输入服务器](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image5](../../../resources/image5-5.png)

输入密码：
**[VNC viewer：输入密码](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image6](../../../resources/image6-4.png)

登录成功，界面和服务器本地桌面上一样：
**[VNC viewer](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image7](../../../resources/image7-1.png)

下面我们来修改RIM_Oracle_Agent.9i脚本，使它看起来像下面这样：
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>#!/bin/sh<br />
export DISPLAY=tivf09:1.0; xterm -e gdb RIM_Oracle_Agent.binary</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

如果你的程序在exec的时候还传入了参数，可以改成：
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>#!/bin/sh<br />
export DISPLAY=tivf09:1.0; xterm -e gdb --args RIM_Oracle_Agent.binary $@</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

最后加上执行权限
| \[root@tivf09 bin\]# chmod 755 RIM_Oracle_Agent.9i |
|----------------------------------------------------|

现在就可以调试了。运行启动子进程的程序：
<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 root]# wrimtest -l 9i_linux<br />
Resource Type : RIM<br />
Resource Label : 9i_linux<br />
Host Name : tivf09<br />
User Name : mdstatus<br />
Vendor : Oracle<br />
Database : rim<br />
Database Home : /data/oracle9i/920<br />
Server ID : rim<br />
Instance Home :<br />
Instance Name :<br />
Opening Regular Session...</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

程序停住了。从VNC viewer中可以看到，一个新的gdb xterm窗口在服务器端打开了
**[gdb xterm 窗口](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image8](../../../resources/image8.png)

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 root]# ps -ef|grep gdb<br />
nobody 24312 24311 0 04:30 ? 00:00:00 xterm -e gdb RIM_Oracle_Agent.binary<br />
nobody 24314 24312 0 04:30 pts/2 00:00:00 gdb RIM_Oracle_Agent.binary<br />
root 24326 10599 0 04:30 pts/0 00:00:00 grep gdb</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

运行的正是要调试的程序。设置好断点，开始调试吧！
注意，下面的错误一般是权限的问题，使用 xhost 命令来修改权限：
**[xterm 错误](https://blog.csdn.net/dllbl/article/details/2978388)**  

![image9](../../../resources/image9.png)

<table>
<colgroup>
<col style="width: 100%" />
</colgroup>
<thead>
<tr class="header">
<th>[root@tivf09 bin]# export DISPLAY=tivf09:1.0<br />
[root@tivf09 bin]# xhost +<br />
access control disabled, clients can connect from any host</th>
</tr>
</thead>
<tbody>
</tbody>
</table>

xhost + 禁止了访问控制，从任何机器都可以连接过来。考虑到安全问题，你也可以使用xhost + \<你的机器名\>。
[小结](https://blog.csdn.net/dllbl/article/details/2978388)
上述三种方法各有特点和优劣，因此适应于不同的场合和环境：
- follow-fork-mode方法：方便易用，对系统内核和GDB版本有限制，适合于较为简单的多进程系统
- attach子进程方法：灵活强大，但需要添加额外代码，适合于各种复杂情况，特别是守护进程
- GDB wrapper方法：专用于fork+exec模式，不用添加额外代码，但需要X环境支持（xterm/VNC）。

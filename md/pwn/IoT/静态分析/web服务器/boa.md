---
title: boa
updated: 2022-05-15T14:02:06.0000000+08:00
created: 2022-05-10T16:10:42.0000000+08:00
---

<http://www.boa.org/>
[Ulord-Web/boa.md at master · UlordChain/Ulord-Web (github.com)](https://github.com/UlordChain/Ulord-Web/blob/master/boa.md)
编译
[(45条消息) boa移植 boa交叉编译_thomas_blog的博客-CSDN博客_boa交叉编译](https://blog.csdn.net/zhangxuechao_/article/details/82821739)

./configure

\# 改Makefile

CC = arm-linux-gnueabi-gcc

CPP = arm-linux-gnueabi-gcc -E

make
命令行参数
-c server_root，用来改变working directory，默认是/etc/boa，

默认配置文件是boa.conf，所以修改working directory，

会影响默认配置文件的读取。

-d 不fork

-f 指定配置文件的文件名。

-r chroot和chdir到那个目录，chroot后，所有的绝对路径都相对于设置的路径。

makefile
boa.c main函数
select.c loop函数
process_request
[(45条消息) boa源码解析（1）-接收请求，发送html的流程\_～边城浪子～的博客-CSDN博客](https://blog.csdn.net/zouwm12/article/details/72717113) 把完整的过程梳理出来了，但没写完

[boa学习 - ILD (insidelinuxdev.net)](https://insidelinuxdev.net/article/a0a4e1.html) 写完了request，比较简洁

get_request()，accept新请求，然后分配一个新的请求，将fd设置到request-\>fd。将status初始化为READ_HEADER

状态机，遍历request，每次只执行一个状态，执行完就退出
<table>
<colgroup>
<col style="width: 23%" />
<col style="width: 25%" />
<col style="width: 51%" />
</colgroup>
<thead>
<tr class="header">
<th>状态</th>
<th>函数</th>
<th>内容</th>
</tr>
</thead>
<tbody>
<tr class="odd">
<td><p>READ_HEADER</p>
<p>ONE_CR</p>
<p>ONE_LF</p>
<p>TWO_CR</p></td>
<td>read_header()</td>
<td><p>一个while循环，一个字符一个字符的解析回车，</p>
<blockquote>
<p>如果一个回车就是ONE_LF</p>
<p>如果两个回车就是READ_HEADER</p>
<p>结束循环</p>
</blockquote>
<p></p>
<p>如果状态是ONE_LF，则处理这一行，调用</p>
<p>process_logline()，处理http的第一行，process_option_line()，读key:value，设置cgi的参数</p>
<p></p>
<p></p>
<p>如果状态是BODY_READ，则调用process_header_end()</p>
<blockquote>
<p>unescape_uri 解析特殊字符</p>
<p>clean_pathname 清理路径中 /../ 之类的东东</p>
<p>读req-&gt;host ？</p>
<p>translate_uri 解析alias，如果是script，则解析对应的脚本的路径。</p>
<p>如果是POST（只有cgi才允许POST），则创建临时文件，文件描述符post_data_fd并返回，</p>
<p>如果是GET请求的cgi，则调用init_cgi，</p>
<p>如果是GET请求静态页面，则status变为write，调用init_get，打开静态文件。</p>
</blockquote>
<p></p>
<p>read() 没看懂</p></td>
</tr>
<tr class="even">
<td>BODY_READ</td>
<td>read_body()</td>
<td>从套接字读取数据到缓存，读到一些数据后，将状态设置为BODY_WRITE。</td>
</tr>
<tr class="odd">
<td>BODY_WRITE</td>
<td>write_body()</td>
<td><p>将read_body读取的数据，写入临时文件(post_data_fd）。如果写完了，就调用了init_cgi，启动cgi进程。</p>
<p></p>
<p>init_cgi()</p>
<p></p>
<p>创建pipe，对于boa，读端fd存储在data_fd，对于fork出来的cgi进程，写端fd，绑定到标准输出。如果是POST请求，post_data_fd绑定到标准输入。</p>
<p></p></td>
</tr>
<tr class="even">
<td>WRITE</td>
<td>process_get()</td>
<td>调用系统write()发送get的文件</td>
</tr>
<tr class="odd">
<td>PIPE_READ</td>
<td>read_from_pipe()</td>
<td>从data_fd，读取cgi的输出，</td>
</tr>
<tr class="even">
<td>PIPE_WRITE</td>
<td>write_from_pipe()</td>
<td><p>将从pipe读到的数据写入客户端套接字。</p>
<p></p>
<p></p>
<p></p>
<p>还有个IOSHUFFLE的状态，它处理partial request。</p></td>
</tr>
</tbody>
</table>

[(45条消息) 嵌入式web服务器BOA源码解析_finleyzhang的博客-CSDN博客_boa服务器源码](https://blog.csdn.net/u010372050/article/details/104241267)
GET调用链
POST调用链


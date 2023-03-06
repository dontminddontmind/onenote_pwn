---
title: qemu安装
updated: 2022-09-15T13:27:39.0000000+08:00
created: 2022-04-16T15:24:12.0000000+08:00
---

# 常用软件包

- qemu：比较完整的软件包，包括了qemu-system、qemu-user以及binfmt-support
- qemu-system：system模式的软件包，模拟完整的系统
- qemu-user：user模式的软件包，本身是动态链接
- qemu-user-static：user模式的软件包，本身是静态链接，用于chroot更换动态路径后仍然能运行
- binfmt-support：根据二进制的magic number选择解析器的工具

其实只要认真看一下apt install给出的提示就能看出，qemu除了没有包含qemu-user-static，剩下都有

*来自 \<<https://xuanxuanblingbling.github.io/ctf/tools/2020/04/16/qemu/>\>*
# 
# apt安装
sudo apt install git libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev

\#可以使用--install-suggests选项安装建议的包，即可安装我们需要的所有qemu功能：

sudo apt install--install-suggests qemu

sudo apt-get install qemu-user qemu-system qemu-user-static binfmt-support

# 编译安装
首先下载源码，在[官网](https://www.qemu.org/)可以直接下载，我下载了最新版本，即

wget <https://download.qemu.org/qemu-6.2.0.tar.xz>

下好之后解压，进入目录，编译安装，建议在其中建立一个 build 文件夹，因为会编译出来一堆东西。

mkdir build  
cd build  
../configure --gdb=/usr/bin/gdb --enable-debug --prefix=/usr/local

这里的参数，通过 --gdb 设置 gdb 路径，其实不需要显式设置这个；用 --enable-debug 开启调试功能；用 --prefix 设置安装的路径，我这里就直接安装到 /usr/local 中了。默认情况下会编译所有架构的虚拟机，正是我们需要的。

我在 configure 的时候碰到了ERROR: Cannot find Ninja，也就是缺少 ninja。解决这个问题，不建议直接通过包管理器安装，因为包管理器中的版本往往较低，可能还是无法满足需求，可以直接源码安装

git clone <https://github.com/ninja-build/ninja.git>

cd ninja

./configure.py --bootstrap

sudo cp ninja /usr/bin/

configure 好了之后，就可以 make 了

make -j\$(nproc)

这里加 -j 参数是指定编译使用的线程数，应为要编译大量架构的虚拟机，编译一次的时间会比较长，建议开到最大（\$(nproc) = 机器逻辑处理器数）。

make 好了后就可以安装

sudo make install

这样就安装好了 qemu，也自带了许多 libc，在 /usr/ 目录下。

*来自 \<<https://www.cjovi.icu/pwnreview/1353.html>\>*

没有uninstall，卸载不了：

sudo make uninstall

手动卸载：

[可执行文件](https://so.csdn.net/so/search?q=%E5%8F%AF%E6%89%A7%E8%A1%8C%E6%96%87%E4%BB%B6&spm=1001.2101.3001.7020)默认放在/usr/local/bin

库文件默认存放在/usr/local/libexec

配置文件默认存放在/usr/local/etc

共享文件默认存放在/usr/local/share

rm -rf /usr/local/bin/qemu-\*

rm -rf /usr/local/libexec/qemu-bridge-helper

rm -rf /usr/local/etc/qemu

rm -rf /usr/local/share/qemu

*来自 \<<https://blog.csdn.net/Oliverlyn/article/details/56667222>\>*

# 更改版本
如果系统内的 qemu 版本小于 3.0.0，首先删除系统内的 qemu，我们要安装 qemu-3.0.0:
<table>
<colgroup>
<col style="width: 27%" />
<col style="width: 72%" />
</colgroup>
<thead>
<tr class="header">
<th><p>1</p>
<p>2</p></th>
<th><p>sudo apt-get purge "qemu*"</p>
<p>sudo apt-get autoremove</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>
然后更改/etc/apt/sources.list的内容，启用源代码存储库

之后安装它的构建依赖
<table>
<colgroup>
<col style="width: 27%" />
<col style="width: 72%" />
</colgroup>
<thead>
<tr class="header">
<th><p>1</p>
<p>2</p></th>
<th><p>sudo apt-get update</p>
<p>sudo apt-get build-dep qemu</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>

<table>
<colgroup>
<col style="width: 17%" />
<col style="width: 82%" />
</colgroup>
<thead>
<tr class="header">
<th><p>1</p>
<p>2</p>
<p>3</p>
<p>4</p>
<p>5</p>
<p>6</p></th>
<th><p>cd./Downloads</p>
<p>wget <a href="https://download.qemu.org/qemu-3.0.0.tar.xz">https://download.qemu.org/qemu-3.0.0.tar.xz</a></p>
<p>tar -xf qemu-3.0.0.tar.xz</p>
<p>cd qemu-3.0.0/</p>
<p>./configure</p>
<p>make</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>
然后使用 checkinstall
<table>
<colgroup>
<col style="width: 25%" />
<col style="width: 74%" />
</colgroup>
<thead>
<tr class="header">
<th><p>1</p>
<p>2</p>
<p>3</p></th>
<th><p>sudo apt-get install checkinstall</p>
<p>sudo checkinstall make install</p>
<p>sudo apt-get install ./*.deb</p></th>
</tr>
</thead>
<tbody>
</tbody>
</table>
这样就安装完了，如果想卸载的话，依旧是输入apt remove qemu

最后禁止系统更新 qemu 到低版本，我们需要禁止更新 qemu
| 1   | echo"qemu hold"\| dpkg --set-selections |
|-----|-----------------------------------------|


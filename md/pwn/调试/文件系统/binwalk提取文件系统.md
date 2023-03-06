---
title: binwalk提取文件系统
updated: 2022-05-10T15:50:50.0000000+08:00
created: 2022-04-18T14:21:59.0000000+08:00
---

## 安装binwalk
git clone <https://gitee.com/h4lo1/binwalk.git>

cd binwalk

sudo python setup.py install

sudo apt install python-lzma
## 安装其他工具（等用到的时候再说吧！）
python-magic：用以根据文件头识别文件类型。

pip install git+https://github.com/ahupp/python-magic

jefferson：用于提取JFFS2 file systems。

pip install git+https://github.com/sviehb/jefferson

squashfs-tools：支持对squashfs格式的文件进行解压和压缩处理。

squashfs-tools的安装方法很多，可以使用apt进行快速安装。

sudo apt-get install squashfs-tools

Dlink路由器固件-qemu调试环境搭建
## binwalk使用
binwalk -A firmware.bin
| 无指令 | 扫描固件                 |
|--------|--------------------------|
| -A     | 识别指令集               |
| -e     | 提取文件                 |
| -Me    | M指根据magic进行递归提取 |

Binwalkt提取固件及qemu模拟
*来自 \<<https://blog.csdn.net/yalecaltech/article/details/104216139>\>*


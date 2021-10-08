# 1. 习题说明

# 2. 熟悉 Linux（2pt, 2h）

> 2.1 如何在 Ubuntu 中安装软件（命令⾏界⾯）？它们通常被安装在什么地⽅？ 

+ 安装软件
  + `apt` 安装（Ubuntu v16+）：`sudo apt install xxx`
  + `snap` 安装（载到虚拟环境）：`sudo snap install xxx`
  + `dpkg` 安装：`sudo dpkg -i 文件名.deb`
  + 参考：https://zhuanlan.zhihu.com/p/270908077
+ 安装到位置
  + `apt` 安装 -> `/usr/bin`
  + `dpkg` 安装 -> `/opt`
+ 查找软件安装的位置
  + 用 `find` 或 `whereis/which` 命令查找文件位置 

> 2.2 linux 的环境变量是什么？我如何定义新的环境变量？ 

+ 系统环境变量详解：https://blog.csdn.net/netwalk/article/details/9455893
+ 环境变量
  + 用来指定系统运行环境的一些参数
+ 定义新的环境变量
  + `sudo gedit ~/.bashrc`
  + 输入用户密码
  + 末尾添加 `export PATH=/opt/mysoft/bin:$PATH`
    + 其中 `/opt/mysoft/bin` 为你自己需要设置的环境变量路径
+ 使其立即生效，在终端执行 `source ~/.bashrc`


> 2.3 假设我要给 a.sh 加上可执⾏权限，该输⼊什么命令？


+ 输入命令：`sudo chmod +x a.sh`


![](../pic/1/quanxian8.png)

**注释一些内容**
+ 列出文件 `ls -l`

![](../pic/1/quanxian1.png)

+ 上图的解释

![](../pic/1/quanxian2.png)

+ 关于权限

![](../pic/1/quanxian3.png)


> 2.4 假设我要将 a.sh ⽂件的所有者改成 xiang:xiang，该输⼊什么命令？

+ 首先创建 `a.sh` 这个文件，并查看当前的权限信息以及拥有者和所属用户，这里是 `shiyanlou`

![](../pic/1/quanxian4.png)

+ 创建一个 `xiangxiang` 用户

![](../pic/1/quanxian5.png)

+ 更改文件拥有者 `chown`

![](../pic/1/quanxian6.png)

+ 更改文件的用户组 `chgrp`

![](../pic/1/quanxian7.png)

# 3. SLAM 综述文献阅读（3pt, 3h）


# 4. CMake 练习（2pt, 1.5h）


# 5. 理解 ORB-SLAM2 框架（3pt, 2h）


# 6. 使用摄像头或视频运行 ORB-SLAM2（3pt, 1h）
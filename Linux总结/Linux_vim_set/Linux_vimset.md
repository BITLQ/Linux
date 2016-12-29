Linux下g++/gdb的简单安装和vim的配置
-----------------------

	首先说明，本片博客所讲的g++和gdb的安装以及vim的配置仅在Centos 6.0 版本上进行了测试，所以，不同的版本可能会出现差异！

注： g++/gdb的安装方法给出的都是简单命令下载安装；

----------

**g++的安装：** 

现在下载的Centos的版本几乎都会自带gcc和vim，所以我们需要的只是g++而已；如果没有请先下载 gcc；

然后检查你的Linux是否有gcc:

```
：# which gcc;
```

如果有的话就会列出命令的路径，如下所示：

![这里写图片描述](http://img.blog.csdn.net/20161229133516703?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


没有的话请在确保你的**Linux连网**的情况下使用以下命令安装：

```
：# yum  install  gcc;
```

当然也可以下载压缩包进行解压缩安装，不做讨论；

如果有gcc，那么检查你的Linux是否有g++:

```
:# which  g++
```

如果有的话就会列出命令的路径，如下所示：

![这里写图片描述](http://img.blog.csdn.net/20161229133246883?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

没有的话请在确保你的**Linux连网**的情况下使用以下命令安装：

```
：# yum  install gcc-c++;  //注意是  gcc-c++;
//注意在Centos和红帽使用该命令可以；
```
当然也可以下载压缩包进行解压缩安装，不做讨论；


----------

**gdb的安装 ：**

: 请在确保你的**Linux连网**的情况下使用以下命令安装：

```
：# yum install  gdb;
```

其实这三个都是利用 yum 安装的；


----------

**vim的配置**

vim是Linux下强大的编辑器，我们初学者对它是又爱又恨；

我们不得不承认vim的强大，允许我们自己进行各种配置和插件的安装，把vim配置的几乎可以和windows下的IDE相媲美；

而我们Linux自带的vim配置就相对比较简陋了，使用root权限进入根目录下的etc/ 目录，列出所有文件（包含隐藏的文件）你就会发现一个文件名为 vimrc的文件（或者是.vimrc），这就是存放Linux 默认配置的地方；

```
：# cd  /root/etc/
```

![这里写图片描述](http://img.blog.csdn.net/20161229141359472?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


里面就是默认配置，可以用 vim   vimrc  命令进去看一下；

而我们一般自己去配置的时候，不去改动这个文件，而是选择在自己当前用户的主目录下新建一个 .vimrc  文件，存放我们的配置：

**注： 在当前用户的主目录下进行配置的只对当前用户有效！**

```
：# cd ~/     //进入当前用户的主目录
：# touch  .vimrc  //创建一个 .vimrc  文件
```
如果你觉得你不需要很多的功能的话，把下面这下简单的配置黏贴进创建的 .vimrc 文件即可；

```
：# vim  .vimrc    //进入.vimrc  文件
```

将以下内容复制进去：

```	
1 set nocompatible
  2 set number
  3 filetype on
  4 set history=1000
  5 color evening
  6 syntax on
  7 set autoindent
  8 set smartindent
  9 set tabstop=4
 10 set shiftwidth=4
 11 set showmatch
 12 set guioptions-=T
 13 set vb t_vb=
 14 set ruler
 15 set nohls
 16 set incsearch
 17 if has("vms")
 18 set nobackup
 19 else
 20 set backup
 21 endif
```

```
设置完后
 
$:x 或者 $wq 

 进行保存退出即可。有些linux里vi即调用vim，可以用which vi或alias查看。

 下面给出一个例子，其中列出了经常用到的设置，详细的设置信息请参照参考资料：

 “双引号开始的行为注释行，下同
 
“去掉讨厌的有关vi一致性模式，避免以前版本的一些bug和局限

 set nocompatible

 “显示行号

 set number

 “检测文件的类型

 filetype on 

 “记录历史的行数

 set history=1000 

 “背景使用夜晚模式 //你会很爽的

color eveing

 “语法高亮度显示

 syntax on 

 “下面两行在进行编写代码时，在格式对起上很有用；

 “第一行，vim使用自动对起，也就是把当前行的对起格式应用到下一行；

 “第二行，依据上面的对起格式，智能的选择对起方式，对于类似C语言编

 “写上很有用

 set autoindent

 set smartindent

 “第一行设置tab键为4个空格，第二行设置当行之间交错时使用4个空格

 set tabstop=4

 set shiftwidth=4

 “设置匹配模式，类似当输入一个左括号时会匹配相应的那个右括号

 set showmatch

 “去除vim的GUI版本中的toolbar

 set guioptions=T

 “当vim进行编辑时，如果命令错误，会发出一个响声，该设置去掉响声

 set vb t_vb=

 “在编辑过程中，在右下角显示光标位置的状态行

 set ruler

 “默认情况下，寻找匹配是高亮度显示的，该设置关闭高亮显示

 set nohls

 “查询时非常方便，如要查找book单词，当输入到/b时，会自动找到第一

 “个b开头的单词，当输入到/bo时，会自动找到第一个bo开头的单词，依

 “次类推，进行查找时，使用此设置会快速找到答案，当你找要匹配的单词

 “时，别忘记回车

 set incsearch

 “修改一个文件后，自动进行备份，备份的文件名为原文件名加“~“后缀

 if has(“vms”) //注意双引号要用半角的引号"　"

 set nobackup

 else

 set backup

 endif
```


然后你再打开一个 xxx.c 或者 xxx.cpp文件编辑一段代码，就会看到配置效果；如下图：

![这里写图片描述](http://img.blog.csdn.net/20161229140659469?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


----------


**Vim  再配置**

前面我们已经说了，vim不仅可以支持简单的配置也可以安装以下列的插件，这里我就直接列出大神的vim配置链接：

http://www.cnblogs.com/ma6174/archive/2011/12/10/2283393.html

这位大神的配置可以支持很多编程语言的环境，甚至在github 上给出了.sh 文件可以你只需要在终端执行一条命令什么都不用做；

![这里写图片描述](http://img.blog.csdn.net/20161229145749719?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

如果你在执行这条命令时报错，提示。。。。。-no-check。。。
只需要这样执行即可：

```
：#wget https://raw.github.com/ma6174/vim/master/setup.sh --no-check-certificate && bash setup.sh
```

注： 在连网的环境下执行即可自动下载安装；

但是可能安装好之后vim 一个文件会出现很多问题，因为可能因为每个人Linux配置不同的原因，很多东西用不了，那么只需要按照提示出错的行号，进入文件将对应行用 **引号** 注释掉即可；
 
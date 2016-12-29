【Linux】find 命令概述

分析Linux下的查找命令linux下常用的查找命令：
–文件查找命令：locate, find; 
–其它查找命令：which，whereis，whateis;

文章大体框架：
第一部分：对查找命令的概述；
第二部分：对 find 命令及其参数使用详细描述；
第三部分： 总结；
第一部分：查找命令概述
注： 文章下述所有命令都尽量自己在man/info中查看文档说明； 文章中不再截图标识；

1.1 文件查找命令—locate（简介）
 注：先去 man / info  locate;

	* 1

命令介绍：顾名思义，定位的意思，作用是让使用者可以快速的搜寻系统中是否有指定的文件，或者是含有查找字符的文件；有意思的是这个命令是非实时的，查找时根据全系统文件数据库进行的，模糊查找；阅读man文档话就会发现这个命令一般配合 updatedb 使用；
命令使用： loctae filename
: 创建一个文件 test.txt ; 查找 test.txt 文件； 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/1.png)

：注意查找结果，并没有查找到刚创建的 test.txt， 这就是命令介绍里所说的是在文件系统数据库中进行查找且一般配合 updatedb 使用的原因，最近增加或者删除的文件，如果不 updatedb 的话是 locate 不到的，下面我们试试 updatedb；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/2.png)

命令使用2： 根据字符串查找匹配文件

locate include //查找文件名含有include字符串的文件
注： 结果不做截图，你会发现会找到特别多的文件；
1.2 文件查找命令–find(简介)
 注：先去 man / info  find;（这个特别长，估计很难看下去）

	* 1

命令介绍：find命令在目录结构中搜索文件，并执行指定的操作。所以查找速度比较慢，Linux下find命令提供了相当多的查找条件，功能很强大。由于find具有强大的功能，所以它的选项也很多，这里我们先简单的示范，后面详细讲解；

使用格式：find(选项)(参数)
命令使用：find命令用来在指定目录下查找文件。任何位于参数之前的字符串都将被视为欲查找的目录名。如果使用该命令时，不设置任何参数，则find命令将在当前目录下查找子目录与文件。并且将查找到的子目录和文件全部进行显示。
来自: http://man.linuxde.net/find
例如：
find test.txt // 直接查找不加参数选项，直接在当前目录查找

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/3.png)

（后面详述！）
1.3 查找命令–which
命令介绍：定位一个命令的完整路径; 我们经常用来查看一个命令是否存在；若存在就列出路径；
注意：which 命令是按照PATH环境变量的路径查找；
使用格式：which 命令
首先，我们先找一个不存在的命令，看结果：
which sb

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/4.png)

：看到没，没有 no sb in，然后后面的括号里就是PATH环境变量的路径，不信的话你可以 echo $PATH 看一看；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/5.png)

： 尝试查找命令 ls：
# which ls

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/6.png)


1.4 查找命令–whereis
命令介绍：与which类似，而且会额外的给出给出该命令的man页的完整路径
命令使用： 查找命令 ls
# whereis   ls

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/7.png)


1.5 查找命令–whatis
命令解析： whatis命令是用于查询一个命令执行什么功能，并将查询结果打印到终端上;个人认为这个很好用！
来自: http://man.linuxde.net/whatis
比如我们查看 ls 命令和 chown 命令；
# whatis  ls# whatis  chown

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/8.png)


第二部分： find 命令详细分析
find命令的介绍前面已经简单的说明和简单的使用过了，下面我们对find命令的参数及使用进行详细介绍；
2.1 find命令的使用格式
find   [PATH]    [option]   [action] 

2.2 find命令的参数介绍
find 命令不可谓不强大，可以代替很多命令，但是与之相随的就是繁多的参数选项；
参数大致分类有：
1> 与时间有关的参数； 
2> 于用户用户组名有关的参数； 
3> 与文件权限及名称有关的参数； 
4> 其他可进行的操作；

下面按照参数分类进行部分举例说明：
2.2.1 与时间有关的参数
注：与时间有关的参数有 -atime,-ctime,-mtime;
关于这三个时间参数我专门有一篇博客介绍： 

http://blog.csdn.net/bitboss/article/details/53870273
参数格式： 以mtime为例；
-mtime n : 在n天之前的 <一天之内>被修改过的文件；
：# find   /root/code/  -mtime  1  //这个路径下一天前的一天之内，内容被修改的文件；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/9.png)


-mtime +n : 列出n天之前（不包括n天），被更改过的文件； 
-mtime -n: 列出n天之内（包含n）被更改过的文件
// 不做截图演示
：# find   /   -mtime  +2     //列出根目录下2天之前被修改的文件  
：# find   /   -mtime  -2      //列出2天之内被更改过的文件


* -newer file : * file为一个存在的文件，列出比file还要新的文件；
：# find    /root/code/    -newer  /root/code/test.c
//列出 /root/code/ 目录下比  /root/code/test.c  文件还要新的文件；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/10.png)


注： 可以在目录下 ll 命令查看对比；
2.2.2 与用户或用户组名有关的参数
参数格式：
-uid n : 查找属于对应的UID的用户的文件；
-gid n: 查找属于对应GID的用户组的文件；
（UID，GID会在以后的博客中介绍）；
-user name : name为用户名，查找目录下属于该用户的文件！
：#find  /home  -user  bossliu //bossliu  是我的用户，请输入自己的用户名；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/11.png)

//查找 home 目录下属于bossliu用户的文件；//不做截图展示

-group name : 类似上一条命令，查找目录下属于该用户组的文件；
：#find   /home   -user    bossliu  //请输自己的用户组//为什么和上一条命令一样呢，因为如果你在创建用户的时候没有指定的用户组，linux默认以用户名生成一个用户组；

// 命令结果和 -user  name  的结果



-nouser : 查找给定目录下无属主的文件； 
-nogroup :查找给定目录下无属组的文件；
：# find   /   nouser  //查找根目录下无属主的文件；
：# find   /    nogroup  //查找根目录下无属组的文件；

//不做截图展示


2.2.3 与文件权限及名称有关的参数
参数格式 ：
-name filename : 查找文件名filename，如不加路径，则默认在当前目录下查找；

注： 还测试了没有给路径名和-name参数的实例；
-type TYPE : 查找文件类型为TYPE的；文件的类型不做赘述； 
// l : 链接文件 
// d: 目录 
// f： 普通文件 等等；
：# find  /root  -type  l//查找 /root 目录下文件类型为“链接”的文件；


![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/12.png)

注： 文件的类型将在文件系统概述的博客中讲解；
-size [-+]SIZE : 查找指定目录下大于小于或等于 SIZE的文件，注意，SIZE也有单位， c 代表 byte, k 代表 KB；当然还有 M，和 G；
：#find   /root/code   -size  +1k 
//查找 /root/code 目录下大小  >1KB的文件；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/13.png)

可以在这个目录下 ll 看一下文件大小：
：# cd  /root/code; ll   

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/14.png)


注：经测试小于1k的文件要查找的话只能用 <1000c 查找；
-perm mode : 查找指定路径下文件权限是 mode（权限值） 的文件；
 : # ll      //查看目录下的文件权限
：# find  -perm  777     //查找权限为777的文件；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/15.png)


-perm -mode : 在指定目录下查找“至少包含mode权限的文件”；
// 比如 mode是 -rw-rw-rw-, 如果一个文件的权限是 -rwx-rwx-rw; 
// 那么这个文件也会被找出来；
:# find  -perm -644

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/17.png)


-perm +mode : 在指定目录下查找文件权限包含“任一mode权限”的文件； 
// 举个例子，mode是 -rw-rw-rw-, 而test文件的权限是 -rw-r–r–; 那么test文件也会被列出；
:# find  -perm +644

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/16.png)


当然还有可以查找特殊权限的文件，比如含有SGID,SUID,SBIT属性的文件，这里就不一一举例了；
注：关于文件的权限问题会在文件的权限管理概述中讲解；
2.2.4 其他可进行操作
参数格式
-exec command : 在exec参数之后可以接其它命令来处理查找结果；
注意： 这个参数的使用格式；
： #  find  -perm -644 -exec  ls  -l  {} \;
// 将查找的文件用 ls  -l  命令列出来； 注意使用时后面的 {}  \ ;{} 存放的就是查找结果；‘\’ 代表命令的结束而且还和 ‘；’构成转义；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_Find/photo/18.png)

第三部分： 总结
通过对以上find命令的介绍，对find命令有了更深刻的认识，同时我们所说的命令参数还不是完整的，find还有有些不常用的参数没有介绍，可以通过man 去了解；
文章中遗留的关于文件的权限和分类的问题，会在接下来的博客中进行补充！
                 ---参考《鸟哥的Linux私房菜》第三版

完！

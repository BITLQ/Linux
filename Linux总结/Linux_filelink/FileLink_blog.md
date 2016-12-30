
-------------

**重点内容： 文件的链接**

**Linux下文件的链接分为两种：** **软连接 和 硬链接**；


----------


在Linudx下使用 ls -l 命令即可看到文件的很多信息，其中第一列的第一个字符代表的就是文件的类型；而下面紧跟的数字代表文件的连接数；

**比如**:
**-r-xr-xr-x**  这个字符串**第一个字符，代表文件的类型**；

linux下文件的类型通常有以下几类：

> d  :   代表一个目录；
> - ：  代表一个普通文件；
>  l   :   代表一个普通文件； 
>  b :    代表设备文件里面的可供存储的接口设备； 
>  c :     代表设备文件里的串行端口设备；

在Linux下每个文件都有一个与之对应的inode节点号，用来保存文件的信息，而查看文件的inode节点号可以用 ls -i filename命令；

```
: # ls -i test1  //查看test1文件的Inode节点号
```
![这里写图片描述](http://img.blog.csdn.net/20161230073547067?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

： 我们可以看到test1的文件inode节点号为 398662;（这里不对inode节点的结构作分析）

 可是这和我们所要说的文件的链接又有什么关系呢？

： 当然有关系，因为软连接和硬链接都直接和文件的inode节点有关系；


----------


**1. 硬链接(hard  link) ：**

既然每个文件都有inode节点号，那么硬链接的实现究竟是怎么在inode节点上做的文章呢？

其实，硬链接的实现原理和我们C++编程中内存管理使用的**引用计数** 的方式是一样的，举例来说：

```
：# ls -il test1  // 看看test1权限后面的数字是不是 1；
```
![这里写图片描述](http://img.blog.csdn.net/20161230104807795?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

```
创建硬链接的命令： # ln  [src]  [dest];
：# ln test1 test1-hd  //为文件test1 创建硬连接文件 test1-hd;
```

![这里写图片描述](http://img.blog.csdn.net/20161230080802942?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

分析： 我们为test1文件创建了一个硬链接文件test1-hd,通过截图可以看出，test1 和 test1-hd 使用同一个inode节点号，说明它们是同一个文件，而且细心的你会发现，它们的文件链接数都变为了 2 ，是不是和引用计数一样，多一个硬链接文件就会把链接数+1；更准确的说，test1 和test1-hd链接的都是 inode 所代表的文件；此inode上链接了两个文件；

：此时，我们应该也有疑惑，既然这 test1 和 test1-hd代表的是同一个文件，那么我们对test1-hd做一些修改会不会改变 test1呢？

我们试试：

```
首先看看test1里面有没有内容：
：# cat   test1
```
![这里写图片描述](http://img.blog.csdn.net/20161230082017023?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

**test1此时没有内容**
```
// 向test1-hd 添加内容
： #echo "hello looker"
```

然后查看test1 和 test1-hd 内容；

![这里写图片描述](http://img.blog.csdn.net/20161230082323152?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

：结果是不是很明显，同时改变了test1的内容，更准确的说是改变了此inode节点所代表的文件的 内容；

**还有疑问？  引用计数的话，我把test1-hd 或者 test1删掉的话，是不是不会影响另一个文件，同时引用计数-1？**

:那就继续试试吧!   毕竟实践才是真知！

```
// 以删除test1-hd 为例；
：#rm -f test1-hd

//然后在看文件信息是否变化
：# ls -ial

//看看test1的内容是否变化
：# cat  test1
```

![这里写图片描述](http://img.blog.csdn.net/20161230083252358?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

：结果很明显了，正如我们所预料的，test1-hd被删除后，test1的内容没有收到影响，而连接数变为了 1；

**小结一下 **

到这里我们就可以小结一下硬链接了；

硬链接是采用对inode代表文件引用计数的方式对文件进行链接，对任一链接文件进行修改都会直接影响到全部链接文件，而删除某一链接文件，不会影响其它链接文件的内容，但是文件的引用计数会-1，除非引用计数为0，否则inode所代表的文件不会被删除。

**硬链接的限制**：

我们在使用硬链接的同时也需要对硬链接的限制有所了解；
1. 不能跨文件系统
2. 不能链接到目录

分析：第一点很好理解，我们就第二点作一些解释；

假如你尝试链接目录，系统会报错：
![这里写图片描述](http://img.blog.csdn.net/20161230084633184?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

不能链接目录？ 原因呢，其实也很好理解，如果给目录创建链接的话，关系的可不是目录本身，关乎目录下的所有文件，比如你在硬链接的ld-hd 目录下要创建一个新文件，必须在ld目录下有一个与之对应的文件，可想而知如果目录的链接多了，这是多么繁多的工程，正是因为这个复杂的原因，Linux不允许为目录创建硬链接；


----------


**2. 软链接(symbolic  link）：**

软连接又叫做符号链接，它几乎可以等价于windows下的快捷方式；

那么软连接的实现又在inode上做了什么文章呢？

其实也很简单，软连接是创建一个新的 inode，而这个indoe所指向的文件里存的内容呢？  是被链接文件的“文件名”，为什么文件名要带引号呢？ 因为如果是链接不同的目录下的文件，需要在链接的时候加上绝对路径，而此时软链接新建的文件里的内容就是这个路径，也就是“文件名”；

那么，现在就很好理解为什么软连接是不同的文件，却可以得到被连接文件的内容，是通过链接文件中存放的“文件名”找到被链接文件的；

做个示范：

```
软链接的命令格式： ln -s [src] [dest]
// 为test1文件在同一目录下创建软连接 test1-so
: # ln -s test1 test1-so

// 查看文件的信息：
：# ls -il  
```

![这里写图片描述](http://img.blog.csdn.net/20161230090739355?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

分析 ： 看结果我们很容易看出和硬链接不同的地方，即软连接文件的inode和test1的不同，并且引用计数没有增加；

那么我们前面说的test1-so中应该存放的是test1的文件名而不是test1的内容，怎么验证呢？ 如果你知道那一列代表的是文件的大小的话就很好看出来了，但是这里我们用 **stat** 命令查看文件的信息：

```
：#stat  test1-so  //查看test1-so的文件信息
```

![这里写图片描述](http://img.blog.csdn.net/20161230091529539?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

：我们可以看出文件的 size 为5，单位字节，符号链接等一系列信息；
为什么大小是5呢？  因为 test1 这个文件名有五个字符啊！  这下明白了吗？

值得注意的是我们这里是在同一目录下创建软链接，所以size是5；如果是在不同的目录下创建test1的软连接，那么绝对路径即是软连接文件的内容，举个例子：

```
比如说我们现在 /root/code目录下；
：# ln -s /root/Test/test1   test1-so
```
![这里写图片描述](http://img.blog.csdn.net/20161230092401550?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

**分析**： 此时的test1-so的大小是16，而它链接的文件的路径是 **/root/Test/test1**   加上 / 一共16个字符，这个就是test1-so中的内容，现在是否明白了软连接到底是怎么回事了；

还没完！！！

我们还没试试修改或者删除软连接对被连接文件的影响呢？
**回到/root/Test目录**
```
：# cat  test1-so  //显示test1-so内容，注意显示所连接文件的内容

向test1-so 中添加内容
: # echo "hello  world">>test1-so

：# cat  test1-so  //显示test1-so内容
：# cat  test1     //显示test1的内容
```

![这里写图片描述](http://img.blog.csdn.net/20161230093555435?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

分析：看结果，我么可以看出，和硬链接一样，对软连接文件的修改同样会影响到被连接文件；

同理，我们分析一下删除源文件对软连接文件的影响和删除软连接对源文件的影响；

现在我们已经知道了软连接的实现原理，联想windows下快捷方式的工作原理，很容易就可以推断出，删除软连接的话，不会影响源文件，而如果删除了原文件，软连接通过 “文件名” 找不到源文件，就会用深色背景色标识出来；

示范删除源文件对链接文件的影响：

```
: # rm -f test1
```

![这里写图片描述](http://img.blog.csdn.net/20161230094146137?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

结果和描述一致；

但是，如果我们把test1-so就扔在这里岂不是很浪费，如果你不需要的可以把它删掉，但是如果你还会在这个目录下创建一个 文件名还是 test1 的文件，那么这个软连接文件依然有效，因为它的里面存放的是路径嘛！

```
:# touch test1
```

![这里写图片描述](http://img.blog.csdn.net/20161230094504547?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

是不是test1-so 又变回来了，但是此时因为test1是空的，所以test1-so是没有内容的，不信你试试！

**小结一下**

软连接就说到这里了，真是讲了好长一段，总结一句话，软链接和windows的快捷方式几乎等价；

软连接和硬链接的不同之处在前面的演示已经体现出来了，那么 硬链接的限制软连接是否也有呢？

不能在不同的文件系统，这一条依然有效；

但是软连接是可以对目录进行链接的：

```
: # mkdir ld   //创建一个空目录
: # ln  -s  ld ld-so  //软连接目录ld
: # ls -il     //查看
```

![这里写图片描述](http://img.blog.csdn.net/20161230095631079?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

分析： 成功了，系统并没有报错，你可以自己试试看看用 cd 命令是否可以进入ld-so;其实ld-so还是一个链接文件而已，不过存放的是ld目录的“文件名”,可以看出ld 的大小是 2 ，同时你会发现ld的链接数量为了2？而ld-so 的链接数量还是1，并且此时你用 stat 命令去查看 **ld-so/**
的信息，会发现和ld 的信息一致，而与 ld-so 显示的不一样,也就验证了**ld-so**是一个文件，而**ld-so/** 就变成了目录；

![这里写图片描述](http://img.blog.csdn.net/20161230101524543?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

为什么目录的链接数量会变化呢？ 这和前面所说的不一样啊？
下一点，我们就来讨论这个问题；


----------

最后一点：
**3. 关于目录的链接数量**

前面我们在说文件的软硬链接的时候说到，目录不能被硬链接，但是可以被软连接； 但是软连接不会改变文件的链接数量，那为什么还有目录的数量这么一个概念呢？

 但是事实就是这样的，通过参考鸟哥的书，并自己验证之后，确实有这么一个事实：当新建一个空目录时，新的目录的连接数为 2，而上一层的目录的链接数会 +1；

示范：

```
先查看当前目录的连接数：
: #ls -al   

注意： '.' 代表的是当前目录  '..' 代表上层目录

重新创建空目录 testing；
：# mkdir testing 

再查看新建目录和当前目录的链接数变化
：# ls -al
```

![这里写图片描述](http://img.blog.csdn.net/20161230102631479?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

分析： 通过上图可以很直观的看出当前目录连接数的变化 2->3;
新建目录testing的连接数为 2；

并且不影响当前目录的上一层目录的链接数；

（以下原因有待认真考究 —_—！！）

难道是因为：
**/Test/testing/.** 和 **/Test/testing** 是一样的；
  所以新建的testing目录默认两个链接，并且系统处理为硬链接，并且不允许我们自己创建目录的硬链接；

而上一层目录加 1 的原因是新建目录下默认又有一个 **/Test/testing/..**
的上一层目录的链接；


前述：
我们都知道 linux 一切皆文件，而现实生活中，或者Windows下，创建一个文件都会有一个创建日期来标识这个文件，linux与此不同，Linux下的文件时间是由三个主要的时间参数来决定的，没有创建时间这一概念，而这三个主要的时间参数分别是：

	1. modification (简写： mtime): 当文件的 “内容数据”发生改动时，就会更新这个时间；
	2. status time (简写：ctime ) : 顾名思义，状态时间，当文件的状态改变时就会更新这个时间，直接点说就是文件的权限或者属性被改变；
	3. access time (简写： atime): 当文件的内容被采用，就会更新这个时间；
                           ------参考《鸟哥的Linux私房菜》第三版



注： 我是全程以root权限登录，接下来就这三个主要的改动时间展开叙述；
：查看方式
首先，我们需要知道一条命令：stat 来帮助我们查看文件的三个时间参数；
我们先 touch 一个空文件 test1 ，(touch 这个命令，后面详述。)
然后用 stat 查看文件信息，我们现在只看那三个时间，那三个英文单词应该可以认出来吧!（如果觉得英文别扭，可以把linux设置为中文显示；）

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/20161225113031928.png)

注：
Access   对应  atime;
Modify  对应  mtime;
Change 对应  ctime;

如果想要单独看每个时间参数的话还可以用单独的命令：
ls -lc filename :查看test文件的ctime
ls -lu filename :查看test文件的atime
ls -l filename:查看test文件的mtime
当然，鸟哥的书上也给出了 # ll –time=atime/ctime filename的形式;


：变动方式
既然我们已经知道了这三个时间参数是三个主要的变动的时间，那么接下来就是了解他们的变动方式；

1. atime 的变动
文件的内容被取用时，这个时间就会发生更新，举个最简单的例子，我们平时cat一个文件的时候，就是对文件的内容的读取，那么会不会改变这个时间呢？ 下面我们试试：

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/20161225114553904.png)

分析：因为我们创建test1的时候是个空的文件，所以cat的时候什么都没显示， 对比我们刚开始创建test1时的三个时间，用过cat命令之后，改变的只有atime，而ctime和mtime没有变化；
2. mtime 的变动方式
文件的内容数据发生变化时，这个时间参数会发生变动； 
我们这次测试两个操作： echo 和 vim
2.1 测试echo 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/20161225121346650.png)

分析： 我通过echo命令 在test1中导入了hello looker，然后查看stat, 
通过和上一次的状态对比发现，只有atime没有改变，其它两个时间参数都发生了改变；echo可以在不改变访问时间的基础上，改变文件内容，但是属性怎么也改变了？
文件的大小也是文件的属性啊，你从空文件增加了一个字符串，文件的 大小发生的变化，可以很清晰的从图中的size的变化看出来，所以影响到了ctime；
2.2 测试vim

在文件中加入一句： nice to meet you!

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/20161225121304379.png)

分析：对比上一次的状态，发现三个时间参数都改变了，这个很容易想到，我们用vim命令（最后对vim做简介）打开了文件，就是读取了文件数据，改变了atime，在文件中加入了一句话，即是改变了文件内容和大小，即改变了mtime和ctime;
3 . ctime 的变动方式
文件的状态发生改变，就会更新这个时间；
前面我们的测试中已经两次改变了ctime，虽然不是去专门测试它的，文件的状态就很多了，比如权限和属性，比如前面发生改变的文件大小，所以说，一般情况下，mtime发生改变都会影响ctime,那么我们想单纯的改变ctime，而不改变其它两个时间参数，我们可以试试改变文件权限：

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/20161225123843365.png)

分析：我们先看了一下test1原本的权限，然后赋予了它一个新的权限，然后stat test1，可以看到，改变的只有ctime; 这样我们对ctime的变动方式就有了一个更清晰的了解；
注： 如果你是普通用户去修改文件属性而权限不够的话，可以在命令的最前面加上sudo, 如果还是不行，提示user没有在sudoers文件中的话，可以在sudoers文件中添加，方法在文章最后给出！
小结：
通过上面对三个时间参数的变动方式的分析，对它们有了深一点的认识，可是这样，还满足不了我们的需求，我们还希望，可以按照我们自己的想法，自己给的时间任意的去修改它们，所以，touch应声而来，touch命令可以满足我们的需求；
下表是在网上找的总结的常用的 命令对这三个时间参数的影响！

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B4%5D.png)

touch 命令详解

	1. 了解touch命令

我们在Linux学习一条命令时，首先要做的不是去百度它，不是去看书找它，最先做的，最准确的方式应该是去 man/info 命令，去读最标准的 文档，例如：man touch
我们只看重要的 部分： 

说明文档，至少我是那么认为的，开始三个部分： 
1.名字说明 
2.使用格式 
3.详细描述
我用蓝框标记的那句话，就是我们比较敏感的词汇，大意是：“更新每个文件的访问和修改时间为当前时间”；
![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image.png)

好了，提取到了我们需要的信息； 
下面关于参数的信息，我就不截图了，但是参数的描述里，我们依然可以得到我们需要的信息；
同样我们 info touch, 会看到更详细的说明，和利用touch改变atime和mtime的参数使用方法；这里截取几个明显的说明； 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B2%5D.png)

参数截图（部分） 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B3%5D.png)

这些英文说明都是一些比较好理解的英语，作为一个程序员，这些英语应该可以大致看懂的；
参数列表：
-a : 仅修改访问时间； 
-c : 仅修改文件时间，若该文件不存在则不创建； 
-d : 后面可以接欲修改的日期而不用目前的日期，也可以使用 –date=”日期或时间”； 
-m : 仅修改mtime; 
-t：后面可以接欲修改的时间而不用目前的时间，格式为【YYMMDDhhmm】;
现在，我们对touch的能力有了更明确的认识，不是只停留在原来的只创建文件，那么，我来测试一下这几个命令，顺便演示命令格式（因为我得这个文档比较坑）：

1.1 -a 参数
仅修改访问时间的意思是，只把文件的访问时间更新到最新时间，即当前时间戳；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B8%5D.png)

新建一个文件test,ls -lu test查看atime； 
执行命令 touch -a test; 
然后过会用ls -lu test查看atime; 
为了截图方便，所以才等一会，因为ls -lu 不显示秒！ 
可以直接stat test查看，你会发现ctime也变了，更新到最新时间，和文档说的 only change atime不太一样，后面参数都是一样！
1.2 -c 参数
修改文件时间，若该文件不存在则不创建；

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B9%5D.png)

实践结果，就是把存在的文件的三个时间参数更新到最新时间！ 

1.3 -d 参数
后面可以接欲修改的日期而不用目前的日期，也可以使用 --date="日期或时间"；

第一种形式：touch -d 121212 test
将atime mtime修改为指定日期或者时间，ctime更新到最新时间； 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B10%5D.png)

第二种形式：touch -d “2 days ago” test
采用鸟哥的实例： 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B11%5D.png)

你会注意到atime和mtime日期都退回到两天前，而ctime更新到最新时间；
1.4 -m 参数
和-a参数类似，只不过修改的是mtime的值，同时ctime更新到最新时间；不做截图；

1.5 -t 参数
后面可以接欲修改的时间而不用目前的时间，格式为【YYMMDDhhmm】;

touch -t 1409011212 test //年月日时分

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B12%5D.png)

测试结果发现，mtime和atime都变为指定的时间，而ctime更新到最新时间；
vi,vim 概述
既然前面已经提到了vim而且讲到了用touch来创建文件夹，那么vim必然值得一提，不过，本片博客只是概述，后期我会总结一篇关于vim的配置及使用的博客！
vi 是UNIX世界里极为普通的全屏幕文本编辑器，vim是它的改进版本 vi improved的简称。
现在的linux的发行版本几乎都自带这vi,vim所以不用我们自己下载，我们所熟悉的vi,vim的使用大致就是 vi filename,或者 vim filename, 进入一个文本编辑区，进行文本编辑或者更多的是coding;
而vi有三种工作方式： 
1.命令模式 
当我们vi filename 进入编辑器时就处于命令模式；
2.插入模式 
进入文本编辑器后按 i/o/a等命令即进入了插入模式；
3.底行命令模式 
当我们编辑完成后按esc退出时在最底下的冒号后输命令时就是底行命令模式；
而我们细心一点的话肯定会发现，vi和vim打开文件的最明显的不同之处在于，文本是否有不同色彩（配置才有）；
因为vim是完全兼容vi的，所以vim相对vi有以下几点优势：

1、多级撤消 
我们知道在vi里，按 u只能撤消上次命令，而在vim里可以无限制的撤消。 
2、易用性 
vi只能运行于unix中，而vim不仅可以运行于unix,windows ,mac等多操作平台。 
3、语法加亮 
vim可以用不同的颜色来加亮你的代码。 
4、可视化操作 
就是说vim不仅可以在终端运行，也可以运行于x window、 mac os、windows。 
5、对vi的完全兼容 
某些情况下，你可以把vim当成vi来使用。**

善尾
前文中遗留了一个小问题，就是当你是普通用户时，使用chown或者chgrp改变文件属主或者属组时遇到的权限不够问题；
可以在命令前加 sudo 命令，如：
sudo chown root test.cpp;
如果报以下错误： 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B5%5D.png)

解决方法： 
su 进入root 权限；
然后需要给 etc/sudoers 这个文件一个属主可以写的权限；
chmod u+w /etc/sudoers;

	* 1

最后进入 etc/sudoers 文件
vim /etc/sudoers

	* 1

最后找到图中标注位置： 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B6%5D.png)

在这行底下照着图上的那行抄一行一样的，把root改为你的普通用户名即可！ 

![](https://github.com/BITLQ/Linux/blob/master/Linux%E6%80%BB%E7%BB%93/Linux_time/Image%20%5B7%5D.png)

经本人验证，只能加入一个用户~

Linux��g++/gdb�ļ򵥰�װ��vim������
-----------------------

	����˵������Ƭ����������g++��gdb�İ�װ�Լ�vim�����ý���Centos 6.0 �汾�Ͻ����˲��ԣ����ԣ���ͬ�İ汾���ܻ���ֲ��죡

ע�� g++/gdb�İ�װ���������Ķ��Ǽ��������ذ�װ��

----------

**g++�İ�װ��** 

�������ص�Centos�İ汾���������Դ�gcc��vim������������Ҫ��ֻ��g++���ѣ����û���������� gcc��

Ȼ�������Linux�Ƿ���gcc:

```
��# which gcc;
```

����еĻ��ͻ��г������·����������ʾ��

![����дͼƬ����](http://img.blog.csdn.net/20161229133516703?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


û�еĻ�����ȷ�����**Linux����**�������ʹ���������װ��

```
��# yum  install  gcc;
```

��ȻҲ��������ѹ�������н�ѹ����װ���������ۣ�

�����gcc����ô������Linux�Ƿ���g++:

```
:# which  g++
```

����еĻ��ͻ��г������·����������ʾ��

![����дͼƬ����](http://img.blog.csdn.net/20161229133246883?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

û�еĻ�����ȷ�����**Linux����**�������ʹ���������װ��

```
��# yum  install gcc-c++;  //ע����  gcc-c++;
//ע����Centos�ͺ�ñʹ�ø�������ԣ�
```
��ȻҲ��������ѹ�������н�ѹ����װ���������ۣ�


----------

**gdb�İ�װ ��**

: ����ȷ�����**Linux����**�������ʹ���������װ��

```
��# yum install  gdb;
```

��ʵ�������������� yum ��װ�ģ�


----------

**vim������**

vim��Linux��ǿ��ı༭�������ǳ�ѧ�߶������ְ��ֺޣ�

���ǲ��ò�����vim��ǿ�����������Լ����и������úͲ���İ�װ����vim���õļ������Ժ�windows�µ�IDE��������

������Linux�Դ���vim���þ���ԱȽϼ�ª�ˣ�ʹ��rootȨ�޽����Ŀ¼�µ�etc/ Ŀ¼���г������ļ����������ص��ļ�����ͻᷢ��һ���ļ���Ϊ vimrc���ļ���������.vimrc��������Ǵ��Linux Ĭ�����õĵط���

```
��# cd  /root/etc/
```

![����дͼƬ����](http://img.blog.csdn.net/20161229141359472?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


�������Ĭ�����ã������� vim   vimrc  �����ȥ��һ�£�

������һ���Լ�ȥ���õ�ʱ�򣬲�ȥ�Ķ�����ļ�������ѡ�����Լ���ǰ�û�����Ŀ¼���½�һ�� .vimrc  �ļ���������ǵ����ã�

**ע�� �ڵ�ǰ�û�����Ŀ¼�½������õ�ֻ�Ե�ǰ�û���Ч��**

```
��# cd ~/     //���뵱ǰ�û�����Ŀ¼
��# touch  .vimrc  //����һ�� .vimrc  �ļ�
```
���������㲻��Ҫ�ܶ�Ĺ��ܵĻ������������¼򵥵���������������� .vimrc �ļ����ɣ�

```
��# vim  .vimrc    //����.vimrc  �ļ�
```

���������ݸ��ƽ�ȥ��

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
�������
 
$:x ���� $wq 

 ���б����˳����ɡ���Щlinux��vi������vim��������which vi��alias�鿴��

 �������һ�����ӣ������г��˾����õ������ã���ϸ��������Ϣ����ղο����ϣ�

 ��˫���ſ�ʼ����Ϊע���У���ͬ
 
��ȥ��������й�viһ����ģʽ��������ǰ�汾��һЩbug�;���

 set nocompatible

 ����ʾ�к�

 set number

 ������ļ�������

 filetype on 

 ����¼��ʷ������

 set history=1000 

 ������ʹ��ҹ��ģʽ //����ˬ��

color eveing

 ���﷨��������ʾ

 syntax on 

 �����������ڽ��б�д����ʱ���ڸ�ʽ�����Ϻ����ã�

 ����һ�У�vimʹ���Զ�����Ҳ���ǰѵ�ǰ�еĶ����ʽӦ�õ���һ�У�

 ���ڶ��У���������Ķ����ʽ�����ܵ�ѡ�����ʽ����������C���Ա�

 ��д�Ϻ�����

 set autoindent

 set smartindent

 ����һ������tab��Ϊ4���ո񣬵ڶ������õ���֮�佻��ʱʹ��4���ո�

 set tabstop=4

 set shiftwidth=4

 ������ƥ��ģʽ�����Ƶ�����һ��������ʱ��ƥ����Ӧ���Ǹ�������

 set showmatch

 ��ȥ��vim��GUI�汾�е�toolbar

 set guioptions=T

 ����vim���б༭ʱ�����������󣬻ᷢ��һ��������������ȥ������

 set vb t_vb=

 ���ڱ༭�����У������½���ʾ���λ�õ�״̬��

 set ruler

 ��Ĭ������£�Ѱ��ƥ���Ǹ�������ʾ�ģ������ùرո�����ʾ

 set nohls

 ����ѯʱ�ǳ����㣬��Ҫ����book���ʣ������뵽/bʱ�����Զ��ҵ���һ

 ����b��ͷ�ĵ��ʣ������뵽/boʱ�����Զ��ҵ���һ��bo��ͷ�ĵ��ʣ���

 �������ƣ����в���ʱ��ʹ�ô����û�����ҵ��𰸣�������Ҫƥ��ĵ���

 ��ʱ�������ǻس�

 set incsearch

 ���޸�һ���ļ����Զ����б��ݣ����ݵ��ļ���Ϊԭ�ļ����ӡ�~����׺

 if has(��vms��) //ע��˫����Ҫ�ð�ǵ�����"��"

 set nobackup

 else

 set backup

 endif
```


Ȼ�����ٴ�һ�� xxx.c ���� xxx.cpp�ļ��༭һ�δ��룬�ͻῴ������Ч��������ͼ��

![����дͼƬ����](http://img.blog.csdn.net/20161229140659469?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


----------


**Vim  ������**

ǰ�������Ѿ�˵�ˣ�vim��������֧�ּ򵥵�����Ҳ���԰�װ�����еĲ���������Ҿ�ֱ���г������vim�������ӣ�

http://www.cnblogs.com/ma6174/archive/2011/12/10/2283393.html

��λ��������ÿ���֧�ֺܶ������ԵĻ�����������github �ϸ�����.sh �ļ�������ֻ��Ҫ���ն�ִ��һ������ʲô����������

![����дͼƬ����](http://img.blog.csdn.net/20161229145749719?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

�������ִ����������ʱ������ʾ����������-no-check������
ֻ��Ҫ����ִ�м��ɣ�

```
��#wget https://raw.github.com/ma6174/vim/master/setup.sh --no-check-certificate && bash setup.sh
```

ע�� �������Ļ�����ִ�м����Զ����ذ�װ��

���ǿ��ܰ�װ��֮��vim һ���ļ�����ֺܶ����⣬��Ϊ������Ϊÿ����Linux���ò�ͬ��ԭ�򣬺ܶණ���ò��ˣ���ôֻ��Ҫ������ʾ������кţ������ļ�����Ӧ���� **����** ע�͵����ɣ�
 
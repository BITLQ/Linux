# Linux

**在面试的过程中屡屡被问到设计模式，出现频率很高，可见设计模式的重要性，所以，学习设计模式刻不容缓！**

先了解一下什么是设计模式？

**设计模式的定义：**
		设计模式是一套被反复使用，多数人知晓的、经过分类编目的、代码设计的总结，使用设计模式是为了可重用代码，让代码更容易被他人理解，保证代码可靠性。
		
**设计模式的分类**：按照目的可分为三类，**创建型模式，结构型模式，行为型模式**；按照范围，即模式主要处理类之间的关系还是对象之间的关系分为**类模式和对象模式**；

设计模式主要被广泛应用于面向对象编程；

从最简单的**单例模式**开始学起：**单例模式**，根据名字拆分就可以知道这个模式的意思，即单个实例的模式；

什么是单个实例的模式，既然是面向对象，那么一个类只允许产生一个实例对象的话，就是单例模式；

单例模式按照设计模式的分类属于**创建型模式和对象模式**；

为什么要有单例模式：动机？

最经典也是最容易理解的例子：用windows的都知道，同一时刻只能打开一个任务管理器，不会弹出多个的，为什么呢？因为系统的状态是每时每刻都在变化的，如果你可以同时打开多个任务管理器，而这些管理器显示的内容出现不一致的情况，是不是容易引起用户误解；而如果多个窗口的显示内容一致的话，打开多个窗口是不是很浪费资源；单例模式就是为了解决这种问题而产生的，当前类只允许你拥有一个真实的对象，如果你继续申请，依然返回同一个对象；

**单例模式的标准定**义：单例模式确保某一个类只有一个实例，而且自行实例化并向整个操作系统提供这个实例，这个类成为单例类，它提供全局的访问方法。

**单例模是一种对象创建型模型，单例模式又名单件模式或单态模式**。


----------
上面说的都是概念，不了解是不行的，但是只看概念是不能完全理解的，所以，代码才是真谛!

通过了解单例模式的概念，我们想要设计出这样一个类，该如何设计呢？

**code is cplusplus**

**饿汉单例**，即在最开始的时候，静态对象就已经创建完成；

即类中包含一个静态成员指针，该指针指向该类的一个对象，提供一个公有的静态成员方法，返回该对象指针；为了使得对象唯一，还需要将构造函数设为私有；

```
class Singleton
{
	//构造函数设为私有；
	Singleton()
	{
		cout<<"Singleton()"<<endl;
	}
	static Singleton* intance;  //静态成员，指向Singleton对象的指针
public:
	//提供静态共有方法，可以使用类名加域名进行访问，返回对象指针；
	static Singleton*  GetSingleton()
	{
		return intance;
	}
};
//静态成员必须在类外进行初始化
Singleton* Singleton::intance = new Singleton();
```

那么，我们现在要怎么进行测试呢？   测试哪几个方面呢？

```
int main()
{
	cout<<"main begin"<<endl;    //验证静态对象的创建时在main之前
	
	//验证无法重建实例
	//Singleton tmp;      
	//Singleton* ptr = new Singleton();

	//调用共有的静态成员方法
	Singleton* tmp1 = Singleton::GetSingleton();
	Singleton* tmp2 = Singleton::GetSingleton();

	cout<<(tmp1==tmp2)<<endl;   //判断获取对象是否为同一个
	return 0;
}
```

上面的mian中，我们主要对单例模式的特点进行了测试，发现，我们无法在其它地方再创建一个新的Singleton对象，即下面的两种方法都会失败，这要归功于私有的构造函数；

```
	Singleton tmp;      
	Singleton* ptr = new Singleton();
```

然后，我们注意到，在刚进入main函数，我们就打印了一句“”main begin“”，为什么要在这里加入一句输出语句呢？

因为我们此时的单例模式采用的是饿汉单例，所以，哪怕你还没用到我这个对象，我也会先创建一个出来，先占着，即所谓的饿汉，其实就是类似于全局变量的构造是在进入main函数之前的原理，在这里验证一下，还有最后的比较两个通过共有的静态成员方法返回的对象指针是否一致来验证我们单例模式返回的是同一个对象；

结果：
![这里写图片描述](http://img.blog.csdn.net/20170403103935208?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


----------
上面说的是饿汉单例模式，但是这个模式有个不好的地方就是，如果我一直不使用这个对象，而这个对象是已经存在的，它会一直占着那块内存不那啥，所以啊，比较懒的人就不愿意那么早就准备好；

**单例模式之懒汉单例：**

所谓懒汉模式，就是尽可能晚的创建这个对象的实例，即在单例类第一次被引用时将自己初始化；其实C++里很多地方都是类似这样的思想，比如晚绑定，写时拷贝技术等，就是尽量使资源的利用最大化，不要让空闲的人还占着有限的资源；

懒汉单例的实现：其实就是将静态对象指针初始化为NULL，当单例类被引用的时候，先进行判断指针是否为NULL，为NULL的时候再去实例一个对象，不会NULL时，直接返回静态对象指针；达到保证只有一个实例的目的；

**懒汉单例类：**

```
class Singleton
{
	Singleton()
	{
		cout<<"Singleton()"<<endl;
	}
	static Singleton* intance;  
public:
	static Singleton*  GetSingleton()
	{
		if(intance == NULL)
		{
			intance = new Singleton();
			cout<<"once"<<endl;
		}
		else
		{
			cout<<"it is not once"<<endl;
		}
		return intance;
	}
};
//静态成员必须在类外进行初始化
Singleton* Singleton::intance = NULL;
```

**懒汉单例类和饿汉单例唯一的不同就是，这个唯一的实例创建的时机不同；是一种按需分配的方式；**

![这里写图片描述](http://img.blog.csdn.net/20170403105712249?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvYml0Ym9zcw==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

**小结一下**

单例模式的实现过程中，需要注意以下三点：

1. 单例类的构造函数为私有；
2.  提供一个自身的静态私有成员变量；
3.  提供一个共有的静态工厂方法；


----------
**单例模式的线程安全问题：**
	
							----《剑指offer》单例模式学习
以懒汉单例为例，如果此时多线程进行操作，简单点以两个线程为例，假设pthread_1刚判断完 intance 为NULL  为真，准备创建实例的时候，切换到了pthread_2, 此时pthread_2也判断intance为NULL为真，创建了一个实例，再切回pthread_1的时候继续创建一个实例返回，那么此时就不再满足单例模式的要求了，  既然这样，是因为多线程访问出的问题，那我们就来加把锁，使得线程同步；

**以伪代码的形式展现（省略pthread_mutex_lock/ulock）:**
```
	static Singleton*  GetSingleton()
	{
		lock(mutex)   //伪代码
		{
			if(intance == NULL)
			{
				intance = new Singleton();
				cout<<"once"<<endl;
			}
			else
			{
				cout<<"it is not once"<<endl;
			}
		}
		return intance;
	}
```

我们在判空并创建实例的时候加一把锁，则每个线程都需要申请锁，进行互斥的访问，以达到同步的目的；

那么我们这样写的代码是没有问题的，但是效率可能有点低，因为我们加锁的代价其实是很大的，那么有没有什么改进的地方可以尽可能少的加锁呢？

这就是加锁的注意点，不同的加锁方式带来的效率可能完全不同，比如，此时如果我们在加锁之前再加一个判断，if ( intance == NULL),这样的话，如果静态实例已经存在则不会进行加锁，同时也解决了上面所说的刚开始的时候多线程进行创建的同步问题；

**伪代码如下:**

```
static Singleton*  GetSingleton()
	{
		if(intance == NULL) //再加一层判断
		{
			lock(mutex)   //伪代码
			{
				if(intance == NULL)
				{
					intance = new Singleton();
					cout<<"once"<<endl;
				}
				else
				{
					cout<<"it is not once"<<endl;
				}
			}
		}
		return intance;
	}
```

到这里，C++的单例模式就差不多了，剑指offer上面还提到了C#创建单例模式的方法；


----------

**单例模式的优点**

1. 提供了对唯一实例的受控访问。因为单例类封装了它的唯一实例，所以它可以严格控制客户怎样以及何时访问它；
2. 由于在系统内存中只存在一个对象，因此可以节约系统资源，对于一些需要频繁创建和销毁的对象，单例模式无疑可以提高系统的性能。
3. 允许可变数目的实例，基于单例模式我们可以扩展，使用与单例控制相似的方法来获得指定个数的对象实例。（即单例类内有多个静态对象指针成员，每次当单例类被引用时随机分配一个实例对象）；

**单例模式的缺点**

1. 因为单例模式没有抽象层，所以单例类的扩展有很大的困难；
2. 单例类的职责过重，即是工厂角色，提供了工厂的方法，同时又充当了产品的角色；
3. 滥用单例类会带来一些负面问题；


**单例模式的适用场景**

1. 系统只需要一个实例对象，或者考虑到资源消耗的太大而只允许创建一个对象。
2. 客户调用类的单个实例只允许使用一个公共访问点，除了该访问点之外不允许通过其它方式访问该实例.(就是共有的静态方法)；


						---参考《设计模式》刘伟主编

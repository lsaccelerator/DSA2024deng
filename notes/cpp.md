# 函数
## 函数声明
- constexpr：返回值为常量，可在编译时进行计算；
  - const 与 constexpr 变量之间的主要 区别是，const 变量的初始化可以推迟到运行时进行。constexpr 变量必须在编译时进行初始化。 所有的 constexpr 变量都是 const。constexpr执行速度更快。
- inline：指示编译器将对函数的每个调用替换为函数代码本身；
- static：内部链接，可见性限制在声明它的同一翻译单元（一个cpp文件）内；
  	- 默认情况下，以下对象具有内部链：const对象、constexpr对象、typedef对象、命名空间范围中的static 对象

## 函数参数
- 默认情况：参数通过值传递给函数，即所创建一个传递的对象的副本，函数收到副本。
- 引用传递：不创建副本。函数直接对原始对象进行修改，若不想修改可用const&作为参数。
# 类 class
## 形式
```
	class X{
	public:
	int f(int i){m=i; return mf(i)};
	//用户接口
	private:
	int m;
	int mf(int);
	//仅能被该类的成员访问，默认
	};
	//通过int y = x.f(2)给私有的m赋值、调用私有的mf
	//不能直接x.mf(2)
```

## 成员函数
声明在类内会成为内联的
### 构造函数
与类同名，用于初始化，没有类型，也无返回值，可用于赋初值、检查初值有效性，从而防止产生非法的类，如果没有显式定义构造函数，编译器会自动生成隐式inline构造函数。

## 析构函数
对象被销毁时，自动调用其成员中的析构函数。

## 结构 struct
默认成员为public的类

## 枚举类型
```
enum class Month{
	jan = 1, feb, mar
};
//意为jan，feb，mar为Month可能的取值，是整型量
Month m = Month::feb
//赋值操作
```

## 运算符重载
可以在类、枚举对象上定义运算符，但必须是C++已有的运算符，包括参数个数也要一样。





有public, protected, private三种继承方式，它们相应地改变了基类成员的访问属性。

- 1.**public 继承：**基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：public, protected, private
- 2.**protected 继承：**基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：protected, protected, private
- 3.**private 继承：**基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：private, private, private

但无论哪种继承方式，上面两点都没有改变：

- 1.private 成员只能被本类成员（类内）和友元访问，不能被派生类访问；
- 2.protected 成员可以被派生类访问。

# 错误处理
## Throw
try{
	if() throw(A)
}
catch(A){
}

# 自由空间和指针、引用
## new 
`
int* pi = new int[3]
`
new返回一个所分配内存的首地址，可以分配多块。
  *注*：不能把指向不同类型的指针赋值给指针，如int[0]和int[2]之间隔了2个int大小，不能用指向double的赋给pi。
## 空指针nullptr
  

# 引用(reference)
和指针一样存储其他对象的地址，但语法行为与对象本身一样，类似于一个自动解引用的不可变指针。`int&r =1; r=&b//错误,不可改变引用自身的值`向函数传递引用而非大型对象的效率通常更高，这使编译器能够在保持已用于访问对象的语法的同时传递对象的地址。
有两种引用：引用命名变量的 lvalue 引用和引用临时对象的 rvalue 引用。 & 运算符表示 lvalue 引用，&& 运算符表示 rvalue 引用或通用引用（rvalue 或 lvalue）。
为指针赋值：赋值给指针自己
为引用赋值：深拷贝，赋值给引用的对象
# 类
## 函数模板
```
//单个类型参数T的泛型函数模板
//参数a,b和返回值类型均为T
//调用函数时，编译器会将每个 T 实例替换为由用户指定或编译器推导的具体类型参数。 编译器从模板生成类或函数的过程称为“模板实例化”
//如把abc<T>实例化为abc<int>
template <typename T>	
T abc(const T& a, const T& b)
{
	return a<b? a:b
}

int i = abc<int>(a,b) //可以自定义模板实例
```

## 继承
派生类使用父类成员函数需要用this->
构造函数、析构函数、运算符operator=都不会继承
# 其他一些
## 左值、右值
左值 (lvalue) ：可以放在赋值号的左边，表示了一个占据内存中某个可识别的位置（也就是一个地址）的对象。有内存地址的表达式（包括变量）。
右值：其他对象，没有内存地址处于缓存的值，即编译时未分配内存或使用寄存器存放的值。
- ++i的操作是对i加1后再赋值给i，所以++i的结果是具名的，名称就是i，所以++i是左值
- 对于i++而言，先将i的值进行拷贝(此处假设拷贝到临时变量ii)，然后再对i加1，最后返回ii(其实不存在的，为了在此表述方便)。所以i++是不具名的，因此不是glvaue，所以i++是右值，又因为不具名，且是右值，所以i++是纯右值
https://www.51cto.com/article/701636.html

### 为什么move只能用右值参数
A(A&& a)
定义A x( A(3))：先构造A(3)，换指针传递给x
A(const A&v)
定义A y(x)：v应传入有址的左值实参，因此需先构造x，再构造y，但构造完y后x仍不能析构
## 拷贝
浅拷贝：拷贝指针，因此两个指针会指向同一个对象。如：指针，引用。（move）
深拷贝：拷贝指针指向的数据，因此两个指针指向不同的对象。分配新的内存空间进行元素的拷贝。如：vector, string.（copy）
## 名字空间
头文件：
namespace A_lib{
	struct Color{};
	int line;
}

使用：
```
#inclue <A_lib>
int main{
	i = A_lib::line;
}
```

如果要直接使用line，需要using namespace A_lib
## 初始化并定义
```
int x;
x = 2;
//先定义再赋值
int x{2};
//定义并初始化

Date(int yy,int mm, int dd)
	:y(yy),m(mm),d(dd){}
//对函数Date的成员初始化
```

#
## constant
`const int a = 7`
a只能被赋值一次，不可再次赋值如`a=8 //error`

```
int a = 8;
int b = 9;
int const *p1 = a; //左定值，p1指向的地址内容a不可变
int* const p2 = &a; //右定值，p2指向的地址&a不可变
const int * const p3 = &a //都不可变
p1 = &b;
*p2 = b;
```
## const参数传递
### 传递指针
避免指针被意外篡改
### 传递自定义类型
因为传参需要构造临时对象复制参数，构造临时对象又要调用构造函数，浪费时间，所以多用const+引用传递。
## const修饰成员函数
被修饰的成员函数不能修改被调用对象的值，不允许更改类中任何数据成员的值。如果对象中一部分成员可修改可用mutable修饰。

# 作用域

- 全局作用域：在所有函数和代码块之外声明的变量具有全局作用域，它们可以被*程序(当前源文件)*中的任何函数访问。全局变量在程序开始时被创建，在程序结束时被销毁。

- 局部作用域：在*函数*内部声明的变量具有局部作用域，它们只能在函数内部访问。局部变量在函数每次被调用时被创建，在函数执行完后被销毁。

- 块作用域：在*代码块（被一个{}括起来的区域）*内部声明的变量具有块作用域，它们只能在代码块内部访问。块作用域变量在代码块每次被执行时被创建，在代码块执行完后被销毁。

- 类作用域：在类内部声明的变量具有类作用域，它们可以被类的所有成员函数访问。类作用域变量的生命周期与类的生命周期相同。
```
#include <iostream>

int main() {
    int a = 10;
    {
        int a = 20;  // 块作用域变量
        std::cout << "块变量: " << a << std::endl;
    }
    std::cout << "外部变量: " << a << std::endl;
    return 0;
}
```

## static,extern,const,inline
### static
static修饰全局变量将外部链接性改为内部链接性（仅仅在定义它的源文件中共享，对其他文件隐藏，定义的实体是源文件私有的)。
不会放在头文件中，因为头文件就是用来共享的，用static是为了避免被共享。

### const
const修饰全局默认是具有内部链接性，就像使用了static修饰后一样。（仅C++，C还是外部链接）
由于const全局常量是内部链接性的，所以我们可以将const定义放在头文件中，这样所有包含了这个头文件的源文件都有了*自己的一组*const 定义,由于const为文件内部链接性，所以不会有重定义错误。

### inline
内部链接
全局inline函数默认是内部链接性，这也就是inline函数为什么可以整体定义放在头文件中的原因了。这点和宏函数一样，宏也是仅仅在一个源文件中有效的。
### extern